#pragma once
#include "Extractor.h"

class ExtractorB : Extractor<Point>
{
private:
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorB(u_ptr<Extractor<Army>> eA) : _eA(std::move(eA)){};
	~ExtractorB();
	Point get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorP : Extractor<Point>
{
private:
	u_ptr<Extractor<Unit>> _eU;
public:
	ExtractorP(u_ptr<Extractor<Unit>> eU) : _eU(std::move(eU)){};
	~ExtractorP();
	Point get(Unit currentUnit, Army ally, Army opp);
};
