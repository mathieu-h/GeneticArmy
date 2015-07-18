#ifndef _NODEBUILDER_H_
#define _NODEBUILDER_H_

#include <string>     
#include <iostream> 
#include <sstream>
#include "Extractors/Extractor.hpp"
#include "DecisionTree/INode.hpp"
#include "DecisionTree/DecisionNode.hpp"
#include "DecisionTree/ActionNode.hpp"

class NodeBuilder
{
private:
	//static ExtractorBuilder* instance;		
	//ExtractorBuilder(ExtractorBuilder const&); // Don't Implement.
	//void operator=(ExtractorBuilder const&); // Don't implement
	NodeBuilder(){};
	~NodeBuilder(){};

public:
	static NodeBuilder& getInstance(){
		//if (instance == nullptr){
		//	instance = new ExtractorBuilder();
		//}
		static NodeBuilder instance;
		return instance;
	}

	u_ptr<INode> createNode(std::stringstream& code){
		char c;
		code >> c;
		if (c == '!'){
			return u_ptr<INode>(new ActionNode(code));
		}
		else if (c == '?'){
			//return u_ptr<INode>(new DecisionNode(code));
		}
		//return 
	}
};
#endif