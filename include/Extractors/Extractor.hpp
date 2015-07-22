#ifndef _EXTRACTOR_HPP_
#define _EXTRACTOR_HPP_
#pragma once
#include "Army.hpp"
#include "Unit.hpp"
#include <algorithm>
#include <functional>
#include <vector>
#include <numeric>
#include "IAGetterCode.hpp"

#define u_ptr std::unique_ptr
#define s_ptr std::shared_ptr

//#define UnicVec std::unique_ptr
typedef std::vector<s_ptr<Unit>> ArmyVec;

template<typename R>
class Extractor : public IAGetterCode
{
public:

	virtual R get(const Unit& currentUnit, Army& ally, Army& opp) = 0;

};

#endif