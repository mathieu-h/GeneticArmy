#include "DecisionTree/DecisionNode.hpp"

DecisionNode::DecisionNode()
{}

std::unique_ptr<Action> DecisionNode::getValue()
{
    if (m_goToLeftPredicate())
    {
        return n_left->getValue();
    }

    return n_right->getValue();
}