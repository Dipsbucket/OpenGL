#pragma once
#include <iostream>
#include <string>

class hasName
{
	public:
	std::string name;

	virtual std::string getName();
	virtual const char* getNameAsChar();
	virtual std::string toString();
};
