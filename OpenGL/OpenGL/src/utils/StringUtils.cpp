#include "StringUtils.h"

std::string StringUtils::mat4toString(glm::mat4& mat)
{
	// TODO JT : au propre
	float matrix[4][4];

	const float* pSource = (const float*)glm::value_ptr(mat);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix[j][i] = pSource[4 * i + j];
		}
	}

	std::string res = "";
	for (int i = 0; i < 4; i++)
	{
		res.append("(" + std::to_string(i) + ") [");
		for (int j = 0; j < 4; j++)
		{
			res.append(std::to_string(matrix[i][j]));
			if (j != 3)
			{
				res.append(", ");
			}
		}
		res.append("]\n");
	}

	return res;
}