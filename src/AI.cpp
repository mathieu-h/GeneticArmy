#include <iostream>
#include <memory>
#include "IA/AI.hpp"


//Parenthesis overloading for applying the AI on the unit provided in parameter
//Return the action which have to be done by the unit in this context
std::unique_ptr<Action> AI::operator()(Unit& unit, Army& allies, Army& opponents)
{
    try {
		// Intégrer la logique de la nouvelle IA
		//
		std::stringstream code;
		code << unit.getIACode();
		// Crée le noeud racine de l'arbre, qui lui va créer l'arbre en appellant getValue() 
		// en cascade
		
		//DecisionNode rootTree = DecisionNode(code);
		//return rootTree.getValue(unit, allies, opponents);
		TreeIA tree = TreeIA(code);
		return tree(unit, allies, opponents);
    }
    catch(std::invalid_argument&)
    {
        //std::cout<<e.what()<<std::endl;
        return std::unique_ptr<Action>(new EmptyAction(unit));
    }
}

/*
DecisionNode& generateDecisionTreeRoot(std::string& code){
	//DecisionNode 
	//return ;
	return DecisionNode(code);
}*/