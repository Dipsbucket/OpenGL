#pragma once
#include <string>

template <class T>
class TypeUtils
{
	public:
	static T parseString(std::string value);
};

template<class T>
inline T TypeUtils<T>::parseString(std::string value)
{
	return T();
}

template<>
inline const char* TypeUtils<const char*>::parseString(std::string value)
{
	if (!value.empty())
	{
		char* res = new char[value.length() + 1];
		std::strcpy(res, value.c_str());
		return res;
	}

	return nullptr;
}
