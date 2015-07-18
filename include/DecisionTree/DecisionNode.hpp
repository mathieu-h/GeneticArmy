#ifndef _DECISIONNODE_H_
#define _DECISIONNODE_H_

#include <memory>
#include <functional>

#include "INode.hpp"
#include "Extractors/Extractor.hpp"
#include "Extractors/ExtractorBuilder.hpp"
#include "NodeBuilder.hpp"
#include "ActionNode.hpp"
#include "Army.hpp"
#include "boost/algorithm/string.hpp"
#include <boost/algorithm/string/predicate.hpp>


class DecisionNode : public INode
{
public:

	DecisionNode(std::stringstream& code/*, u_ptr<INode>& n_left, u_ptr<INode>& n_right*/){
		//_n_left = std::move(n_left);
		//_n_right = std::move(n_right);
		//generateChildren(code);
		_extractorLeft = ExtractorBuilder::getInstance().buildValueExtractor(code);
		code >> _comparator;
		_extractorRight = ExtractorBuilder::getInstance().buildValueExtractor(code);
		_nLeft = NodeBuilder::getInstance().getInstance().createNode(code);
		_nRight = NodeBuilder::getInstance().getInstance().createNode(code);
	};

	u_ptr<Action> getValue(Unit& unit, Army& allies, Army& opponents){
		//return chooseChildNode(unit, allies, opponents) ? _n_left->getValue(unit, allies, opponents) : _n_right->getValue(unit, allies, opponents);

	}

private:
	u_ptr <Extractor<float>> _extractorLeft;
	u_ptr <Extractor<float>> _extractorRight;
	std::string _comparator;
    u_ptr<INode> _nLeft = nullptr;
	u_ptr<INode> _nRight = nullptr;
};


/*
// true => left , false => right
bool chooseChildNode(const Unit& currUnit, const Army& allies, const Army& opponents){
// Parser le code du node en deux sous codes (détecter le '<' ou '>')
// Extract the code of the first child
std::string strFull = _code;
std::vector<std::string> strs;
boost::split(strs, strFull, boost::is_any_of("?!<"));
std::string leftPred = strs.at(1);
std::string rightPred = strs.at(2);
// Conversion des string retournées par boost en stringstream pour les passer au builder d'extracteurs
std::stringstream leftPredSS;
std::stringstream rightPredSS;
leftPredSS << leftPred;
rightPredSS << rightPred;

// Créer les extracteurs correspondants et comparer leurs valeurs de retour avec le '<' ou '>' => Se diriger vers le fils correspondant
// Extracteurs gauche et droit
float valueExLeft = ExtractorBuilder::getInstance().buildValueExtractor(leftPredSS)->get(currUnit, allies, opponents);
float valueExRight = ExtractorBuilder::getInstance().buildValueExtractor(rightPredSS)->get(currUnit, allies, opponents);
return valueExLeft < valueExRight;
}
*/

/* Détermination de l'extracteur à créer en fonction du premier caractère
std::string army = "AONT";
std::string point = "BP";
std::string unit = "ULH";
std::string value = "CDMma";

if (army.find(leftPred[0]) != std::string::npos)
valueExLeft = ExtractorBuilder::getInstance()->buildArmyExtractor(leftPredSS)->get(currUnit, allies, opponents);
else if (point.find(leftPred[0]) != std::string::npos)
valueExLeft = ExtractorBuilder::getInstance()->buildPointExtractor(leftPredSS)->get(currUnit, allies, opponents);
else if (unit.find(leftPred[0]) != std::string::npos)
valueExLeft = ExtractorBuilder::getInstance()->buildUnitExtractor(leftPredSS)->get(currUnit, allies, opponents);
else if (value.find(leftPred[0]) != std::string::npos)
*/

// Récupération du comparateur (toujours situé un cran apres le leftpredicate)
// PAS BESOIN EN FAIT CAR LE COMPARATEUR SERA TOUJOURS < 
// char comp = strFull[leftPred.size() + 1];

#endif //_DECISIONNODE_H_