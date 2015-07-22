#ifndef _ACTIONNODE_H_
#define _ACTIONNODE_H_

#include <memory>
#include "INode.hpp"
#include "Actions/EmptyAction.hpp"
#include "Actions/ShotAction.hpp"
#include "Actions/MoveAction.hpp"
#include "Extractors/ExtractorBuilder.hpp"

class ActionNode : public INode
{
public:
	ActionNode(std::stringstream& code){
		code >> actionType;
		// On créé l'extracteur ici afin de 'consommer' le code
		if (actionType == 'M'){
			extractorPoint = ExtractorBuilder::getInstance().buildPointExtractor(code);
		}
		else if (actionType == 'E'){
			extractorPoint = ExtractorBuilder::getInstance().buildPointExtractor(code);
		}
		else if (actionType == 'A'){
			extractorUnit = ExtractorBuilder::getInstance().buildUnitExtractor(code);
		}
	}

	u_ptr<Action> getValue(Unit& unit, Army& allies, Army& opponents){
		if (actionType == 'M'){
			return u_ptr<Action>(new MoveAction(unit, extractorPoint->get(unit, allies, opponents)));
		}
		else if (actionType == 'E'){
			Point p = (2 * unit.getPosition()) - extractorPoint->get(unit, allies, opponents);
			return u_ptr<Action>(new MoveAction(unit, 1000 * p));
		}
		else if (actionType == 'A'){
			if (unit.getFirerate().canShoot()){
				Unit target = extractorUnit->get(unit, allies, opponents);
				if (target.getPosition().distance(unit.getPosition())>unit.getRange().getValue())
				{
					return std::unique_ptr<Action>(new MoveAction(unit, target.getPosition()));
				}
				else
				{
					return std::unique_ptr<Action>(new ShotAction(unit, target));
				}
			}
			//return u_ptr<Action>(new ShotAction(unit, ));
		}
		else if (actionType == 'N'){
			return u_ptr<Action>(new EmptyAction(unit));
		}
	}

	std::string getCode(){
		if (actionType == 'M'){
			std::stringstream code;
			code << "!" << actionType << extractorPoint->getCode();
			return code.str();
		}
		else if (actionType == 'E'){
			std::stringstream code;
			code << "!" << actionType << extractorPoint->getCode();
			return code.str();
		}
		else if (actionType == 'A'){
			std::stringstream code;
			code << "!" << actionType << extractorUnit->getCode();
			return code.str();
		}
		else if (actionType == 'N'){
			std::stringstream code;
			code << "!" << actionType;
			return code.str();
		}
	}

private:
	u_ptr<Action> _action;
	char actionType;
	u_ptr<Extractor<Point>> extractorPoint;
	u_ptr<Extractor<Unit&>> extractorUnit;
};

#endif //_ACTIONNODE_H_