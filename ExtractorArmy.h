#pragma once
#include "Extractor.h"

class ExtractorA : Extractor<Army>
{
public:
	ExtractorA();
	~ExtractorA();
	Army get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorO : Extractor<Army>
{
public:
	ExtractorO();
	~ExtractorO();
	Army get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorNL : Extractor<Army>
{
public:
	ExtractorNL();
	~ExtractorNL();
	Army get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorNLD : Extractor<Army>
{
public:
	ExtractorNLD();
	~ExtractorNLD();
	Army get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorNHD : Extractor<Army>
{
public:
	ExtractorNHD();
	~ExtractorNHD();
	Army get(Unit currentUnit, Army ally, Army opp);
};
