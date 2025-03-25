#ifndef FUIR_HPP
#define FUIR_HPP
#pragma once
#include "includes.hpp"
#include "GOAPAction.hpp"

class Fuir : public GOAPAction {
public:
    bool CanExecute(const GOAPState& state) override;
    void Execute(GOAPState& state) override;
};

#endif