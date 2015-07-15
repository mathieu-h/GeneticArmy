#pragma once
#include <string>     
#include <iostream> 
#include <sstream>
#include "Extractor.h"
#include "ExtractorArmy.h"
#include "ExtractorUnit.h"
#include "ExtractorPoint.h"
#include "ExtractorValue.h"

class ExtractorBuilder
{
	private:
	public:

		u_ptr<Extractor<Army>> buildArmyExtractor(std::stringstream& code){
			char c;
			code >> c;
			switch (c){
				case 'A':
				{
					u_ptr<Extractor<Army>> exB(new ExtractorA());
					return exB;
				}
				case 'O':
				{
					u_ptr<Extractor<Army>> exP(new ExtractorO());
					return exP;
				}
				case 'N':
				{
					code >> c;
					if (c == 'L'){
						code >> c;
						if (c == 'D'){
							code >> c;
							// TODO s'assurer qu'ici le code qu'on passe a buildPointExtractor a bien été 'consommé' par buildArmyExtractor avant
							u_ptr<Extractor<Army>> exNLD(new ExtractorNLD(buildValueExtractor(code), buildArmyExtractor(code), buildPointExtractor(code)));
							return exNLD;
						}
						else{
							code >> c;
							u_ptr<Extractor<Army>> exNL(new ExtractorNL((int)c, buildValueExtractor(code), buildArmyExtractor(code)));
							return exNL;
						}
					}
					else{
						if (c == 'D'){
							code >> c;
							// TODO s'assurer qu'ici le code qu'on passe a buildPointExtractor a bien été 'consommé' par buildArmyExtractor avant
							u_ptr<Extractor<Army>> exNHD(new ExtractorNLD(buildValueExtractor(code), buildArmyExtractor(code), buildPointExtractor(code)));
							return exNHD;
						}
						else{
							code >> c;
							u_ptr<Extractor<Army>> exNH(new ExtractorNL((int)c, buildValueExtractor(code), buildArmyExtractor(code)));
							return exNH;
						}
					}
				}

				case 'T':
				{
					code >> c;
					if (c == 'L'){
						code >> c;
						if (c == 'D'){
							code >> c;
							// TODO s'assurer qu'ici le code qu'on passe a buildPointExtractor a bien été 'consommé' par buildArmyExtractor avant
							u_ptr<Extractor<Army>> exTLD(new ExtractorNLD(buildValueExtractor(code), buildArmyExtractor(code), buildPointExtractor(code)));
							return exTLD;
						}
						else{
							code >> c;
							u_ptr<Extractor<Army>> exTL(new ExtractorNL((int)c, buildValueExtractor(code), buildArmyExtractor(code)));
							return exTL;
						}
					}
					else{
						if (c == 'D'){
							code >> c;
							// TODO s'assurer qu'ici le code qu'on passe a buildPointExtractor a bien été 'consommé' par buildArmyExtractor avant
							u_ptr<Extractor<Army>> exTHD(new ExtractorNLD(buildValueExtractor(code), buildArmyExtractor(code), buildPointExtractor(code)));
							return exTHD;
						}
						else{
							code >> c;
							u_ptr<Extractor<Army>> exTH(new ExtractorNL((int)c, buildValueExtractor(code), buildArmyExtractor(code)));
							return exTH;
						}
					}
				}
				default:
					return nullptr;
			}
		}

		u_ptr<Extractor<Point>> buildPointExtractor(std::stringstream& code){
			char c;
			code >> c;
			switch (c){
				case 'B':
				{
					u_ptr<Extractor<Point>> exB(new ExtractorB(buildArmyExtractor(code)));
					return exB;
				}
				case 'P':
				{
					u_ptr<Extractor<Point>> exP(new ExtractorP(buildUnitExtractor(code)));
					return exP;
				}
				default:
					return nullptr;
			}
		}

		u_ptr<Extractor<Unit>> buildUnitExtractor(std::stringstream& code){
			char c;
			code >> c;
			switch (c){
				case 'U':
				{
					u_ptr<Extractor<Unit>> exU(new ExtractorU());
					return exU;
				}
				case 'L':
				{
					code >> c;
					if (c == 'D'){
						u_ptr<Extractor<Unit>> exL(new ExtractorLD(buildArmyExtractor(code), buildPointExtractor(code)));
						return exL;
					}
					else{
						u_ptr<Extractor<Unit>> exL(new ExtractorL((int)c, buildArmyExtractor(code)));
						return exL;
					}
				}
				case 'H':
				{
					code >> c;
					if (c == 'D'){
						u_ptr<Extractor<Unit>> exH(new ExtractorHD(buildArmyExtractor(code), buildPointExtractor(code)));
						return exH;
					}
					else{
						u_ptr<Extractor<Unit>> exH(new ExtractorH((int)c, buildArmyExtractor(code)));
						return exH;
					}
				}
				default :
					return nullptr;
			}
		}

		u_ptr<Extractor<float>> buildValueExtractor(std::stringstream& code){
			char c;
			code >> c;
			switch (c){
				// TODO direct value extractor, case avec un chiffre en premier caractère
				case 'C':
				{
					code >> c;
					u_ptr<Extractor<float>> exC(new ExtractorC((int)c, buildUnitExtractor(code)));
					return exC;
				}				
				case 'D':
				{
					u_ptr<Extractor<float>> exD(new ExtractorD(buildUnitExtractor(code), buildPointExtractor(code)));
					return exD;
				}				
				case 'M':
				{
					code >> c;
					if (c == 'D'){
						u_ptr<Extractor<float>> exMD(new ExtractorMD(buildArmyExtractor(code), buildPointExtractor(code)));
						return exMD;
					}
					else{
						u_ptr<Extractor<float>> exM(new ExtractorM((int)c, buildArmyExtractor(code)));
						return exM;
					}
				}
				case 'm':
				{
					code >> c;
					if (c == 'D'){
						u_ptr<Extractor<float>> exmD(new ExtractormD(buildArmyExtractor(code), buildPointExtractor(code)));
						return exmD;
					}
					else{
						u_ptr<Extractor<float>> exm(new Extractorm((int)c, buildArmyExtractor(code)));
						return exm;
					}
				}
				case 'a':
				{
					code >> c;
					if (c == 'D'){
						u_ptr<Extractor<float>> exaD(new ExtractormD(buildArmyExtractor(code), buildPointExtractor(code)));
						return exaD;
					}
					else{
						u_ptr<Extractor<float>> exa(new Extractorm((int)c, buildArmyExtractor(code)));
						return exa;
					}
				}
			}
		}
		


};