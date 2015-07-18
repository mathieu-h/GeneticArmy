#ifndef _TREEIA_H_
#define _TREEIA_H_

#include <memory>
#include <string>

#include "Actions/Action.hpp"
#include "Army.hpp"
#include "DecisionTree/DecisionNode.hpp"
#include "DecisionTree/ActionNode.hpp"
class TreeIA
{
public:
    /**
     * Compute a decision tree with codeIa passed in constructor
     */
	TreeIA(std::stringstream& codeIA){
		treeRoot = NodeBuilder::getInstance().createNode(codeIA);
	}

    /**
     * Return the action computed by the decision tree
     */
	std::unique_ptr<Action> operator()(Unit& unit, Army& allies, Army& opponents){
		return treeRoot->getValue(unit, allies, opponents);
	}
private:
	u_ptr<INode> treeRoot;
};

/*
std::vector<std::string> vecstr;
boost::split(vecstr, codeIA, boost::is_any_of("?!"));
std::stringstream strs;
strs << codeIA;
char cc;
strs >> cc;
std::string currentCode;
while (cc != '?' && cc != '!'){
currentCode.push_back(cc);
}
treeRoot = u_ptr<DecisionNode>(new DecisionNode(codeIA));*/

//u_ptr<INode>& createLeftChild(std::stringstream& codeIA){
//	char cc;
//	codeIA >> cc;
//	if (cc == '?'){

//	}
//}

//DecisionNode& generateRootTree();

/*
//std::string leftPred = strs.at(1);
//std::string rightPred = strs.at(2);
u_ptr<INode> lastDecisionNode = nullptr;
for (std::vector<std::string>::iterator it = strs.begin(); it != strs.end(); ++it){
std::string codeD = *it;
++it;
std::string actions = "MEAN";
u_ptr<INode> leftChild;
if (actions.find(it[0]) != std::string::npos){
leftChild = u_ptr<INode>(new ActionNode(*it));
}
else{
//rightChild = u_ptr<INode>(new DecisionNode());
}
u_ptr<INode> rightChild;
if (actions.find(it[0]) != std::string::npos){
leftChild = u_ptr<INode>(new ActionNode(*it));
}
else{

}
//lastDecisionNode = u_ptr<INode>(new DecisionNode(*it, leftChild, );
}
*/

#endif //