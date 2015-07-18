#ifndef _AI_HPP_
#define _AI_HPP_
#include <memory>
#include "Actions/Action.hpp"
#include "Unit.hpp"
#include "Army.hpp"
#include "DecisionTree/DecisionNode.hpp"
#include "DecisionTree/ActionNode.hpp"
#include "IA/TreeIA.hpp"
#include "Actions/Action.hpp"
#include "Actions/MoveAction.hpp"
#include "Actions/ShotAction.hpp"
#include "Actions/EmptyAction.hpp"

//class representing an Artificial Intelligence
class AI {
public:

    //Parenthesis overloading for applying the AI on the unit provided in parameter
    //Return the action which have to be done by the unit in this context
    std::unique_ptr<Action> operator()(Unit& unit, Army& allies, Army& opponents);
	//DecisionNode& generateDecisionTreeRoot(std::string code);

};


#endif