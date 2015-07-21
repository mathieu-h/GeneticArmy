#include "Army.hpp"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <string>     
#include <sstream>
#include "training.hpp"
#include "fstream"

#include "Filters/IFilters.hpp"
#include "boost/algorithm/string.hpp"
#include "IA/TreeIA.hpp"
#include "IA/IACodeGenerator.hpp"

void unitTest()
{

}

int main(void)
{
    std::srand(static_cast<unsigned int>(time(nullptr)));

	 //TEST FOR SPLIT CHAR
	//std::cout << "toto" << std::endl;
	//std::stringstream code;
	//code << "?C1<C3!EB?C2>C4!EB!AN1";
	//std::string strFull = code.str();
	//std::vector<std::string> strs;
	//boost::split(strs, strFull, boost::is_any_of("?!<>"));
	//std::string firstChildCode = strs.at(1);
	//std::string secondChildCode = strs.at(2);
	//std::string thirdChildCode = strs.at(3);
	//std::string fourthChildCode = strs.at(4);
	//std::string fourthChildCode = strs.at(4);

	//char comp = strFull[firstChildCode.size() + 1];

	//std::cout << strFull << std::endl;
	//std::cout << comp << std::endl;
	//std::cout << firstChildCode << std::endl;
	//std::cout << secondChildCode << std::endl;
	//std::cout << thirdChildCode << std::endl;
	//std::cout << fourthChildCode << std::endl;

	//****************************** TEST DE GENERATION DE CODE *****************************************
	//std::string iacodegen = IACodeGenerator::getInstance().GenerateIACode();
	//std::string iacodegen("?C1LDOPU<C4U!ALDOPU?aDOPU<a5O!EBO!N");
	//std::string iacodegen("?DHDABOBA<[86]!MBNLD[71.1]OPU!MPU");
	//std::string iacodegen("?C1LDOPU<[32]!ALDOPU?aDOPU<a5O!EBO!N");
	//std::string iacodegen("?m4O<M2NL5[64.6]A!MBA!MPHDOBO");
	//std::string iacodegen("?DH6OBO<[78]!EPHDAPL0TLD[94]TL6[54]TL4[127]OPHDTHD[26]NLD[98]OPL1OPL4APL2A!AH2A");
	std::string iacodegen("?C6H0THD[103]ABO<MDOPU!MPL6A!MBO");

	//std::cout << iacodegen << std::endl;

	//*************************** TEST DE GENERATION D'ARBRE A PARTIR DU CODE ***************************
	std::stringstream codeSS;
	codeSS << iacodegen;
	TreeIA tree = TreeIA(codeSS);
	std::string iacodetree = tree.getCode();

	
	//std::stringstream codeSS;
	//char c;
	//codeSS << codeTest;
	//codeSS >> c;

	//char c2;
	//codeSS >> c2;

	//std::cout << c << std::endl;
	//std::cout << codeTest << std::endl;
	//std::cout << c2 << std::endl;
	//std::cout << codeSS.str() << std::endl;

	//TreeIA tree = TreeIA(codeSS);
	//std::cout << float((rand() % 99)+(rand() % (1600 - 1200)) / 10.0) << std::endl;

    std::vector<std::unique_ptr<Army> > champions;
    try
    {
        std::ifstream in("Army_10_100.save");
        Army army = Army::load(in);
        std::cout << army << std::endl;
        champions.push_back(std::unique_ptr<Army>(new Army(army)));
    }
    catch(...)
    {
    }

    try
    {
        std::unique_ptr<Army> army = train(10, 100, 20, 10, 100, champions);
        std::cout << *army << std::endl;
        std::ofstream out("Army_10_100.save");
        army->save(out);
        out.flush();
        out.close();
    }
    catch (std::invalid_argument& e)
    {
        std::cout << "toto" << std::endl;
    }

    return 0;
}