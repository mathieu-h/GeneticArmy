#pragma once
#include "Extractor.h"

class ExtractorU : Extractor<Unit>
{
public:
	ExtractorU();
	~ExtractorU();
	Unit get(Unit currentUnit, Army ally, Army opp){
		return currentUnit;
	}
};

class ExtractorL : Extractor<Unit>
{
private: 
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorL(int index, u_ptr<Extractor<Army>> eA) : _index(index),_eA(std::move(eA)){};
	~ExtractorL();
	Unit get(Unit currentUnit, Army ally, Army opp){
		return _eA->get(currentUnit, ally, opp).getLowestUnit(_index);
	}
};

class ExtractorH : Extractor<Unit>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorH(int index, u_ptr<Extractor<Army>> eA) : _index(index), _eA(std::move(eA)){};
	~ExtractorH();
	Unit get(Unit currentUnit, Army ally, Army opp){
		return _eA->get(currentUnit, ally, opp).getHigestUnit(_index);
	}
};

class ExtractorLD : Extractor<Unit>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorLD(int index, u_ptr<Extractor<Army>> eA,
		u_ptr<Extractor<Point>> eP) : _index(index), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorLD();
	Unit get(Unit currentUnit, Army ally, Army opp){
		Point p = _eP->get(currentUnit, ally, opp);
		return _eA->get(currentUnit, ally, opp).getNearestUnit(p);
	}
};

class ExtractorHD : Extractor<Unit>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorHD(int index, u_ptr<Extractor<Army>> eA,
		u_ptr<Extractor<Point>> eP) : _index(index), _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorHD();
	Unit get(Unit currentUnit, Army ally, Army opp){
		Point p = _eP->get(currentUnit, ally, opp);
		return _eA->get(currentUnit, ally, opp).getFurthestUnit(p);
	}
};
