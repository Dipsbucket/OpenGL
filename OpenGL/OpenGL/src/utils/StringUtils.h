#pragma once
#include <string>
#include <iterator>
#include <vector>
#include <sstream>

class StringUtils
{
	public:
	template <class T> static std::string array2dToString(T** arrayPointer);
	template <class T> static std::string vecToString(std::vector<T> value);
	template <class T> static T parseString(std::string value);
};

template<class T>
inline std::string StringUtils::array2dToString(T** arrayPointer)
{
	std::string res = "";
	for (int i = 0; i < 4; i++)
	{
		res.append("(" + std::to_string(i) + ") [");
		for (int j = 0; j < 4; j++)
		{
			res.append(std::to_string(arrayPointer[i][j]));
			if (j != 3)
			{
				res.append(", ");
			}
		}
		res.append("]\n");
	}

	return res;
}

template<class T>
inline std::string StringUtils::vecToString(std::vector<T> value)
{
	std::string res("Empty vector");
	if (!value.empty())
	{
		std::ostringstream vts;

		// On add le dernier élément après pour pas add la "," durant l'itération du stream
		std::copy(value.begin(), value.end() - 1, std::ostream_iterator<T>(vts, ", "));
		vts << value.back();

		res = vts.str();
	}

	return res;
}

template<class T>
inline T StringUtils::parseString(std::string value)
{
	// Non implémenté
	return nullptr;
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