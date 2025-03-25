#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "Enemy.hpp"

bool Player::isAlive() const
{
    return health > 0;
}

Player::Player(float x, float y, int hp) : Entity(x, y, Color::Blue, hp), attackTimer(0.f) {}

void Player::update(float deltaTime, Grid& grid, vector<Entity*> enemies) {
    if (!isAlive()) return;

    Vector2f movement(0.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::Z)) movement.y -= SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::S)) movement.y += SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::Q)) movement.x -= SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::D)) movement.x += SPEED * deltaTime;

    Vector2f newPosition = shape.getPosition() + movement;
    FloatRect newBounds(newPosition, shape.getSize());

    auto isWalkable = [&](float x, float y) {
        int gridX = static_cast<int>(x / CELL_SIZE);
        int gridY = static_cast<int>(y / CELL_SIZE);
        return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
        };

    if (isWalkable(newBounds.left, newBounds.top) &&
        isWalkable(newBounds.left + newBounds.width, newBounds.top) &&
        isWalkable(newBounds.left, newBounds.top + newBounds.height) &&
        isWalkable(newBounds.left + newBounds.width, newBounds.top + newBounds.height)) {
        shape.move(movement);
    }

    attackTimer += deltaTime;
    if (Mouse::isButtonPressed(Mouse::Left) && attackTimer >= ATTACK_COOLDOWN) {
        attack(enemies);
        attackTimer = 0.f;
    }
}
void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;

   // cout << "Player prend " << damage << " damage. HP restant : " << health << endl;

    if (!isAlive()) {
       // cout << "Le joueur est mort ! Game Over !" << endl;
        shape.setFillColor(Color::Transparent);
    }
}

void Player::attack(vector<Entity*> enemies) {
    for (auto& enemy : enemies) {
        Enemy* e = dynamic_cast<Enemy*>(enemy);
        if (e && e->isAlive() && shape.getGlobalBounds().intersects(e->shape.getGlobalBounds())) {
            e->takeDamage(DAMAGE);
           // cout << "Enemy HP: " << e->health << endl;
        }
    }
   // cout << "Player attacks\n";
}