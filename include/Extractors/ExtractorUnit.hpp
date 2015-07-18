#pragma once
#include "Extractor.hpp"


class ExtractorU : public Extractor<Unit>
{
public:
	ExtractorU();
	~ExtractorU();
	Unit get(const Unit& currentUnit, const Army& ally, const Army& opp){
		return currentUnit;
	}
};

class ExtractorL : public Extractor<Unit>
{
private: 
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorL(int index, u_ptr<Extractor<Army>>& eA) : _index(index),_eA(std::move(eA)){};
	~ExtractorL();
	Unit get(const Unit& currentUnit, const Army& ally, const Army& opp){
		return _eA->get(currentUnit, ally, opp).getLowestUnit(_index);
	}
};

class ExtractorH : public Extractor<Unit>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorH(int index, u_ptr<Extractor<Army>>& eA) : _index(index), _eA(std::move(eA)){};
	~ExtractorH();
	Unit get(const Unit& currentUnit, const Army& ally, const Army& opp){
		return _eA->get(currentUnit, ally, opp).getHigestUnit(_index);
	}
};

class ExtractorLD : public Extractor<Unit>
{
private:
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorLD(u_ptr<Extractor<Army>>& eA,
		u_ptr<Extractor<Point>>& eP) : _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorLD();
	Unit get(const Unit& currentUnit, const Army& ally, const Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		return _eA->get(currentUnit, ally, opp).getNearestUnit(p);
	}
};

class ExtractorHD : public Extractor<Unit>
{
private:
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorHD(u_ptr<Extractor<Army>>& eA,
		u_ptr<Extractor<Point>>& eP) : _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorHD();
	Unit get(const Unit& currentUnit, const Army& ally, const Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		return _eA->get(currentUnit, ally, opp).getFurthestUnit(p);
	}
};
