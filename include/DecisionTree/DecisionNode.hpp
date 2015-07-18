#ifndef _DECISIONNODE_H_
#define _DECISIONNODE_H_

#include <memory>
#include <functional>

#include "INode.hpp"
#include "Extractors/Extractor.hpp"
#include "Extractors/ExtractorBuilder.hpp"
#include "ActionNode.hpp"
#include "Army.hpp"
#include "boost/algorithm/string.hpp"
#include <boost/algorithm/string/predicate.hpp>


class DecisionNode : INode
{
public:
    DecisionNode();
	std::unique_ptr<Action> getValue(const Unit& unit, const Army& allies, const Army& opponents);
protected:
    std::unique_ptr<INode> n_left;
    std::unique_ptr<INode> n_right;
    ///**
    // * Prédicat de choix récupération valeur de droite ou de gauche
    // */
    //std::function<bool()> m_goToLeftPredicate;
    ///** Ou simplement une méthode vituel pur qui devra être redéfini par les class héritant de décision Node*/
    //virtual bool operator()() = 0;
    ///* Voir le plus simple */

	bool chooseChildNode(const Unit& currUnit, const Army& allies, const Army& opponents){
		// Parser le code du node en deux sous codes (détecter le '<' ou '>')
		// Remove the '?' element from the stringsteam
		char s;
		code >> s;
		// Extract the code of the first child
		std::string strFull = code.str();
		std::vector<std::string> strs;
		boost::split(strs, strFull, boost::is_any_of("?!<>"));
		std::string leftPred = strs.at(1);
		std::string rightPred = strs.at(2);
		std::stringstream leftPredSS;
		std::stringstream rightPredSS;
		leftPredSS << leftPred;
		rightPredSS << rightPred;
		// Créer les extracteurs correspondants et comparer leurs valeurs de retour avec le '<' ou '>'
		// Se diriger vers le fils correspondant
		// std::stringstream subcode1 = code
		// Extractor  
		std::string army = "AONT";
		std::string point = "BP";
		std::string unit = "ULH";
		std::string value = "CDMma";
		float valueExLeft = 0.0f;
		if (army.find(leftPred[0]) != std::string::npos)
			ExtractorBuilder::getInstance()->buildArmyExtractor(leftPredSS)->get(currUnit, allies, opponents);
		else if (point.find(leftPred[0]) != std::string::npos)
			ExtractorBuilder::getInstance()->buildPointExtractor(leftPredSS)->get(currUnit, allies, opponents);
		else if (unit.find(leftPred[0]) != std::string::npos)
			ExtractorBuilder::getInstance()->buildUnitExtractor(leftPredSS)->get(currUnit, allies, opponents);
		else if (value.find(leftPred[0]) != std::string::npos)
			ExtractorBuilder::getInstance()->buildValueExtractor(leftPredSS)->get(currUnit, allies, opponents);

		//std::stringstream subcode2 = code
	}
};

#endif //_DECISIONNODE_H_