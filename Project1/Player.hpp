#ifndef PLAYER_HPP
#define PLAYER_HPP
#pragma once
#include "includes.hpp"
#include "Entity.hpp"

class Player : public Entity {
public:
    static constexpr float SPEED = 200.0f;
    static constexpr int DAMAGE = 20;
    static constexpr float ATTACK_COOLDOWN = 0.5f;
    bool isAlive() const;

    float attackTimer;

    Player(float x, float y, int hp);
    void attack(vector<Entity*> enemies);
    void update(float deltaTime, Grid& grid, vector<Entity*> enemies) override;
    void takeDamage(int damage);
};

#endif