#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once
#include <SFML/Graphics.hpp>
#include "includes.hpp"
#include "Grid.hpp"

class Entity {
public:
    RectangleShape shape;
    Vector2f velocity;
    int health;

    Entity(float x, float y, Color color, int hp);
    virtual void update(float deltaTime, Grid& grid, vector<Entity*> neededEntities) = 0;
    bool isAlive() const;
    void takeDamage(int damage);
};


#endif // ENTITY_HPP