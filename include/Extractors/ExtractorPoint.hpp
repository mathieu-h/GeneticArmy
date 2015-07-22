#ifndef _EXTRACTORPOINT_H_
#define _EXTRACTORPOINT_H_
#pragma once
#include "Extractor.hpp"

class ExtractorB : public Extractor<Point>
{
private:
	u_ptr<Extractor<ArmyVec>> _eA;
public:
	ExtractorB(u_ptr<Extractor<ArmyVec>>& eA) : _eA(std::move(eA)){};
	~ExtractorB();
	// return the barycenter of all units in the set
	Point get(Unit& currentUnit, Army& ally, Army& opp){
		ArmyVec& vUnit = _eA->get(currentUnit, ally, opp);
		float sumY = std::accumulate(vUnit.begin(), vUnit.end(),
			0, [](float a, s_ptr<Unit>& it){return a + it->getPosition().getY(); });
		float sumX = std::accumulate(vUnit.begin(), vUnit.end(),
			0, [/*&sumY*/](float a, s_ptr<Unit>& it){return a + it->getPosition().getX();
					/*sumY += it->getPosition().getY();*/ });
		return vUnit.size() == 0 ? Point(.0f,.0f) : Point(sumX / vUnit.size(), sumY / vUnit.size());
	}

	std::string getCode(){
		return "B" + _eA->getCode();
	}
};

class ExtractorP : public Extractor<Point>
{
private:
	u_ptr<Extractor<Unit&>> _eU;
public:
	ExtractorP(u_ptr<Extractor<Unit&>>& eU) : _eU(std::move(eU)){};
	~ExtractorP();
	Point get(Unit& currentUnit, Army& ally, Army& opp){
		return _eU->get(currentUnit, ally, opp).getPosition();
	}

	std::string getCode(){
		return "P" + _eU->getCode();
	}
};
#endif //_EXTRACTORPOINT_H_