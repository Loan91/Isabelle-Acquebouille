#ifndef PATROUILLER_HPP
#define PATROUILLER_HPP
#pragma once
#include "includes.hpp"
#include "GOAPAction.hpp"

class Patrouiller : public GOAPAction {
public:
    bool CanExecute(const GOAPState& state) override;
    void Execute(GOAPState& state) override;
};

#endif