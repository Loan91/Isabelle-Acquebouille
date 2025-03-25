#pragma once
#include "includes.hpp"

class Blackboard {
private:
    unordered_map<string, int> data;
public:
    void SetValue(const string& key, int value) {
        data[key] = value;
    }
    int GetValue(const string& key) {
        return data[key];
    }
};