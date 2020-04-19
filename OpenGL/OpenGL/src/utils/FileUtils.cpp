#include "FileUtils.h"

std::string FileUtils::parseFile(const std::string& filePath)
{
	std::string res("Empty file");
	if (!filePath.empty())
	{
		std::ifstream stream(filePath);
		std::string line;

		std::stringstream sStream;
		while (getline(stream, line))
		{
			sStream << line << '\n';
		}

		res = sStream.str();
	}

	return res;
}