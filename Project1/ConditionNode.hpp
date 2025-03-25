//#include "includes.hpp"
#include "BTNode.hpp"
#include "BlackBoard.hpp"

class ConditionNode : public BTNode {
private:
    Blackboard& blackboard;
    string key;
    int expectedValue;
public:
    ConditionNode(Blackboard& bb, const string& key, int value) : blackboard(bb), key(key), expectedValue(value) {}
    NodeState execute() override {
        return (blackboard.GetValue(key) == expectedValue) ? NodeState::SUCCESS : NodeState::FAILURE;
    }
};
