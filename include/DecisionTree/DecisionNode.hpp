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
    std::unique_ptr<Action> getValue();
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

	bool chooseChildNode(){
		// Parser le code du node en deux sous codes (détecter le '<' ou '>')
		// Remove the '?' element from the stringsteam
		char s;
		code >> s;
		// Extract the code of the first child
		std::string strFull = code.str();
		std::vector<std::string> strs;
		boost::split(strs, strFull, boost::is_any_of("?!<>"));
		std::string firstChildCode = strs.at(1);
		std::string secondChildCode = strs.at(2);
		std::stringstream firstChildSS;
		std::stringstream secondChildSS;
		firstChildSS << firstChildCode;
		secondChildSS << secondChildCode;
		// Créer les extracteurs correspondants et comparer leurs valeurs de retour avec le '<' ou '>'
		// Se diriger vers le fils correspondant
		//std::stringstream subcode1 = code
		//Extractor 
		std::string army = "AONT";
		std::string point = "BP";
		std::string unit = "ULH";
		std::string value = "CDMma";
		float valueEx = 0.0f;
		//if (army.find(firstchildcode[0]) != std::string::npos)
		//	extractorbuilder::getinstance()->buildarmyextractor(firstchildss)->get();
		//if (point.find(firstchildcode[0]) != std::string::npos)
		//	extractorbuilder::getinstance()->buildpointextractor(firstchildss)->get();
		//if (unit.find(firstchildcode[0]) != std::string::npos)
		//	extractorbuilder::getinstance()->buildunitextractor(firstchildss)->get();
		//if (value.find(firstchildcode[0]) != std::string::npos)
		//	extractorbuilder::getinstance()->buildvalueextractor(firstchildss)->get();

		//std::stringstream subcode2 = code
	}
};

#endif //_DECISIONNODE_H_