#ifndef ENEMY_HPP
#define ENEMY_HPP
#pragma once
#include "Entity.hpp"
#include "Suivre.hpp"
#include "Player.hpp"
#include "Attaquer.hpp"
#include "Pathfinding.hpp"
#include "Fuir.hpp"
#include "Patrouiller.hpp"
#include "GOAPState.hpp"
#include "GOAPPlanner.hpp"
#include "includes.hpp"

class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    static constexpr float DETECTION_RADIUS = 200.0f;
    static constexpr float DETECTION_RADIUS2 = 50.0f;
    static constexpr int DAMAGE = 10;

    Enemy(float x, float y, int hp);
    void update(float deltaTime, Grid& grid, vector<Entity*> players) override;

private:
    GOAPState state;
    GOAPPlanner planner;
    Goal currentGoal;

    vector<Vector2f> patrolPoints;
    int currentPatrolIndex = 0;

    void moveTowards(const Vector2f& target, float deltaTime, Grid& grid);
    void moveAway(const Vector2f& target, float deltaTime, Grid& grid);
    void fleePlayer(float deltaTime, Grid& grid, Vector2f playerPosition);
    void patrol(float deltaTime, Grid& grid, Vector2f playerPosition);
    void followPlayer(float deltaTime, Grid& grid, Vector2f playerPosition);
    void attackPlayer(vector<Entity*> players);
    void setupPatrolPoints();
};

#endif