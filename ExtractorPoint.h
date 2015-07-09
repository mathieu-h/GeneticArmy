#pragma once
#include "Extractor.h"

class ExtractorU : Extractor<Point>
{
public:
	ExtractorU();
	~ExtractorU();
	Point get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorL : Extractor<Point>
{
public:
	ExtractorL();
	~ExtractorL();
	Point get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorH : Extractor<Point>
{
public:
	ExtractorH();
	~ExtractorH();
	Point get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorLD : Extractor<Point>
{
public:
	ExtractorLD();
	~ExtractorLD();
	Point get(Unit currentUnit, Army ally, Army opp);
};

class ExtractorHD : Extractor<Point>
{
public:
	ExtractorHD();
	~ExtractorHD();
	Point get(Unit currentUnit, Army ally, Army opp);
};
