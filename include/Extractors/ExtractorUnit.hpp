#ifndef _EXTRACTORUNIT_H_public Extractor<Unit&>
#define _EXTRACTORUNIT_H_
#pragma once
#include "Extractor.hpp"


class ExtractorU : public Extractor<Unit&>
{
private:
public:
	ExtractorU(){};
	~ExtractorU();
	Unit& get(Unit& currentUnit, Army& ally, Army& opp){
		return currentUnit;
	}

	std::string getCode(){
		return "U";
	}
};

class ExtractorL : public Extractor<Unit&>
{
private: 
	int _index;
	u_ptr<Extractor<ArmyVec>> _eA;
public:
	ExtractorL(int index, u_ptr<Extractor<ArmyVec>>& eA) : _index(index),_eA(std::move(eA)){};
	~ExtractorL();
	Unit& get(Unit& currentUnit, Army& ally, Army& opp){
		return Army::getLowestUnitS(_index, _eA->get(currentUnit, ally, opp));
	}

	std::string getCode(){
		std::stringstream code;
		code << "L" << _index << _eA->getCode();
		return code.str();
	}
};

class ExtractorH : public Extractor<Unit&>
{
private:
	int _index;
	u_ptr<Extractor<ArmyVec>> _eA;
public:
	ExtractorH(int index, u_ptr<Extractor<ArmyVec>>& eA) : _index(index), _eA(std::move(eA)){};
	~ExtractorH();
	Unit& get(Unit& currentUnit, Army& ally, Army& opp){
		return Army::getHigestUnitS(_index, _eA->get(currentUnit, ally, opp));
	}	
	
	std::string getCode(){
		std::stringstream code;
		code << "H" << _index << _eA->getCode();
		return code.str();
	}
};

class ExtractorLD : public Extractor<Unit&>
{
private:
	u_ptr<Extractor<ArmyVec>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorLD(u_ptr<Extractor<ArmyVec>>& eA,
		u_ptr<Extractor<Point>>& eP) : _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorLD();
	Unit& get(Unit& currentUnit, Army& ally, Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		return  Army::getNearestUnitS(p, _eA->get(currentUnit, ally, opp));
	}	
	
	std::string getCode(){
		std::stringstream code;
		code << "LD" << _eA->getCode() << _eP->getCode();
		return code.str();
	}
};

class ExtractorHD : public Extractor<Unit&>
{
private:
	u_ptr<Extractor<ArmyVec>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorHD(u_ptr<Extractor<ArmyVec>>& eA,
		u_ptr<Extractor<Point>>& eP) : _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorHD();
	Unit& get(Unit& currentUnit, Army& ally, Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);

		return Army::getFurthestUnitS(p, _eA->get(currentUnit, ally, opp));
	}

	std::string getCode(){
		std::stringstream code;
		code << "HD" << _eA->getCode() << _eP->getCode();
		return code.str();
	}
};
#endif //_EXTRACTORUNIT_H_