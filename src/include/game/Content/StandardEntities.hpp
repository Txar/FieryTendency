#include "game/Object/Entity.hpp"
#include "game/World/Tile.hpp"
#include "game/Content/Items.hpp"
#include <vector>
#pragma once

std::vector<Entity> entityTypes;
std::vector<HealthBar> healthBars;
std::vector<sf::Texture> entityTextures;
Entity standard_item_entity;

void LoadStandardEntities(){
    sf::Texture tempTexture;
    ObjectSprite tempSprite;

    tempSprite.sprite.setTexture(itemTexture);
    tempSprite.sprite.setTextureRect({0, 0, 8, 8});

    standard_item_entity.invincible = true;
    standard_item_entity.item = true;

    tempTexture.loadFromFile("assets/badguy.png");
    entityTextures.push_back(tempTexture);

    Entity entity;
    CollisionBox tempCollisionBox;
    
    tempSprite.sprite.setTexture(entityTextures.at(0));
    
    //player
    entity.player = true;

    tempCollisionBox.width = 18;
    tempCollisionBox.offset.x = 0;

    tempCollisionBox.height = 24;
    tempCollisionBox.offset.y = 0;

    tempSprite.sprite.setTextureRect({0, 0, 18, 24});
    tempSprite.offset.x = tempSprite.offset.y = 0;
    entity.sprites.push_back(tempSprite);

    tempSprite.sprite.setTextureRect({0, 24, 18, 24});
    tempSprite.offset.x = tempSprite.offset.y = 0;
    entity.dead_sprites.push_back(tempSprite);

    entity.collisionBoxes.push_back(tempCollisionBox);

    HealthBar hb;
    tempTexture.loadFromFile("assets/smallhealthbar.png");
    HPtextures.push_back(tempTexture);
    hb.setTexture(0);
    hb.max = 20;
    hb.current = 20;
    hb.spritesAmount = 10;
    hb.spriteSize.x =  32;
    hb.spriteSize.y = 8;

    hb.currentSprite.setTexture(HPtextures.at(hb.texture));

    healthBars.push_back(hb);

    ItemDrop tempDrop;
    tempDrop.item = itemTypes.at(0);
    tempDrop.propability = 1;
    tempDrop.quantity = 1;
    tempDrop.quantityModifier = 0;

    entity.loot.push_back(tempDrop);

    entity.HP = healthBars.at(0);
    entityTypes.push_back(entity);
};