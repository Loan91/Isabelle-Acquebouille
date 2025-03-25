#include "GOAPPlanner.hpp"
#include "Suivre.hpp"
#include "Attaquer.hpp"
#include "Fuir.hpp"
#include "Patrouiller.hpp"

vector<GOAPAction*> GOAPPlanner::Plan(GOAPState& state, Goal goal) {
    vector<GOAPAction*> plan;

    if (goal == Goal::Fuir) {
        plan.push_back(new Fuir());
    }
    else if (goal == Goal::Attaquer) {
        plan.push_back(new Attaquer());
    }
    else if (goal == Goal::Suivre) {
        plan.push_back(new Suivre());
    }
    else {
        plan.push_back(new Patrouiller());
    }

    return plan;
}