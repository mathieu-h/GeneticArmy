#ifndef _EXTRACTORBUILDER_H_
#define _EXTRACTORBUILDER_H_
#pragma once
#include <string>     
#include <iostream> 
#include <sstream>
#include "Extractor.hpp"
#include "ExtractorArmy.hpp"
#include "ExtractorUnit.hpp"
#include "ExtractorPoint.hpp"
#include "ExtractorValue.hpp"
#define toDigit(c) (c-'0')

class ExtractorBuilder
{
	private:
		//static ExtractorBuilder* instance;		
		//ExtractorBuilder(ExtractorBuilder const&); // Don't Implement.
		//void operator=(ExtractorBuilder const&); // Don't implement
		ExtractorBuilder(){};
		~ExtractorBuilder(){};

	public:
		static ExtractorBuilder& getInstance(){
			//if (instance == nullptr){
			//	instance = new ExtractorBuilder();
			//}
			static ExtractorBuilder instance;
			return instance;
		}

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
							u_ptr<Extractor<float>> eV = buildValueExtractor(code);
							u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
							u_ptr<Extractor<Point>> eP = buildPointExtractor(code);
							u_ptr<Extractor<Army>> exNLD(new ExtractorNLD(eV, eA, eP));
							return exNLD;
						}
						else{
							u_ptr<Extractor<float>> eV = buildValueExtractor(code);
							u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
							u_ptr<Extractor<Army>> exNL(new ExtractorNL(toDigit(c), eV, eA));
							return exNL;
						}
					}
					else{
						if (c == 'D'){
							u_ptr<Extractor<float>> eV = buildValueExtractor(code);
							u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
							u_ptr<Extractor<Point>> eP = buildPointExtractor(code);
							u_ptr<Extractor<Army>> exNHD(new ExtractorNHD(eV, eA, eP));
							return exNHD;
						}
						else{
							u_ptr<Extractor<float>> eV = buildValueExtractor(code);
							u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
							u_ptr<Extractor<Army>> exNH(new ExtractorNH(toDigit(c), eV, eA));
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
							u_ptr<Extractor<float>> eV = buildValueExtractor(code);
							u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
							u_ptr<Extractor<Point>> eP = buildPointExtractor(code);
							u_ptr<Extractor<Army>> exTLD(new ExtractorTLD(buildValueExtractor(code), buildArmyExtractor(code), buildPointExtractor(code)));
							return exTLD;
						}
						else{					
							u_ptr<Extractor<float>> eV = buildValueExtractor(code);
							u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
							u_ptr<Extractor<Army>> exTL(new ExtractorTL(toDigit(c), eV, eA));
							return exTL;
						}
					}
					else{
						code >> c;
						if (c == 'D'){
							u_ptr<Extractor<float>> eV = buildValueExtractor(code);
							u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
							u_ptr<Extractor<Point>> eP = buildPointExtractor(code);
							u_ptr<Extractor<Army>> exTHD(new ExtractorTHD(eV, eA, eP));
							return exTHD;
						}
						else{
							u_ptr<Extractor<float>> eV = buildValueExtractor(code);
							u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
							u_ptr<Extractor<Army>> exTH(new ExtractorTH(toDigit(c), buildValueExtractor(code), buildArmyExtractor(code)));
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
					u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
					u_ptr<Extractor<Point>> exB(new ExtractorB(eA));
					return exB;
				}
				case 'P':
				{
					u_ptr<Extractor<Unit>> eU = buildUnitExtractor(code);
					u_ptr<Extractor<Point>> exP(new ExtractorP(eU));
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
						u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
						u_ptr<Extractor<Point>> eP = buildPointExtractor(code);
						u_ptr<Extractor<Unit>> exL(new ExtractorLD(eA, eP));
						return exL;
					}
					else{
						u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
						u_ptr<Extractor<Unit>> exL(new ExtractorL(toDigit(c), eA));
						return exL;
					}
				}
				case 'H':
				{
					code >> c;
					if (c == 'D'){
						u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
						u_ptr<Extractor<Point>> eP = buildPointExtractor(code);
						u_ptr<Extractor<Unit>> exH(new ExtractorHD(eA, eP));
						return exH;
					}
					else{
						u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
						u_ptr<Extractor<Unit>> exH(new ExtractorH(toDigit(c), eA));
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
				case '[':
				{
					float val;
					code >> val;
					// On consomme le ']'
					u_ptr<Extractor<float>> exDirect(new ExtractorDirect(val));
					code >> c;
					return exDirect;
				}
				case 'C':
				{
					code >> c;
					u_ptr<Extractor<Unit>> eU = buildUnitExtractor(code);
					u_ptr<Extractor<float>> exC(new ExtractorC(toDigit(c), eU));
					return exC;
				}				
				case 'D':
				{
					u_ptr<Extractor<Unit>> eU = buildUnitExtractor(code);
					u_ptr<Extractor<Point>> eP = buildPointExtractor(code);
					u_ptr<Extractor<float>> exD(new ExtractorD(eU, eP));
					return exD;
				}				
				case 'M':
				{
					code >> c;
					if (c == 'D'){
						u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
						u_ptr<Extractor<Point>> eP = buildPointExtractor(code);
						u_ptr<Extractor<float>> exMD(new ExtractorMD(eA, eP));
						return exMD;
					}
					else{
						u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
						u_ptr<Extractor<float>> exM(new ExtractorM(toDigit(c), eA));
						return exM;
					}
				}
				case 'm':
				{
					code >> c;
					if (c == 'D'){
						u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
						u_ptr<Extractor<Point>> eP = buildPointExtractor(code);
						u_ptr<Extractor<float>> exmD(new ExtractormD(buildArmyExtractor(code), buildPointExtractor(code)));
						return exmD;
					}
					else{
						u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
						u_ptr<Extractor<float>> exm(new Extractorm(toDigit(c), eA));
						return exm;
					}
				}
				case 'a':
				{
					code >> c;
					if (c == 'D'){
						u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
						u_ptr<Extractor<Point>> eP = buildPointExtractor(code);
						u_ptr<Extractor<float>> exaD(new ExtractoraD(eA, eP));
						return exaD;
					}
					else{
						u_ptr<Extractor<Army>> eA = buildArmyExtractor(code);
						u_ptr<Extractor<float>> exa(new Extractora(toDigit(c), eA));
						return exa;
					}
				}
				default:
					return nullptr;
			}
		}
};
#endif //_EXTRACTORBUILDER_H_