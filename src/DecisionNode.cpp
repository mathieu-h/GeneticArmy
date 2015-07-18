#include "DecisionTree/DecisionNode.hpp"

DecisionNode::DecisionNode()
{}

std::unique_ptr<Action> DecisionNode::getValue(const Unit& unit, const Army& allies, const Army& opponents)
{
   // if (m_goToLeftPredicate())
   // {
   //     return n_left->getValue();
   // }

	return n_right->getValue(unit, allies, opponents);
}