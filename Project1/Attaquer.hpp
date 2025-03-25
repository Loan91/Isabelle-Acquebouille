#ifndef ATTAQUER_HPP
#define ATTAQUER_HPP
#pragma once
#include "includes.hpp"
#include "GOAPAction.hpp"

class Attaquer : public GOAPAction {
public:
    bool CanExecute(const GOAPState& state) override;
    void Execute(GOAPState& state) override;
};

#endif