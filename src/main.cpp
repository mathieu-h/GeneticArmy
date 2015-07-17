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

void unitTest()
{

}

int main(void)
{
    std::srand(static_cast<unsigned int>(time(nullptr)));

	// TEST FOR SPLIT
	//std::cout << "toto" << std::endl;
	//std::stringstream code;
	//code << "?C1<C3!EB?C2>C4!EB!AN1";
	//std::string strFull = code.str();
	//std::vector<std::string> strs;
	//boost::split(strs, strFull, boost::is_any_of("?!<>"));
	//std::string firstChildCode = strs.at(1);
	//std::string secondChildCode = strs.at(2);

	//std::cout << strFull << std::endl;
	////std::cout << strFull << std::endl;
	//std::cout << firstChildCode << std::endl;
	//std::cout << secondChildCode << std::endl;

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