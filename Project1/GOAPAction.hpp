#ifndef GOAPACTION_HPP
#define GOAPACTION_HPP
#pragma once
#include "includes.hpp"
#include "GOAPState.hpp"

class GOAPAction {
public:
    virtual bool CanExecute(const GOAPState& state) = 0;
    virtual void Execute(GOAPState& state) = 0;
    virtual ~GOAPAction() = default;
};

#endif