#ifndef _IAGETTERCODE_HPP_
#define _IAGETTERCODE_HPP_
#pragma once
#include <string>

#define u_ptr std::unique_ptr
#define s_ptr std::shared_ptr

class IAGetterCode
{
public:

	virtual std::string getCode() = 0;

};

#endif