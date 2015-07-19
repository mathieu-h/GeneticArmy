#ifndef _EXTRACTORVALUE_H_
#define _EXTRACTORVALUE_H_
#pragma once
#include "Extractor.hpp"


class ExtractorDirect : public Extractor<float>
{
private:
	float _value;
public:
	ExtractorDirect(float value): _value(value){};
	~ExtractorDirect();
	float get(const Unit& currentUnit, const Army& ally, const Army& opp){
		return _value;
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
	float get(const Unit& currentUnit, const Army& ally, const Army& opp){
		return _eU->get(currentUnit, ally, opp).getCapacity(_index)->getValue();
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
	float get(const Unit& currentUnit, const Army& ally, const Army& opp){
		return _eU->get(currentUnit, ally, opp).getPosition().distance(_eP->get(currentUnit, ally, opp));
	}
};


class ExtractorM : public Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	ExtractorM(int index, u_ptr<Extractor<Army>>& eA) : _index(index), _eA(std::move(eA)){};
	~ExtractorM();
	float get(const Unit& currentUnit, const Army& ally, const Army& opp){
		return _eA->get(currentUnit, ally, opp).getHigestUnit(_index).getCapacity(_index)->getValue();
	}
};

class Extractorm : public Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	Extractorm(int index, u_ptr<Extractor<Army>>& eA) : _index(index), _eA(std::move(eA)){};
	~Extractorm();
	float get(const Unit& currentUnit, const Army& ally, const Army& opp){
		return _eA->get(currentUnit, ally, opp).getLowestUnit(_index).getCapacity(_index)->getValue();
	}
};

class Extractora : public Extractor<float>
{
private:
	int _index;
	u_ptr<Extractor<Army>> _eA;
public:
	Extractora(int index, u_ptr<Extractor<Army>>& eA) : _index(index), _eA(std::move(eA)){};
	~Extractora();
	float get(const Unit& currentUnit, const Army& ally, const Army& opp){
		std::vector<s_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		
		int index = _index;
		float sum = std::accumulate(vUnit.begin(), vUnit.end(), 
				0, [&index](float a, s_ptr<Unit>& it){return a + it->getCapacity(index)->getValue(); });
		return vUnit.size() == 0 ? 0.0 : sum / vUnit.size();
	}
};


class ExtractorMD : public Extractor<float>
{
private:
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractorMD(u_ptr<Extractor<Army>>& eA, u_ptr<Extractor<Point>>& eP) : _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractorMD();
	float get(const Unit& currentUnit, const Army& ally, const Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		return _eA->get(currentUnit, ally, opp).getFurthestUnit(p).getPosition().distance(p);
	}
};

class ExtractormD : public Extractor<float>
{
private:
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractormD(u_ptr<Extractor<Army>>& eA, u_ptr<Extractor<Point>>& eP) : _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractormD();
	float get(const Unit& currentUnit, const Army& ally, const Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		return _eA->get(currentUnit, ally, opp).getNearestUnit(p).getPosition().distance(p);
	}
};

class ExtractoraD : public Extractor<float>
{
private:
	u_ptr<Extractor<Army>> _eA;
	u_ptr<Extractor<Point>> _eP;
public:
	ExtractoraD(u_ptr<Extractor<Army>>& eA, u_ptr<Extractor<Point>>& eP) : _eA(std::move(eA)), _eP(std::move(eP)){};
	~ExtractoraD();
	float get(const Unit& currentUnit, const Army& ally, const Army& opp){
		Point p = _eP->get(currentUnit, ally, opp);
		std::vector<s_ptr<Unit>>& vUnit = _eA->get(currentUnit, ally, opp).getUnitsList();
		float sum = std::accumulate(vUnit.begin(), vUnit.end(),
			0, [&p](float a, s_ptr<Unit>& it){return a + it->getPosition().distance(p); });
		return vUnit.size() == 0 ? 0.0 : sum / vUnit.size();
	}
};
#endif // _EXTRACTORVALUE_H_
