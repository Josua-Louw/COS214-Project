#include "PlantCaretaker.h"

#include <condition_variable>
#include <stdexcept>

#include "WaterPlant.h"
#include "FertilizePlant.h"
#include "NurseryMediator.h"
#include <iostream>
/**
 * @file PlantCaretaker.cpp
 * @brief Implementation of the PlantCaretaker class.
 *
 * Handles plant care tasks by processing WaterPlant and FertilizePlant commands, supporting the Command Pattern (FR5). Participates in the Chain of Responsibility Pattern (FR6) by handling or delegating tasks via nextStaff. Interacts with Plant (FR3 Strategy, FR4 State) and NurseryHub (Mediator, FR7).
 */
using CommandPtr = std::shared_ptr<Command>;


void PlantCaretaker::receiveCommand(CommandPtr command) {
    std::unique_lock<std::mutex> lock(staffMutex);

    if (!command || !command->getPlant()) return;
    if (!command->getPlant() || !command->getPlant()->getIsActive()) return;

    if (staffBusy) {
        if (nextStaff)
            nextStaff->receiveCommand(command);
        return;
    }

    staffBusy = true;
    lock.unlock();

    std::thread([this, command]() {
        auto plant = command->getPlant();
        if (!plant || !plant->getIsActive()) return;

        std::mutex execMutex;
        std::condition_variable cv;
        bool done = false;

        std::thread execThread([&]() {
            if (!plant || !plant->getIsActive()) {
            return;
            }
            nurseryHub->beginCare(plant, command->getType());

            command->execute();
            {
                std::lock_guard<std::mutex> lock(execMutex);
                done = true;
            }
            cv.notify_one();
        });

        // Wait for execute() to complete before finishing care
        {
            std::unique_lock<std::mutex> lock(execMutex);
            cv.wait(lock, [&] { return done; });
        }

        execThread.join();
        nurseryHub->finishCare(plant, command->getType() ,true);

        {
            std::lock_guard<std::mutex> lock(staffMutex);
            staffBusy = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }).detach();
}

void PlantCaretaker::printChain() {
    std::cout << this->getId() << ", ";
    if (nextStaff)
    nextStaff->printChain();
}
