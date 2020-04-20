#pragma once
#include <string>
#include <vector>
#include <sstream>

class StringUtils
{
	public:
	template <class T> static std::string toString(std::vector<T> value);
	template <class T> static T parseString(std::string value);
};

template<class T>
inline std::string StringUtils::toString(std::vector<T> value)
{
	std::string res("Empty vector");
	if (!value.empty())
	{
		std::ostringstream vts;

		// On add le dernier �l�ment apr�s pour pas add la "," durant l'it�ration du stream
		std::copy(value.begin(), value.end() - 1, std::ostream_iterator<T>(vts, ", "));
		vts << value.back();

		res = vts.str();
	}

	return res;
}

template<class T>
inline T StringUtils::parseString(std::string value)
{
	return T();
}

template< >
inline const char* StringUtils::parseString(std::string value)
{
	if (!value.empty())
	{
		char* res = new char[value.length() + 1];
		std::strcpy(res, value.c_str());
		return res;
	}

	return nullptr;
}