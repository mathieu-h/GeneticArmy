#pragma once
#include "Extractor.h"


class ExtractorV : Extractor<float>
{
	float value;
public:
	ExtractorV(float value);
	~ExtractorV();
	float get(Unit currentUnit, Army ally, Army opp){
		return value;
	}
};


class ExtractorC : Extractor<float>
{
public:
	ExtractorC();
	~ExtractorC();
	float get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorD : Extractor<float>
{
private:
	Extractor<Unit>* _eU;
	Extractor<Point>* _eP;
public:
	ExtractorD(Extractor<Unit>* eU, Extractor<Point>* eP) :_eU(eU), _eP(eP){};
	~ExtractorD();
	float get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorM: Extractor<float>
{
private:
	int index;
public:
	ExtractorM(int index);
	~ExtractorM();
	float get(Unit currentUnit, Army ally, Army opp);
};
