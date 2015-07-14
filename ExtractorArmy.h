#pragma once
#include "Extractor.h"

class ExtractorA : Extractor<Army>
{
public:
	ExtractorA();
	~ExtractorA();
	Army get(Unit currentUnit, Army ally, Army opp){
		return ally;
	}
};

class ExtractorO : Extractor<Army>
{
public:
	ExtractorO();
	~ExtractorO();
	Army get(Unit currentUnit, Army ally, Army opp){
		return opp;
	}
};

class ExtractorNL : Extractor<Army>
{
private:
	int _index;
	int _numU;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorNL(int index, int numU, u_ptr<Extractor<Army>> eA) : _index(index), _numU(numU), _eA(std::move(eA)){};
	~ExtractorNL();
	/*
	bool greaterThan(Unit* unit, Unit* unit2){
		return unit->getCapacity(_index) < unit2->getCapacity(_index);
	}*/

	Army get(Unit currentUnit, Army ally, Army opp){
		int index = _index;
		std::vector<u_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		std::nth_element(vUnit.begin(), vUnit.begin() + _numU, vUnit.end(),
			[&index](Unit* a, Unit* b){return a->getCapacity(index) < b->getCapacity(index);});
		std::vector<u_ptr<Unit>> nVUnit(vUnit.begin(), vUnit.begin() + _numU);
		return Army(nVUnit);
	}
};

class ExtractorNH : Extractor<Army>
{
private:
	int _index;
	int _numU;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorNH(int index, int numU, u_ptr<Extractor<Army>> eA) : _index(index), _numU(numU), _eA(std::move(eA)){};
	~ExtractorNH();
	Army get(Unit currentUnit, Army ally, Army opp){
		int index = _index;
		std::vector<u_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		std::nth_element(vUnit.begin(), vUnit.begin() + _numU, vUnit.end(),
			[&index](Unit* a, Unit* b){return a->getCapacity(index) > b->getCapacity(index); });
		std::vector<u_ptr<Unit>> nVUnit(vUnit.begin(), vUnit.begin() + _numU);
		return Army(nVUnit);
	}
};


class ExtractorNLD : Extractor<Army>
{
private:
	int _numU;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorNLD(int numU, u_ptr<Extractor<Army>> eA, u_ptr<Extractor<Point>> eP) : _numU(numU), _eA(std::move(eA)), _eP(std::move(eP)){};
	ExtractorNLD();
	~ExtractorNLD();
	Army get(Unit currentUnit, Army ally, Army opp){
		Point p = _eP->get(currentUnit, ally, opp);
		std::vector<u_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		std::nth_element(vUnit.begin(), vUnit.begin() + _numU, vUnit.end(),
			[&p](Unit* a, Unit* b){return a->getPosition().distance(p) < b->getPosition().distance(p); });
		std::vector<u_ptr<Unit>> nVUnit(vUnit.begin(), vUnit.begin() + _numU);
		return Army(nVUnit);
	}
};

class ExtractorNHD : Extractor<Army>
{
private:
	int _numU;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorNHD(int numU, u_ptr<Extractor<Army>> eA, u_ptr<Extractor<Point>> eP) : _numU(numU), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorNHD();
	Army get(Unit currentUnit, Army ally, Army opp){
		Point p = _eP->get(currentUnit, ally, opp);
		std::vector<u_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		std::nth_element(vUnit.begin(), vUnit.begin() + _numU, vUnit.end(),
			[&p](Unit* a, Unit* b){return a->getPosition().distance(p) > b->getPosition().distance(p); });
		std::vector<u_ptr<Unit>> nVUnit(vUnit.begin(), vUnit.begin() + _numU);
		return Army(nVUnit);
	}
};

class ExtractorTL : Extractor<Army>
{
private:
	float _treshold;
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorTL(float treshold, int index, u_ptr<Extractor<Army>> eA) : _treshold(treshold), _index(index), _eA(std::move(eA)){};
	~ExtractorTL();
	Army get(Unit currentUnit, Army ally, Army opp){
		_eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<u_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<u_ptr<Unit>> nVUnit(vUnit.size());
		int index = _index;
		float treshold = _treshold;
		auto it = std::copy_if(vUnit.begin(), vUnit.end(), nVUnit.begin(), [&index,&treshold](Unit* a){return a->getCapacity(index)->getValue() < treshold;});
		nVUnit.resize(std::distance(nVUnit.begin(), it));
	}
};

class ExtractorTH : Extractor<Army>
{
private:
	float _treshold;
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorTH(float treshold, int index, u_ptr<Extractor<Army>> eA) : _treshold(treshold), _index(index), _eA(std::move(eA)){};
	~ExtractorTH();
	Army get(Unit currentUnit, Army ally, Army opp){
		_eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<u_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<u_ptr<Unit>> nVUnit(vUnit.size());
		int index = _index;
		float treshold = _treshold;
		auto it = std::copy_if(vUnit.begin(), vUnit.end(), nVUnit.begin(), [&index, &treshold](Unit* a){return a->getCapacity(index)->getValue() > treshold; });
		nVUnit.resize(std::distance(nVUnit.begin(), it));
	}
};


class ExtractorTLD : Extractor<Army>
{
private:
	float _treshold;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorTLD(float treshold, int index, u_ptr<Extractor<Army>> eA, u_ptr<Extractor<Point>> eP) : _treshold(treshold), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorTLD();
	Army get(Unit currentUnit, Army ally, Army opp){
		Point p = _eP->get(currentUnit, ally, opp);
		_eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<u_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<u_ptr<Unit>> nVUnit(vUnit.size());

		float treshold = _treshold;
		auto it = std::copy_if(vUnit.begin(), vUnit.end(), nVUnit.begin(), [&p, &treshold](Unit* a){return a->getPosition().distance(p) < treshold; });
		nVUnit.resize(std::distance(nVUnit.begin(), it));
	}
};

class ExtractorTHD : Extractor<Army>
{
private:
	float _treshold;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorTHD(float treshold, int index, u_ptr<Extractor<Army>> eA, u_ptr<Extractor<Point>> eP) : _treshold(treshold), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorTHD();
	Army get(Unit currentUnit, Army ally, Army opp){
		Point p = _eP->get(currentUnit, ally, opp);
		_eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<u_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		std::vector<u_ptr<Unit>> nVUnit(vUnit.size());

		float treshold = _treshold;
		auto it = std::copy_if(vUnit.begin(), vUnit.end(), nVUnit.begin(), [&p, &treshold](Unit* a){return a->getPosition().distance(p) > treshold; });
		nVUnit.resize(std::distance(nVUnit.begin(), it));
	}
};