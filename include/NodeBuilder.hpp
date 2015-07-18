#pragma once
#include <string>     
#include <iostream> 
#include <sstream>
#include "INode.hpp"
#include "DecisionNode.hpp"
#include "ActionNode.hpp"


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

		//return 
	}
};