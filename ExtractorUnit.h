#pragma once
#include "Extractor.h"

class ExtractorU : Extractor<Unit>
{
public:
	ExtractorU();
	~ExtractorU();
	Unit get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorL : Extractor<Unit>
{
public:
	ExtractorL();
	~ExtractorL();
	Unit get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorH : Extractor<Unit>
{
public:
	ExtractorH();
	~ExtractorH();
	Unit get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorLD : Extractor<Unit>
{
public:
	ExtractorLD();
	~ExtractorLD();
	Unit get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorHD : Extractor<Unit>
{
public:
	ExtractorHD();
	~ExtractorHD();
	Unit get(Unit currentUnit, Army ally, Army opp);
};
