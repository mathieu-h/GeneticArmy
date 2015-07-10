#pragma once
#include "Extractor.h"


class ExtractorDirect : Extractor<float>
{
	float value;
public:
	ExtractorDirect(float value);
	~ExtractorDirect();
	float get(Unit currentUnit, Army ally, Army opp){
		return value;
	}
};


class ExtractorC : Extractor<float>
{
	int _index;
	Extractor<Unit>* _eU;
public:
	ExtractorC(int index, Extractor<Unit>* eU) : _index(index), _eU(eU){};
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


class ExtractorM : Extractor<float>
{
private:
	int _index;
	Extractor<Army>* _eA;
public:
	ExtractorM(int index, Extractor<Army>* eA) : _index(index){}, _eA(eA){};
	~ExtractorM();
	float get(Unit currentUnit, Army ally, Army opp);
};

class Extractorm : Extractor<float>
{
private:
	int _index;
	Extractor<Army>* _eA;
public:
	Extractorm(int index, Extractor<Army>* eA) : _index(index){}, _eA(eA){};
	~Extractorm();
	float get(Unit currentUnit, Army ally, Army opp);
};

class Extractora : Extractor<float>
{
private:
	int _index;
	Extractor<Army>* _eA;
public:
	Extractora(int index, Extractor<Army>* eA) : _index(index){}, _eA(eA){};
	~Extractora();
	float get(Unit currentUnit, Army ally, Army opp);
};


class ExtractorMD: Extractor<float>
{
private:
	int _index;
	Extractor<Army>* _eA;
	Extractor<Point>* _eP;
public:
	ExtractorMD(int index, Extractor<Army>* eA, Extractor<Point>* eP) : _index(index){}, _eA(eA), _eP(eP){};
	~ExtractorMD();
	float get(Unit currentUnit, Army ally, Army opp);
};

class ExtractormD : Extractor<float>
{
private:
	int _index;
	Extractor<Army>* _eA;
	Extractor<Point>* _eP;
public:
	ExtractormD(int index, Extractor<Army>* eA, Extractor<Point>* eP) : _index(index){}, _eA(eA), _eP(eP){};
	~ExtractormD();
	float get(Unit currentUnit, Army ally, Army opp);
};

class ExtractoraD : Extractor<float>
{
private:
	int _index;
	Extractor<Army>* _eA;
	Extractor<Point>* _eP;
public:
	ExtractoraD(int index, Extractor<Army>* eA, Extractor<Point>* eP) : _index(index){}, _eA(eA), _eP(eP){};
	~ExtractoraD();
	float get(Unit currentUnit, Army ally, Army opp);
};

