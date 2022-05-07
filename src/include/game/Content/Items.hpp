#include "game/Object/Item.hpp"
#include "game/World/Tile.hpp"
#include <vector>
#pragma once

std::vector<Item> itemTypes;
sf::Texture itemTexture;

void LoadStandardItems(){
    sf::Sprite tempSprite;
    Item tempItem;

    itemTexture.loadFromFile("assets/items.png");

    tempSprite.setTexture(itemTexture);
    tempSprite.setTextureRect({0, 0, 8, 8});

    tempItem.name = "gun";
    tempItem.description = "it shoots";
    tempItem.sprite = tempSprite;

    itemTypes.push_back(tempItem);
};