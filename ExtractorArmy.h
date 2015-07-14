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
	Army get(Unit currentUnit, Army ally, Army opp);
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
	Army get(Unit currentUnit, Army ally, Army opp);
};


class ExtractorNLD : Extractor<Army>
{
private:
	int _numU;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorNLD(int numU, u_ptr<Extractor<Army>> eA) : _numU(numU), _eA(std::move(eA)){};
	ExtractorNLD();
	~ExtractorNLD();
	Army get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorNHD : Extractor<Army>
{
private:
	int _numU;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorNHD(int numU, u_ptr<Extractor<Army>> eA) : _numU(numU), _eA(std::move(eA)){};
	~ExtractorNHD();
	Army get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorTL : Extractor<Army>
{
private:
	int _treshold;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorTL(int treshold, u_ptr<Extractor<Army>> eA) : _treshold(treshold), _eA(std::move(eA)){};
	~ExtractorTL();
	Army get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorTH : Extractor<Army>
{
private:
	int _treshold;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorTH(int treshold, u_ptr<Extractor<Army>> eA) : _treshold(treshold), _eA(std::move(eA)){};
	~ExtractorTH();
	Army get(Unit currentUnit, Army ally, Army opp);
};
