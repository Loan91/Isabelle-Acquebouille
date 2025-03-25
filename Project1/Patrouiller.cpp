#include "Patrouiller.hpp"
#include "Enemy.hpp"

bool Patrouiller::CanExecute(const GOAPState& state) {
    return !state.InSight();
}

void Patrouiller::Execute(GOAPState& state) {
   // cout << "L'ennemi patrouille !\n";
}