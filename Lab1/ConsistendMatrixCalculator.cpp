#include "stdafx.h"
#include "ConsistendMatrixCalculator.h"

Matrix CConsistendMatrixCalculator::GetAdditionalMatrix(const Matrix & matrix, Matrix & result)
{
	return GetAdditionalMatrix(matrix, result, Vector2UL(), Vector2UL(matrix.size(), matrix[0].size()));
}

Matrix CConsistendMatrixCalculator::GetAdditionalMatrix(const Matrix & matrix, Matrix & result, Vector2UL start, Vector2UL end)
{
	for (size_t y = start.y; y < end.y; ++y)
	{
		for (size_t x = start.x; x < end.x; ++x)
		{
			size_t first = x - start.x;
			size_t second = y - start.y;

			result[second][first] = GetMinor(matrix, x, y);
		}
	}
	return result;
}

double CConsistendMatrixCalculator::GetMinor(const Matrix & matrix, size_t x, size_t y)
{
	Matrix subMatrix;
	size_t widthMinor = matrix.size() - 1;
	size_t heightMinor = matrix[0].size() - 1;

	if (matrix.size() == 1)
	{
		return matrix[y][x];
	}

	subMatrix.resize(heightMinor);
	for (size_t index = 0; index < heightMinor; ++index)
	{
		subMatrix[index].resize(widthMinor);
	}

	/////////////////////////////////////////////
	// Set skipPositions
	std::vector<Vector2UL> skipPositions;

	for (size_t i = 0; i <= subMatrix.size(); i++)
	{
		skipPositions.push_back(Vector2UL(i, y));
	}
	for (size_t i = 0; i <= subMatrix[0].size(); i++)
	{
		skipPositions.push_back(Vector2UL(x, i));
	}
	/////////////////////////////////////////////
	size_t sx = 0;
	size_t sy = 0;

	for (size_t my = 0; my <= widthMinor; ++my)
	{
		for (size_t mx = 0; mx <= heightMinor; ++mx)
		{

			if (std::count(skipPositions.begin(), skipPositions.end(), Vector2UL(mx, my)) == 0)
			{
				subMatrix[sy][sx] = matrix[my][mx];

				// Расчёт индексов для нового минора
				sx++;
				if (sx > (heightMinor - 1))
				{
					sx = 0;
					sy++;
					if (sy > (widthMinor - 1))
					{
						sy = 0;
					}
				}
			}

		}
	}

	return GetDeterminate(subMatrix, x, y);
}

double CConsistendMatrixCalculator::GetDeterminate(const Matrix & matrix, size_t x, size_t y)
{
	double determinate = 0;
	size_t sizeMatrix = matrix.size();

	size_t countForDegree = x + y + 2;// because compute position from zero
	float power = pow(-1.f, countForDegree);


	if (sizeMatrix != 1)
	{
		for (size_t i = 0; i < sizeMatrix; i++)
		{
			determinate += matrix[0][i] * pow(-1.f, countForDegree) * GetMinor(matrix, i, 0);
			countForDegree++;
		}
	}
	else if (sizeMatrix == 2)// TODO : fix -
	{
		determinate = ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));// for more 3 :  pow(-1.f, countForDegree) 
	}
	else if (sizeMatrix == 1)
	{
		determinate = matrix[0][0];//
	}

	return determinate;
}
