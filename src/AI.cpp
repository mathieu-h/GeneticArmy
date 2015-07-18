#include <iostream>
#include <memory>

#include "IA/AI.hpp"
#include "Actions/Action.hpp"
#include "Actions/MoveAction.hpp"
#include "Actions/ShotAction.hpp"
#include "Actions/EmptyAction.hpp"
#include "Unit.hpp"
#include "Army.hpp"

//Parenthesis overloading for applying the AI on the unit provided in parameter
//Return the action which have to be done by the unit in this context
std::unique_ptr<Action> AI::operator()(Unit& unit, Army& allies, Army& opponents)
{
    try {
		// Int�grer la logique de la nouvelle IA
		//

		return std::unique_ptr<Action>(new EmptyAction(unit));
    }
    catch(std::invalid_argument&)
    {
        //std::cout<<e.what()<<std::endl;
        return std::unique_ptr<Action>(new EmptyAction(unit));
    }
}
