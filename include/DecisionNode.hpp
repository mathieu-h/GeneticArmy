#pragma once

#include <memory>
#include <functional>

#include "INode.hpp"
#include "Extractors/ExtractorBuilder.hpp"
#include "ActionNode.hpp"
#include "Army.hpp"
#include "boost/algorithm/string.hpp"
#include <boost/algorithm/string/predicate.hpp>


class DecisionNode : public INode
{
public:

	DecisionNode(std::stringstream& code){
		_extractorLeft = ExtractorBuilder::getInstance().buildValueExtractor(code);
		code >> _comparator;
		_extractorRight = ExtractorBuilder::getInstance().buildValueExtractor(code);
		char c;
		code >> c;
		if (c == '!'){
			_nLeft = u_ptr<INode>(new ActionNode(code));
		}
		else if (c == '?'){
			_nLeft = u_ptr<INode>(new DecisionNode(code));
		}
		code >> c;
		if (c == '!'){
			_nRight = u_ptr<INode>(new ActionNode(code));
		}
		else if (c == '?'){
			_nRight = u_ptr<INode>(new DecisionNode(code));
		}
	}
	~DecisionNode(){};
	
	u_ptr<Action> getValue(Unit& unit, Army& allies, Army& opponents){
		// Assuming comparator will always be '<' => rule to be defined in the IACode generator
		return _extractorLeft->get(unit, allies, opponents) < _extractorRight->get(unit, allies, opponents) ? _nLeft->getValue(unit, allies, opponents) : _nRight->getValue(unit, allies, opponents);
	}

	std::string getCode(){
		std::stringstream code;
		// Easier to debug 
		std::string eLeft = _extractorLeft->getCode();
		std::string eRight = _extractorRight->getCode();
		std::string nLeft = _nLeft->getCode();
		std::string nRight = _nRight->getCode();
		code << "?" << eLeft << _comparator << eRight << nLeft << nRight;
		std::string codeR = code.str();
		// Easier to debug
		//code << "?" << _extractorLeft->getCode() << _comparator << _extractorRight->getCode() << _nLeft->getCode() << _nRight->getCode();
		return codeR;
	}

private:
	u_ptr <Extractor<float>> _extractorLeft;
	u_ptr <Extractor<float>> _extractorRight;
	char _comparator;
	u_ptr<INode> _nLeft;
	u_ptr<INode> _nRight;
};


