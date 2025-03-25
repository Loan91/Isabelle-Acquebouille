
#ifndef GOAPSTATE_HPP
#define GOAPSTATE_HPP
#pragma once

#include "includes.hpp"

class GOAPState {
private:
    Vector2f playerPosition;
    int health;
    bool inRange;
    bool inSight;
    bool lowHealth;
public:
    GOAPState();

    void SetPlayerPosition(Vector2f position);
    Vector2f GetPlayerPosition() const;

    void SetHealth(int hp);
    int GetHealth() const;

    void SetInRange(bool range);
    bool InRange() const;

    void SetInSight(bool sight);
    bool InSight() const;

    bool isLowHealth() const;
    void SetLowHealth(bool health);
};

#endif