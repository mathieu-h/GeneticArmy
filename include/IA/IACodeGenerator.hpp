#pragma once

#include <string>     
#include <iostream> 
#include <sstream>
#include <vector>

#define NB_CAPACITY 7

class IACodeGenerator
{
private:
	//static ExtractorBuilder* instance;		
	//ExtractorBuilder(ExtractorBuilder const&); // Don't Implement.
	//void operator=(ExtractorBuilder const&); // Don't implement
	IACodeGenerator(){};
	~IACodeGenerator(){};
	int _maxTreeLength = 4;
	int _sizecounter;

public:
	static IACodeGenerator& getInstance(){
		//if (instance == nullptr){
		//	instance = new ExtractorBuilder();
		//}
		static IACodeGenerator instance;
		return instance;
	}
	void setMaxTreeLength(int maxLength){ _maxTreeLength = maxLength; };
	
	std::string GenerateIACode(){

		std::string newIACode;
		_sizecounter = _maxTreeLength;
		while (_sizecounter > 0){
			newIACode.append(GenerateIACodeDecisionNode());
		}

		return newIACode;
	}

	float GenerateIACodeRandomIndex(){
		return rand() % NB_CAPACITY;
	}

	float GenerateIACodeRandomValue(){
		return float((rand() % 100) + (rand() % (1600 - 1200)) / 10.0);
	}

	std::string GenerateIACodeDecisionNode(){
		if (_sizecounter == 0) return GenerateIACodeActionNode();
		_sizecounter-=1;
		std::string firstChild;
		std::string secondChild;
		int dice = rand() % 2;
		if (dice){
			firstChild = GenerateIACodeActionNode();
		}
		else{
			firstChild = GenerateIACodeDecisionNode();
		}
		dice = rand() % 2;
		if (dice){
			secondChild = GenerateIACodeActionNode();
		}
		else{
			secondChild = GenerateIACodeDecisionNode();
		}
		return "?" + GenerateIACodeValueExtractor() + "<" + GenerateIACodeValueExtractor() + firstChild + secondChild ;
	}

	std::string GenerateIACodeActionNode(){
		std::vector<std::string> arr = { "M", "E", "A", "N"};
		std::stringstream actionNodeCode("");
		int dice = rand() % arr.size();

		actionNodeCode << "!";
		switch (dice){
		case 0:
		case 1:
		{
			std::string pointCode = GenerateIACodePointExtractor();
			actionNodeCode << arr[dice] << pointCode;
			break;
		}
		case 2:
		{
			std::string unitCode = GenerateIACodeUnitExtractor();
			actionNodeCode << arr[dice] << unitCode;
			break;
		}
		case 3:
		{
			actionNodeCode << arr[dice];
			break;
		}
		default:
			break;
		}

		return actionNodeCode.str();
	}
		
	std::string GenerateIACodeArmyExtractor(){
		std::vector<std::string> arr = { "A", "O", "NL", "NH", "TL", "TH", "NLD", "NHD", "TLD", "THD"};
		std::stringstream armyCode("");
		//int dice = rand() % arr.size()-6;
		int diceDirectArmy = rand() % 3;
		int dice;
		if (diceDirectArmy < 2){
			dice = diceDirectArmy;
		}
		else{
			dice = rand() % arr.size();
		}

		//dice = rand() % arr.size()+2;
		//if (dice > arr.size()) dice -= arr.size();
		switch (dice){
		case 0:
		case 1:
			armyCode << std::string(arr[dice]);
			//armyCode << "tamer";
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		{
			std::string armyCodeR = GenerateIACodeArmyExtractor();
			armyCode << arr[dice] << GenerateIACodeRandomIndex() << "[" << GenerateIACodeRandomValue() << "]" << armyCodeR;
			break;
		}
		case 6:
		case 7:
		case 8:
		case 9:
		{
			std::string armyCodeR = GenerateIACodeArmyExtractor();
			std::string pointCode = GenerateIACodePointExtractor();
			armyCode << arr[dice] << "[" << GenerateIACodeRandomValue() << "]" << armyCodeR << pointCode;
			break;
		}
		default:
			break;
		}
		return armyCode.str();
	}

	std::string GenerateIACodeUnitExtractor(){
		std::vector<std::string> arr = { "U", "H", "L", "HD", "LD" };
		std::stringstream unitCode("");
		int dice = rand() % arr.size();

		switch (dice){
		case 0:
			unitCode << arr[dice];
			break;
		case 1:
		case 2:
		{
			std::string armyCode = GenerateIACodeArmyExtractor();
			unitCode << arr[dice] << GenerateIACodeRandomIndex() << armyCode;
			break;
		}
		case 3:
		case 4:
		{
			std::string armyCodeR = GenerateIACodeArmyExtractor();
			std::string pointCode = GenerateIACodePointExtractor();
			unitCode << arr[dice] << armyCodeR << pointCode;
			break;
		}
		default:
			break;
		}
		return unitCode.str();
	}

	std::string GenerateIACodeValueExtractor(/*bool firstEx*/){
		std::vector<std::string> arr = { "[val]", "C", "D", "M", "m", "a", "MD", "mD", "aD" };
		std::stringstream valueCode("");
		//std::cout << arr.size() << std::endl;
		int dice = rand() % arr.size();

		switch (dice){
		case 0:
		{
			// Generates random value between 0 and 99 with one decimal
			valueCode << "[" << GenerateIACodeRandomValue() << "]" /*<< GenerateIACodeUnitExtractor()*/;
			break;
		}
		case 1:
		{
			std::string unitCode = GenerateIACodeUnitExtractor();
			valueCode << arr[dice] << GenerateIACodeRandomIndex() << unitCode;
			break;
		}
		case 2:
		{
			std::string unitCode = GenerateIACodeUnitExtractor();
			std::string pointCode = GenerateIACodePointExtractor();
			valueCode << arr[dice] << unitCode << pointCode;
			break;
		}
		case 3:
		case 4:
		case 5:
		{
			std::string armyCode = GenerateIACodeArmyExtractor();
			valueCode << arr[dice] << GenerateIACodeRandomIndex() << armyCode;
			break;
		}
		case 6: 
		case 7:
		case 8:
		{
			std::string armyCode = GenerateIACodeArmyExtractor();
			std::string pointCode = GenerateIACodePointExtractor();
			valueCode << arr[dice] << armyCode << pointCode;
			break;
		}
		default:
			break;
		}
		std::string codeString(valueCode.str());
		return codeString;
		//return valueCode.str();
	}

	std::string GenerateIACodePointExtractor(){
		std::string pointCodes("PB");
		std::string pointCode("");
		int dice = rand() % pointCodes.size();
		
		if (dice){
			std::string unitCode = GenerateIACodeUnitExtractor();
			pointCode.append("P" + unitCode);
		}
		else{
			std::string armyCode = GenerateIACodeArmyExtractor();
			pointCode.append("B" + armyCode);
		}
		//std::string codeString(pointCode.str());
		return pointCode;
	}
};