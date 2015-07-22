#ifndef _EXTRACTORVALUE_H_
#define _EXTRACTORVALUE_H_
#pragma once
#include "Extractor.hpp"

class ExtractorDirect : public Extractor<float>
{
private:
	int _value;
public:
	ExtractorDirect(int value): _value(value){};
	~ExtractorDirect();
	float get(const Unit& currentUnit, Army& ally, Army& opp){
		return _value;
	}

	std::string getCode(){
		std::stringstream ss;
		ss << "[" << _value << "]";
		return ss.str();
	}
};


class ExtractorC : public Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<Unit>> _eU;
public:
	ExtractorC(int index, u_ptr<Extractor<Unit>>& eU) : _index(index), _eU(std::move(eU)){};
	~ExtractorC();
	float get(const Unit& currentUnit, Army& ally, Army& opp){
		return _eU->get(currentUnit, ally, opp).getCapacity(_index)->getValue();
	}

	std::string getCode(){
		std::stringstream code;
		code << "C" << _index << _eU->getCode();
		return code.str();
	}
};

class ExtractorD : public Extractor<float>
{
private:
	u_ptr<Extractor<Unit>> _eU;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorD(u_ptr<Extractor<Unit>>& eU, u_ptr<Extractor<Point>>& eP) :_eU(std::move(eU)), _eP(std::move(eP)){};
	~ExtractorD();
	float get(const Unit& currentUnit, Army& ally, Army& opp){
		return _eU->get(currentUnit, ally, opp).getPosition().distance(_eP->get(currentUnit, ally, opp));
	}

	std::string getCode(){
		std::stringstream code;
		code << "D" << _eU->getCode() << _eP->getCode();
		return code.str();
	}
};


class ExtractorM : public Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<ArmyVec>> _eA;
public:
	ExtractorM(int index, u_ptr<Extractor<ArmyVec>>& eA) : _index(index), _eA(std::move(eA)){};
	~ExtractorM();
	float get(const Unit& currentUnit, Army& ally, Army& opp){
		//return _eA->get(currentUnit, ally, opp).getHigestUnit(_index).getCapacity(_index)->getValue();
		return Army::getHigestUnitS(_index, _eA->get(currentUnit, ally, opp)).getCapacity(_index)->getValue();
	}

	std::string getCode(){
		std::stringstream code;
		code << "M" << _index << _eA->getCode();
		return code.str();
	}
};

class Extractorm : public Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<ArmyVec>> _eA;
public:
	Extractorm(int index, u_ptr<Extractor<ArmyVec>>& eA) : _index(index), _eA(std::move(eA)){};
	~Extractorm();
	float get(const Unit& currentUnit, Army& ally, Army& opp){
		return Army::getLowestUnitS(_index, _eA->get(currentUnit, ally, opp)).getCapacity(_index)->getValue();
	}	
	
	std::string getCode(){
		std::stringstream code;
		code << "m" << _index << _eA->getCode();
		return code.str();
	}
};

class Extractora : public Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<ArmyVec>> _eA;
public:
	Extractora(int index, u_ptr<Extractor<ArmyVec>>& eA) : _index(index), _eA(std::move(eA)){};
	~Extractora();
	float get(const Unit& currentUnit, Army& ally, Army& opp){
		ArmyVec& vUnit = _eA->get(currentUnit, ally, opp);
		
		int index = _index;
		float sum = std::accumulate(vUnit.begin(), vUnit.end(), 
				0, [&index](float a, s_ptr<Unit>& it){return a + it->getCapacity(index)->getValue(); });
		return vUnit.size() == 0 ? 0.0 : sum / vUnit.size();
	}

	std::string getCode(){
		std::stringstream code;
		code << "a" << _index << _eA->getCode();
		return code.str();
	}
};


class ExtractorMD : public Extractor<float>
{
private:
	u_ptr<Extractor<ArmyVec>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorMD(u_ptr<Extractor<ArmyVec>>& eA, u_ptr<Extractor<Point>>& eP) : _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorMD();
	float get(const Unit& currentUnit, Army& ally, Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);

		return Army::getFurthestUnitS(p, _eA->get(currentUnit, ally, opp)).getPosition().distance(p);
		//return _eA->get(currentUnit, ally, opp).getFurthestUnit(p).getPosition().distance(p);
	}	
	
	std::string getCode(){
		std::stringstream code;
		code << "MD" << _eA->getCode() << _eP->getCode();
		return code.str();
	}
};

class ExtractormD : public Extractor<float>
{
private:
	u_ptr<Extractor<ArmyVec>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractormD(u_ptr<Extractor<ArmyVec>>& eA, u_ptr<Extractor<Point>>& eP) : _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractormD();
	float get(const Unit& currentUnit, Army& ally, Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		//return _eA->get(currentUnit, ally, opp).getNearestUnit(p).getPosition().distance(p);
		return  Army::getNearestUnitS(p, _eA->get(currentUnit, ally, opp)).getPosition().distance(p);
	}

	std::string getCode(){
		std::stringstream code;
		code << "mD" << _eA->getCode() << _eP->getCode();
		return code.str();
	}
};

class ExtractoraD : public Extractor<float>
{
private:
	u_ptr<Extractor<ArmyVec>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractoraD(u_ptr<Extractor<ArmyVec>>& eA, u_ptr<Extractor<Point>>& eP) : _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractoraD();
	float get(const Unit& currentUnit, Army& ally, Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		ArmyVec& vUnit = _eA->get(currentUnit, ally, opp);
		float sum = std::accumulate(vUnit.begin(), vUnit.end(),
			0, [&p](float a, s_ptr<Unit>& it){return a + it->getPosition().distance(p); });
		return vUnit.size() == 0 ? 0.0 : sum / vUnit.size();
	}

	std::string getCode(){
		std::stringstream code;
		code << "aD" << _eA->getCode() << _eP->getCode();
		return code.str();
	}
};
#endif // _EXTRACTORVALUE_H_
