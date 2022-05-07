#include "game/Object/Item.hpp"
#pragma once

struct ItemDrop {
    int quantity;
    int quantityModifier;
    float propability;
    Item item;
};