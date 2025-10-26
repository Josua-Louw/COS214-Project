#ifndef DECORATIONADAPTER_H
#define DECORATIONADAPTER_H

#include "Decoration.h"
#include "Item.h"

/**
 * @file DecorationAdapter.h
 * @brief This file contains the definition of the DecorationAdapter class.
 */

 /**
  * @class DecorationAdapter
  * @brief Adapter class to adapt Decoration to Item interface.
  */

class DecorationAdapter : public Item {
private:
    Decoration* decoration;
public:
    /**
     * @brief Constructor for DecorationAdapter.
     * @param d Pointer to the Decoration object to be adapted.
     */
    DecorationAdapter(Decoration* d) : decoration(d) {}
    /**
     * @brief Gets the name of the decoration.
     * @return The name of the decoration as a string.
     */
    std::string getName() const override;
    /**
     * @brief Destructor for DecorationAdapter.
     */
    ~DecorationAdapter();
};

#endif // DECORATIONADAPTER_H
