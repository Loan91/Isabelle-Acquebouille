#ifndef SUIVRE_HPP
#define SUIVRE_HPP
#pragma once
#include "includes.hpp"
#include "GOAPAction.hpp"

class Suivre : public GOAPAction {
public:
    bool CanExecute(const GOAPState& state) override;
    void Execute(GOAPState& state) override;
};

#endif