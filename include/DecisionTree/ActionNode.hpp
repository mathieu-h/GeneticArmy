#ifndef _ACTIONNODE_H_
#define _ACTIONNODE_H_

#include <memory>
#include "INode.hpp"
#include "Actions/EmptyAction.hpp"

class ActionNode : public INode
{
public:
	ActionNode(std::stringstream& code){
		
	}

	u_ptr<Action> getValue(Unit& unit, Army& allies, Army& opponents){
		return u_ptr<Action>(new EmptyAction(unit));
	}
};

#endif //_ACTIONNODE_H_