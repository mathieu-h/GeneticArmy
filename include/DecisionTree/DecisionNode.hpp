#pragma once

#include <memory>
#include <functional>

#include "INode.hpp"
#include "Extractors/Extractor.hpp"
#include "Extractors/ExtractorBuilder.hpp"
#include "NodeBuilder.hpp"
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
		_nLeft = NodeBuilder::getInstance().getInstance().createNode(code);
		_nRight = NodeBuilder::getInstance().getInstance().createNode(code);
	}
	~DecisionNode();
	
	u_ptr<Action> getValue(Unit& unit, Army& allies, Army& opponents){
		// Assuming comparator will always be '<' => rule to be defined in the IACode generator
		return _extractorLeft->get(unit, allies, opponents) < _extractorRight->get(unit, allies, opponents) ? _nLeft->getValue(unit, allies, opponents) : _nRight->getValue(unit, allies, opponents);
	}

private:
	u_ptr <Extractor<float>> _extractorLeft;
	u_ptr <Extractor<float>> _extractorRight;
	std::string _comparator;
	u_ptr<INode> _nLeft;
	u_ptr<INode> _nRight;
};


