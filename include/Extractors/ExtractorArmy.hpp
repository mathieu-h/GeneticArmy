#ifndef _EXTRACTORARMY_H_
#define _EXTRACTORARMY_H_
#pragma once
#include "Extractor.hpp"



class ExtractorA : public Extractor<ArmyVec>
{
private:
public:
	ExtractorA(){};
	~ExtractorA();
	ArmyVec get(Unit& currentUnit, Army& ally, Army& opp){
		ArmyVec& vUnit = ally.getUnitsList();
		return vUnit;
	}
	std::string getCode(){
		return "A";
	}
};

class ExtractorO : public Extractor<ArmyVec>
{
private:
public:
	ExtractorO(){};
	~ExtractorO();
	ArmyVec get(Unit& currentUnit, Army& ally, Army& opp){
		return opp.getUnitsList();
	}
	std::string getCode(){
		return "O";
	}
};

class ExtractorNL : public Extractor<ArmyVec>
{
private:
	int _index;
	// TODO remplacer les numU par des extracteurs de valeurs directs
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<ArmyVec>> _eA;
public:
	ExtractorNL(int index, u_ptr<Extractor<float>>& eV, u_ptr<Extractor<ArmyVec>>& eA) : _index(index), _eV(std::move(eV)), _eA(std::move(eA)){};
	~ExtractorNL();

	/*
	bool greaterThan(Unit* unit, Unit* unit2){
		return unit->getCapacity(_index) < unit2->getCapacity(_index);
	}*/

	ArmyVec get(Unit& currentUnit, Army& ally, Army& opp){
		int index = _index;
		ArmyVec& vUnit = _eA->get(currentUnit, ally, opp);
		int numU = _eV->get(currentUnit, ally, opp);
		
		if (numU > vUnit.size()){
			return vUnit;
		}

		std::nth_element(vUnit.begin(), vUnit.begin() + numU, vUnit.end(),
			[index](s_ptr<Unit>& a, s_ptr<Unit>& b){return a->getCapacity(index) < b->getCapacity(index); });
		ArmyVec nVUnit(vUnit.begin(), vUnit.begin() + numU);
		return nVUnit;
		//return nVUnit;
	}

	std::string getCode(){
		std::stringstream code;
		code << "NL" << _index << _eV->getCode() << _eA->getCode();
		return code.str();
	}
};

class ExtractorNH : public Extractor<ArmyVec>
{
private:
	int _index;
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<ArmyVec>> _eA;
public:
	ExtractorNH(int index, u_ptr<Extractor<float>>& eV, u_ptr<Extractor<ArmyVec>>& eA) : _index(index), _eV(std::move(eV)), _eA(std::move(eA)){};
	~ExtractorNH();
	ArmyVec get(Unit& currentUnit, Army& ally, Army& opp){
		int index = _index;
		ArmyVec& vUnit = _eA->get(currentUnit, ally, opp);
		float numU = _eV->get(currentUnit, ally, opp);
		
		if (numU > vUnit.size()){
			return vUnit;
		}

		std::nth_element(vUnit.begin(), vUnit.begin() + numU, vUnit.end(),
			[index](s_ptr<Unit>& a, s_ptr<Unit>& b){return a->getCapacity(index) > b->getCapacity(index); });
		ArmyVec nVUnit(vUnit.begin(), vUnit.begin() + numU);
		return nVUnit;
	}

	std::string getCode(){
		std::stringstream code;
		code << "NH" << _index << _eV->getCode() << _eA->getCode();
		return code.str();
	}
};


class ExtractorNLD : public Extractor<ArmyVec>
{
private:
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<ArmyVec>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorNLD(u_ptr<Extractor<float>>& eV, u_ptr<Extractor<ArmyVec>>& eA, u_ptr<Extractor<Point>>& eP) : _eV(std::move(eV)), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorNLD();
	ArmyVec get(Unit& currentUnit, Army& ally, Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		ArmyVec& vUnit = _eA->get(currentUnit, ally, opp);
		float numU = _eV->get(currentUnit, ally, opp);

		if (numU > vUnit.size()){
			return vUnit;
		}

		std::nth_element(vUnit.begin(), vUnit.begin() + numU, vUnit.end(),
			[p](s_ptr<Unit>& a, s_ptr<Unit>& b){return a->getPosition().distance(p) < b->getPosition().distance(p); });
		ArmyVec nVUnit(vUnit.begin(), vUnit.begin() + numU);
		return nVUnit;
	}

	std::string getCode(){
		std::stringstream code;
		code << "NLD" << _eV->getCode() << _eA->getCode() << _eP->getCode();
		return code.str();
	}
};

class ExtractorNHD : public Extractor<ArmyVec>
{
private:
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<ArmyVec>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorNHD(u_ptr<Extractor<float>>& eV, u_ptr<Extractor<ArmyVec>>& eA, u_ptr<Extractor<Point>>& eP) : _eV(std::move(eV)), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorNHD();
	ArmyVec get(Unit& currentUnit, Army& ally, Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		ArmyVec& vUnit = _eA->get(currentUnit, ally, opp);
		float numU = _eV->get(currentUnit, ally, opp);
		if (numU > vUnit.size()){
			return vUnit;
		}

		std::nth_element(vUnit.begin(), vUnit.begin() + numU, vUnit.end(),
			[p](s_ptr<Unit>& a, s_ptr<Unit>& b){return a->getPosition().distance(p) > b->getPosition().distance(p); });
		ArmyVec nVUnit(vUnit.begin(), vUnit.begin() + numU);
		return nVUnit;
	}

	std::string getCode(){
		std::stringstream code;
		code << "NHD" << _eV->getCode() << _eA->getCode() << _eP->getCode();
		return code.str();
	}
};

class ExtractorTL : public Extractor<ArmyVec>
{
private:
	int _index;
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<ArmyVec>> _eA;
public:
	ExtractorTL(int index, u_ptr<Extractor<float>>& eV, u_ptr<Extractor<ArmyVec>>& eA) : _index(index), _eV(std::move(eV)), _eA(std::move(eA)){};
	~ExtractorTL();
	ArmyVec get(Unit& currentUnit, Army& ally, Army& opp){
		ArmyVec& vUnit = _eA->get(currentUnit, ally, opp);
		ArmyVec nVUnit(vUnit.size());
		int index = _index;
		float treshold = _eV->get(currentUnit, ally, opp);
		auto it = std::copy_if(vUnit.begin(), vUnit.end(), nVUnit.begin(), [&index, &treshold](s_ptr<Unit>& a){return a->getCapacity(index)->getValue() < treshold; });
		nVUnit.resize(std::distance(nVUnit.begin(), it));
		return nVUnit;
	}	
	
	std::string getCode(){
		std::stringstream code;
		code << "TL" << _index << _eV->getCode() << _eA->getCode();
		return code.str();
	}
};

class ExtractorTH : public Extractor<ArmyVec>
{
private:
	int _index;
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<ArmyVec>> _eA;
public:
	ExtractorTH(int index, u_ptr<Extractor<float>>& eV, u_ptr<Extractor<ArmyVec>>& eA) : _index(index), _eV(std::move(eV)), _eA(std::move(eA)){};
	~ExtractorTH();
	ArmyVec get(Unit& currentUnit, Army& ally, Army& opp){
		ArmyVec& vUnit = _eA->get(currentUnit, ally, opp);
		ArmyVec nVUnit(vUnit.size());
		int index = _index;
		float treshold = _eV->get(currentUnit, ally, opp);
		auto it = std::copy_if(vUnit.begin(), vUnit.end(), nVUnit.begin(), [&index, &treshold](s_ptr<Unit>& a){return a->getCapacity(index)->getValue() > treshold; });
		nVUnit.resize(std::distance(nVUnit.begin(), it));
		return nVUnit;
	}

	std::string getCode(){
		std::stringstream code;
		code << "TH" << _index << _eV->getCode() << _eA->getCode();
		return code.str();
	}
};


class ExtractorTLD : public Extractor<ArmyVec>
{
private:
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<ArmyVec>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorTLD(u_ptr<Extractor<float>>& eV, u_ptr<Extractor<ArmyVec>>& eA, u_ptr<Extractor<Point>>& eP) : _eV(std::move(eV)), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorTLD();
	ArmyVec get(Unit& currentUnit, Army& ally, Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		ArmyVec& vUnit = _eA->get(currentUnit, ally, opp);
		ArmyVec nVUnit(vUnit.size());

		float treshold = _eV->get(currentUnit, ally, opp);
		auto it = std::copy_if(vUnit.begin(), vUnit.end(), nVUnit.begin(), [&p, &treshold](s_ptr<Unit>& a){return a->getPosition().distance(p) < treshold; });
		nVUnit.resize(std::distance(nVUnit.begin(), it));
		return nVUnit;
	}

	std::string getCode(){
		std::stringstream code;
		code << "TLD" << _eV->getCode() << _eA->getCode() << _eP->getCode();
		return code.str();
	}
};

class ExtractorTHD : public Extractor<ArmyVec>
{
private:
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<ArmyVec>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorTHD(u_ptr<Extractor<float>>& eV, u_ptr<Extractor<ArmyVec>>& eA, u_ptr<Extractor<Point>>& eP) : _eV(std::move(eV)), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorTHD();
	ArmyVec get(Unit& currentUnit, Army& ally, Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		ArmyVec& vUnit = _eA->get(currentUnit, ally, opp);
		ArmyVec nVUnit(vUnit.size());

		float treshold = _eV->get(currentUnit, ally, opp);
		auto it = std::copy_if(vUnit.begin(), vUnit.end(), nVUnit.begin(), [&p, &treshold](s_ptr<Unit>& a){return a->getPosition().distance(p) > treshold; });
		nVUnit.resize(std::distance(nVUnit.begin(), it));
		return nVUnit;
	}

	std::string getCode(){
		std::stringstream code;
		code << "THD" << _eV->getCode() << _eA->getCode() << _eP->getCode();
		return code.str();
	}
};

#endif //_EXTRACTORARMY_H_