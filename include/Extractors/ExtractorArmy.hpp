#ifndef _EXTRACTORARMY_H_
#define _EXTRACTORARMY_H_
#pragma once
#include "Extractor.hpp"

class ExtractorA : public Extractor<Army>
{
private:
public:
	ExtractorA(){};
	~ExtractorA();
	Army get(const Unit& currentUnit, const Army& ally, const Army& opp){
		return ally;
	}
	std::string getCode(){
		return "A";
	}
};

class ExtractorO : public Extractor<Army>
{
private:
public:
	ExtractorO(){};
	~ExtractorO();
	Army get(const Unit& currentUnit, const Army& ally, const Army& opp){
		return opp;
	}
	std::string getCode(){
		return "O";
	}
};

class ExtractorNL : public Extractor<Army>
{
private:
	int _index;
	// TODO remplacer les numU par des extracteurs de valeurs directs
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorNL(int index, u_ptr<Extractor<float>>& eV, u_ptr<Extractor<Army>>& eA) : _index(index), _eV(std::move(eV)), _eA(std::move(eA)){};
	~ExtractorNL();
	/*
	bool greaterThan(Unit* unit, Unit* unit2){
		return unit->getCapacity(_index) < unit2->getCapacity(_index);
	}*/

	Army get(const Unit& currentUnit, const Army& ally, const Army& opp){
		int index = _index;
		std::vector<s_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		int numU = _eV->get(currentUnit, ally, opp);
		std::nth_element(vUnit.begin(), vUnit.begin() + numU, vUnit.end(),
			[&index](s_ptr<Unit>& a, s_ptr<Unit>& b){return a->getCapacity(index) < b->getCapacity(index); });
		std::vector<s_ptr<Unit>> nVUnit(vUnit.begin(), vUnit.begin() + numU);
		return Army(nVUnit);
	}

	std::string getCode(){
		return "NL" + _index + _eV->getCode() + _eA->getCode();
	}
};

class ExtractorNH : public Extractor<Army>
{
private:
	int _index;
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorNH(int index, u_ptr<Extractor<float>>& eV, u_ptr<Extractor<Army>>& eA) : _index(index), _eV(std::move(eV)), _eA(std::move(eA)){};
	~ExtractorNH();
	Army get(const Unit& currentUnit, const Army& ally, const Army& opp){
		int index = _index;
		std::vector<s_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		float numU = _eV->get(currentUnit, ally, opp);
		std::nth_element(vUnit.begin(), vUnit.begin() + numU, vUnit.end(),
			[&index](s_ptr<Unit>& a, s_ptr<Unit>& b){return a->getCapacity(index) > b->getCapacity(index); });
		std::vector<s_ptr<Unit>> nVUnit(vUnit.begin(), vUnit.begin() + numU);
		return Army(nVUnit);
	}

	std::string getCode(){
		return "NH" + _index + _eV->getCode() + _eA->getCode();
	}
};


class ExtractorNLD : public Extractor<Army>
{
private:
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorNLD(u_ptr<Extractor<float>>& eV, u_ptr<Extractor<Army>>& eA, u_ptr<Extractor<Point>>& eP) : _eV(std::move(eV)), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorNLD();
	Army get(const Unit& currentUnit, const Army& ally, const Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		std::vector<s_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		float numU = _eV->get(currentUnit, ally, opp);
		std::nth_element(vUnit.begin(), vUnit.begin() + numU, vUnit.end(),
			[&p](s_ptr<Unit>& a, s_ptr<Unit>& b){return a->getPosition().distance(p) < b->getPosition().distance(p); });
		std::vector<s_ptr<Unit>> nVUnit(vUnit.begin(), vUnit.begin() + numU);
		return Army(nVUnit);
	}

	std::string getCode(){
		return "NLD" + _eV->getCode() + _eA->getCode() + _eP->getCode();
	}
};

class ExtractorNHD : public Extractor<Army>
{
private:
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorNHD(u_ptr<Extractor<float>>& eV, u_ptr<Extractor<Army>>& eA, u_ptr<Extractor<Point>>& eP) : _eV(std::move(eV)), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorNHD();
	Army get(const Unit& currentUnit, const Army& ally, const Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		std::vector<s_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		float numU = _eV->get(currentUnit, ally, opp);
		std::nth_element(vUnit.begin(), vUnit.begin() + numU, vUnit.end(),
			[&p](s_ptr<Unit>& a, s_ptr<Unit>& b){return a->getPosition().distance(p) > b->getPosition().distance(p); });
		std::vector<s_ptr<Unit>> nVUnit(vUnit.begin(), vUnit.begin() + numU);
		return Army(nVUnit);
	}

	std::string getCode(){
		return "NHD" + _eV->getCode() + _eA->getCode() + _eP->getCode();
	}
};

class ExtractorTL : public Extractor<Army>
{
private:
	u_ptr<Extractor<float>> _eV;
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorTL(u_ptr<Extractor<float>>& eV, int index, u_ptr<Extractor<Army>>& eA) : _eV(std::move(eV)), _index(index), _eA(std::move(eA)){};
	~ExtractorTL();
	Army get(const Unit& currentUnit, const Army& ally, const Army& opp){
		_eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<s_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<s_ptr<Unit>> nVUnit(vUnit.size());
		int index = _index;
		float treshold = _eV->get(currentUnit, ally, opp);
		auto it = std::copy_if(vUnit.begin(), vUnit.end(), nVUnit.begin(), [&index, &treshold](s_ptr<Unit>& a){return a->getCapacity(index)->getValue() < treshold; });
		nVUnit.resize(std::distance(nVUnit.begin(), it));
	}	
	
	std::string getCode(){
		return "TL" + _index + _eV->getCode() + _eA->getCode();
	}
};

class ExtractorTH : public Extractor<Army>
{
private:
	u_ptr<Extractor<float>> _eV;
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorTH(u_ptr<Extractor<float>>& eV, int index, u_ptr<Extractor<Army>>& eA) : _eV(std::move(eV)), _index(index), _eA(std::move(eA)){};
	~ExtractorTH();
	Army get(const Unit& currentUnit, const Army& ally, const Army& opp){
		_eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<s_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<s_ptr<Unit>> nVUnit(vUnit.size());
		int index = _index;
		float treshold = _eV->get(currentUnit, ally, opp);
		auto it = std::copy_if(vUnit.begin(), vUnit.end(), nVUnit.begin(), [&index, &treshold](s_ptr<Unit>& a){return a->getCapacity(index)->getValue() > treshold; });
		nVUnit.resize(std::distance(nVUnit.begin(), it));
	}

	std::string getCode(){
		return "TH" + _index + _eV->getCode() + _eA->getCode();
	}
};


class ExtractorTLD : public Extractor<Army>
{
private:
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorTLD(u_ptr<Extractor<float>>& eV, u_ptr<Extractor<Army>>& eA, u_ptr<Extractor<Point>>& eP) : _eV(std::move(eV)), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorTLD();
	Army get(const Unit& currentUnit, const Army& ally, const Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		_eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<s_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<s_ptr<Unit>> nVUnit(vUnit.size());

		float treshold = _eV->get(currentUnit, ally, opp);
		auto it = std::copy_if(vUnit.begin(), vUnit.end(), nVUnit.begin(), [&p, &treshold](s_ptr<Unit>& a){return a->getPosition().distance(p) < treshold; });
		nVUnit.resize(std::distance(nVUnit.begin(), it));
	}

	std::string getCode(){
		return "TLD" + _eV->getCode() + _eA->getCode() + _eP->getCode();
	}
};

class ExtractorTHD : public Extractor<Army>
{
private:
	u_ptr<Extractor<float>> _eV;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorTHD(u_ptr<Extractor<float>>& eV, u_ptr<Extractor<Army>>& eA, u_ptr<Extractor<Point>>& eP) : _eV(std::move(eV)), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorTHD();
	Army get(const Unit& currentUnit, const Army& ally, const Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		_eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<s_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<s_ptr<Unit>> nVUnit(vUnit.size());

		float treshold = _eV->get(currentUnit, ally, opp);
		auto it = std::copy_if(vUnit.begin(), vUnit.end(), nVUnit.begin(), [&p, &treshold](s_ptr<Unit>& a){return a->getPosition().distance(p) > treshold; });
		nVUnit.resize(std::distance(nVUnit.begin(), it));
	}

	std::string getCode(){
		return "THD" + _eV->getCode() + _eA->getCode() + _eP->getCode();
	}
};

#endif //_EXTRACTORARMY_H_