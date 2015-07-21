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

template<typename R>
class Extractor : public IAGetterCode
{
public:

	virtual R get(const Unit& currentUnit, const Army& ally, const Army& opp) = 0;

};

#endif