#ifndef _EXTRACTOR_HPP_
#define _EXTRACTOR_HPP_
#pragma once
#include "Army.hpp"
#include "Unit.hpp"

template<typename R>
class Extractor
{
public:

	virtual R get(Unit currentUnit, Army ally, Army opp) = 0;

};

#endif