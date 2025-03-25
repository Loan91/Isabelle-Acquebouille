#include "Fuir.hpp"
#include <iostream>

bool Fuir::CanExecute(const GOAPState& state) {
    return state.isLowHealth();
}

void Fuir::Execute(GOAPState& state) {
    //cout << "L'ennemi fuit !\n";
}