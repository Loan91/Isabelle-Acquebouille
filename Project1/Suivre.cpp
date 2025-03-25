#include "Suivre.hpp"
#include "Enemy.hpp"

bool Suivre::CanExecute(const GOAPState& state) {
    return state.InSight();
}

void Suivre::Execute(GOAPState& state) {
   // cout << "L'ennemi suit le joueur !\n";
}