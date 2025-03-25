#ifndef GOAPPLANNER_HPP
#define GOAPPLANNER_HPP
#pragma once
#include "includes.hpp"
#include "GOAPState.hpp"
#include "GOAPAction.hpp"

enum class Goal { Patrouiller, Suivre, Attaquer, Fuir };

class GOAPPlanner {
public:
    vector<GOAPAction*> Plan(GOAPState& state, Goal goal);
};

#endif