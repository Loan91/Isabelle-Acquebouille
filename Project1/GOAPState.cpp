#include "GOAPState.hpp"

GOAPState::GOAPState() : playerPosition(0.f, 0.f), health(100), inSight(false), inRange(false), lowHealth(false) {}

void GOAPState::SetPlayerPosition(Vector2f position) { playerPosition = position; }
Vector2f GOAPState::GetPlayerPosition() const { return playerPosition; }

void GOAPState::SetHealth(int hp) { health = hp; }
int GOAPState::GetHealth() const { return health; }

void GOAPState::SetInRange(bool range) { inRange = range; }
bool GOAPState::InRange() const { return inRange; }

void GOAPState::SetInSight(bool sight) { inSight = sight;  }
bool GOAPState::InSight() const { return inSight; }

bool GOAPState::isLowHealth() const {
    return health <= 30;
}

void GOAPState::SetLowHealth(bool health) { lowHealth = health; }