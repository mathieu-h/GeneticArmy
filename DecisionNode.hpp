#ifndef _DECISIONNODE_H_
#define _DECISIONNODE_H_
#include <memory>
#include <functional>

#include "DecisionTree/INode.hpp"
#include "Extractors/Extractor.hpp"
#include "Extractors/ExtractorBuilder.hpp"
#include "DecisionTree/NodeBuilder.hpp"
#include "Army.hpp"
#include "boost/algorithm/string.hpp"
#include <boost/algorithm/string/predicate.hpp>


class DecisionNode : public INode
{
public:

	DecisionNode(std::stringstream& code){
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
		return _extractorLeft->get(unit, allies, opponents) < _extractorRight->get(unit, allies, opponents) ? _nLeft->getValue(unit, allies, opponents) : _nRight->getValue(unit, allies, opponents);
	}

private:
	u_ptr <Extractor<float>> _extractorLeft;
	u_ptr <Extractor<float>> _extractorRight;
	std::string _comparator;
	u_ptr<INode> _nLeft;
	u_ptr<INode> _nRight;
};
#endif 


