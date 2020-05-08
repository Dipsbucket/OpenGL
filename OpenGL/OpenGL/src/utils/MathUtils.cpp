#include "MathUtils.h"

void MathUtils::mat4ToArray(float** arrayPointer, glm::mat4 value)
{
	//	// Initialisation de l'array en param�tre
	for (int i = 0; i < 4; i++)
	{
		arrayPointer[i] = new float[4];
	}

	const float* valuePointer = (const float*)glm::value_ptr(value);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arrayPointer[j][i] = valuePointer[4 * i + j];
		}
	}
}

bool MathUtils::isIdentity(float** arrayPointer, int dimension)
{
	bool res = true;
	for (int i = 0; i < 4; i++)
	{
		// La diagonale doit �tre compos�e de 1
		if (arrayPointer[i][i] != 1.0f)
		{
			res = false;
			break;
		}

		float sum = 0.0f;
		for (int j = 0; j < 4; j++)
		{
			sum += arrayPointer[i][j];
		}

		// La somme des lignes doit �tre 1
		if (sum != 1.0f)
		{
			res = false;
			break;
		}
	}

	return res;
}