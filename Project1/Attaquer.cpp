#include "Attaquer.hpp"
#include <iostream>

bool Attaquer::CanExecute(const GOAPState& state) {
    return state.InRange();
}

void Attaquer::Execute(GOAPState& state) {
    //cout << "L'ennemi attaque le joueur !\n";
}