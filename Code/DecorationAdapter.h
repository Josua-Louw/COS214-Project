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
    DecorationAdapter(Decoration* d) : decoration(d) {}
    std::string getName() const override;
    ~DecorationAdapter();
};

#endif // DECORATIONADAPTER_H
