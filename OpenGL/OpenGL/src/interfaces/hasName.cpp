#include "hasName.h"

std::string hasName::getName()
{
	return this->name;
}

const char* hasName::getNameAsChar()
{
	return this->name.c_str();
}

std::string hasName::toString()
{
	return this->name;
}