#pragma once
#include <iostream>
#include <string>

class hasName
{
	public:
	virtual std::string getName() = 0;
	virtual const char* getNameAsChar() = 0;
	virtual std::string toString() = 0;
};
