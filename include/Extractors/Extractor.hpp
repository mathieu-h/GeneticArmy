#ifndef _EXTRACTOR_HPP_
#define _EXTRACTOR_HPP_
#pragma once
#include "Army.hpp"
#include "Unit.hpp"
#include <algorithm>
#include <functional>
#include <vector>
#include <numeric>

#define u_ptr std::unique_ptr
#define s_ptr std::shared_ptr

template<typename R>
class Extractor
{
public:

	virtual R get(Unit currentUnit, Army ally, Army opp) = 0;

};

#endif