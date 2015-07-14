#pragma once
#include "Extractor.h"


class ExtractorDirect : Extractor<float>
{
	float _value;
public:
	ExtractorDirect(float value): _value(value){};
	~ExtractorDirect();
	float get(Unit currentUnit, Army ally, Army opp){
		return _value;
	}
};


class ExtractorC : Extractor<float>
{
	int _index;
	u_ptr<Extractor<Unit>> _eU;
public:
	ExtractorC(int index, u_ptr<Extractor<Unit>>& eU) : _index(index), _eU(std::move(eU)){};
	~ExtractorC();
	float get(Unit currentUnit, Army ally, Army opp){
		return ;
	}
};

class ExtractorD : Extractor<float>
{
private:
	u_ptr<Extractor<Unit>> _eU;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorD(u_ptr<Extractor<Unit>>& eU, u_ptr<Extractor<Point>>& eP) :_eU(std::move(eU)), _eP(std::move(eP)){};
	~ExtractorD();
	float get(Unit currentUnit, Army ally, Army opp);
};


class ExtractorM : Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorM(int index, u_ptr<Extractor<Army>>& eA) : _index(index){}, _eA(std::move(eA)){};
	~ExtractorM();
	float get(Unit currentUnit, Army ally, Army opp);
};

class Extractorm : Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	Extractorm(int index, u_ptr<Extractor<Army>>& eA) : _index(index){}, _eA(std::move(eA)){};
	~Extractorm();
	float get(Unit currentUnit, Army ally, Army opp);
};

class Extractora : Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	Extractora(int index, u_ptr<Extractor<Army>>& eA) : _index(index){}, _eA(std::move(eA)){};
	~Extractora();
	float get(Unit currentUnit, Army ally, Army opp);
};


class ExtractorMD: Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorMD(int index, u_ptr<Extractor<Army>>& eA, u_ptr<Extractor<Point>>& eP) : _index(index){}, _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorMD();
	float get(Unit currentUnit, Army ally, Army opp);
};

class ExtractormD : Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractormD(int index, u_ptr<Extractor<Army>>& eA, u_ptr<Extractor<Point>>& eP) : _index(index){}, _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractormD();
	float get(Unit currentUnit, Army ally, Army opp);
};

class ExtractoraD : Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractoraD(int index, u_ptr<Extractor<Army>>& eA, u_ptr<Extractor<Point>>& eP) : _index(index){}, _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractoraD();
	float get(Unit currentUnit, Army ally, Army opp);
};

