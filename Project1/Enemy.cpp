#include "Enemy.hpp"

Enemy::Enemy(float x, float y, int hp) : Entity(x, y, Color::Red, hp), currentGoal(Goal::Patrouiller) {
    setupPatrolPoints();
}

void Enemy::update(float deltaTime, Grid& grid, vector<Entity*> players) {
    if (players.empty()) return;

    Entity* player = players[0];
    Vector2f playerPosition = player->shape.getPosition();
    state.SetPlayerPosition(playerPosition);
    state.SetHealth(health);

    float distanceToPlayer = hypot(playerPosition.x - shape.getPosition().x, playerPosition.y - shape.getPosition().y);
    bool inSight = (distanceToPlayer < DETECTION_RADIUS);
    bool inRange = (distanceToPlayer < DETECTION_RADIUS2);
    bool lowHealth = (distanceToPlayer < DETECTION_RADIUS2);
    state.SetInSight(inSight);
    state.SetInRange(inRange);
    state.SetLowHealth(lowHealth);

    if (state.isLowHealth() && player->isAlive()) {
        currentGoal = Goal::Fuir;
    }
    else if (state.InRange() && player->isAlive()) {
        currentGoal = Goal::Attaquer;
    }
    else if (state.InSight() && player->isAlive()) {
        currentGoal = Goal::Suivre;
    }
    else if (!state.InSight() && player->isAlive()) {
        currentGoal = Goal::Patrouiller;
    }
    else if (!player->isAlive()) {
        return;
    }

    vector<GOAPAction*> plan = planner.Plan(state, currentGoal);

    for (auto action : plan) {
        if (action->CanExecute(state)) {
            action->Execute(state);

            if (dynamic_cast<Patrouiller*>(action)) {
                patrol(deltaTime, grid, playerPosition);
            }
            else if (dynamic_cast<Suivre*>(action)) {
                followPlayer(deltaTime, grid, playerPosition);
            }
            else if (dynamic_cast<Attaquer*>(action)) {
                attackPlayer(players);
            }
            else if (dynamic_cast<Fuir*>(action)) {
                fleePlayer(deltaTime, grid, playerPosition);
            }
        }
        delete action;
    }
}

void Enemy::moveTowards(const Vector2f& target, float deltaTime, Grid& grid) {
    Vector2f direction = target - shape.getPosition();
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) direction /= length;

    Vector2f movement = direction * SPEED * deltaTime;

    auto isWalkable = [&](float x, float y) {
        int gridX = static_cast<int>(x / CELL_SIZE);
        int gridY = static_cast<int>(y / CELL_SIZE);
        return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
        };
    Vector2f newPosition = shape.getPosition() + movement;
    FloatRect newBounds(newPosition, shape.getSize());
    if (isWalkable(newBounds.left, newBounds.top) &&
        isWalkable(newBounds.left + newBounds.width, newBounds.top) &&
        isWalkable(newBounds.left, newBounds.top + newBounds.height) &&
        isWalkable(newBounds.left + newBounds.width, newBounds.top + newBounds.height)) {
        shape.move(movement);
    }
}

void Enemy::moveAway(const Vector2f& target, float deltaTime, Grid& grid)
{
    Vector2f direction = target - shape.getPosition();
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) direction /= length;

    Vector2f movement = direction * SPEED * deltaTime;

    auto isWalkable = [&](float x, float y) {
        int gridX = static_cast<int>(x / CELL_SIZE);
        int gridY = static_cast<int>(y / CELL_SIZE);
        return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
        };
    Vector2f newPosition = shape.getPosition() + movement;
    FloatRect newBounds(newPosition, shape.getSize());
    if (isWalkable(newBounds.left, newBounds.top) &&
        isWalkable(newBounds.left + newBounds.width, newBounds.top) &&
        isWalkable(newBounds.left, newBounds.top + newBounds.height) &&
        isWalkable(newBounds.left + newBounds.width, newBounds.top + newBounds.height)) {
        shape.move(-movement);
    }
}

void Enemy::fleePlayer(float deltaTime, Grid& grid, Vector2f playerPosition) {
    Vector2f position = shape.getPosition();

    Vector2f direction = playerPosition - position;
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        direction /= distance;
        position += direction * 0.2f;
    }
    moveAway(playerPosition, deltaTime, grid);
}

void Enemy::attackPlayer(vector<Entity*> players) {
    for (auto& player : players) {
        Player* p = dynamic_cast<Player*>(player);
        if (p && p->isAlive() && shape.getGlobalBounds().intersects(p->shape.getGlobalBounds())) {
            //p->takeDamage(DAMAGE);
            //cout << "Player HP: " << p->health << endl;
        }
    }
}

void Enemy::followPlayer(float deltaTime, Grid& grid, Vector2f playerPosition) {
    Vector2f position = shape.getPosition();

    Vector2f direction = playerPosition - position;
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        direction /= distance;
        position += direction * 0.2f;
    }
    moveTowards(playerPosition, deltaTime, grid);
}

void Enemy::patrol(float deltaTime, Grid& grid, Vector2f playerPosition) {
    if (patrolPoints.empty()) return;

    static int currentPatrolIndex = 0;
    static vector<Vector2i> currentPath;
    static int pathIndex = 0;

    Vector2f position = shape.getPosition();
    Vector2i start(static_cast<int>(position.x / CELL_SIZE), static_cast<int>(position.y / CELL_SIZE));

    Vector2f target = patrolPoints[currentPatrolIndex];
    Vector2i end(static_cast<int>(target.x / CELL_SIZE), static_cast<int>(target.y / CELL_SIZE));

    if (currentPath.empty() || pathIndex >= currentPath.size()) {
        Pathfinding pathfinder;
        currentPath = pathfinder.findPath(grid, start, end);
        pathIndex = 0;
    }

    if (!currentPath.empty() && pathIndex < currentPath.size()) {
        Vector2i nextCell = currentPath[pathIndex];
        Vector2f nextPosition(nextCell.x * CELL_SIZE, nextCell.y * CELL_SIZE);

        Vector2f movement(0, 0);

        if (position.x < nextPosition.x) movement.x = SPEED * deltaTime;
        else if (position.x > nextPosition.x) movement.x = -SPEED * deltaTime;
        else if (position.y < nextPosition.y) movement.y = SPEED * deltaTime;
        else if (position.y > nextPosition.y) movement.y = -SPEED * deltaTime;

        if (abs(position.x - nextPosition.x) < abs(movement.x)) movement.x = nextPosition.x - position.x;
        if (abs(position.y - nextPosition.y) < abs(movement.y)) movement.y = nextPosition.y - position.y;

        shape.move(movement);

        if (shape.getPosition() == nextPosition) {
            pathIndex++;
        }
    }

    if (start == end) {
        currentPatrolIndex = (currentPatrolIndex + 1) % patrolPoints.size();
        currentPath.clear();
    }
}

void Enemy::setupPatrolPoints() {
    patrolPoints.clear();

   patrolPoints.emplace_back(700, 450);

   patrolPoints.emplace_back(100,450);
        
    
}