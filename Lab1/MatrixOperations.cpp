#include "stdafx.h"
#include "MatrixOperations.h"

double MatrixOperations::GetDeterminate(const Matrix &matrix, size_t x, size_t y)
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
	else if(sizeMatrix == 2)// TODO : fix -
	{
		determinate = ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]) );// for more 3 :  pow(-1.f, countForDegree) 
	}
	else if(sizeMatrix == 1)
	{
		determinate = matrix[0][0];//
	}

	return determinate;
}

double MatrixOperations::GetSecondDeterminate(const Matrix & matrix, size_t x, size_t y)
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

	Matrix copy = subMatrix;
	for (size_t j = 0; j < copy.size(); ++j)
	{
		for (size_t i = j + 1; i < copy.size() - 1; ++i)
		{


			for (size_t index = 0; index < copy.size(); ++index)
			{
				copy[i][index] -= copy[j][i] / copy[j][j] * copy[j][index];
			}

		}
	}

	double result = 1;
	bool seeOtherDiagonal = false;
	for (size_t index = 0; index < copy.size(); ++index)
	{
		if (copy[index][index] == 0.f)
		{
			seeOtherDiagonal = true;
			break;
		}
		result *= copy[index][index];
	}

	if (seeOtherDiagonal)
	{
		size_t secondIndex = 0;
		for (int index = copy.size() - 1; index >= 0; --index)
		{
			if (copy[secondIndex][index] == 0.f)
			{
				break;
			}
			result *= copy[secondIndex++][index];
		}
	}

	return result;
}


// work for 3X3 matrixs
double MatrixOperations::GetMinor(const Matrix &matrix , size_t x , size_t y)
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
		skipPositions.push_back(Vector2UL(i , y));
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

	return MatrixOperations::GetDeterminate(subMatrix, x, y);
}

Matrix MatrixOperations::GetMinorMatrix(const Matrix & matrix)
{
	Matrix minorMatrix;
	const size_t sizeMinorMatrix = matrix.size();
	minorMatrix.resize(sizeMinorMatrix);

	for (size_t index = 0; index < sizeMinorMatrix; index++)
	{
		minorMatrix[index].resize(sizeMinorMatrix);
	}

	int countForDegree = 2;
	for (size_t y = 0; y < sizeMinorMatrix; y++)
	{
		for (size_t x = 0; x < sizeMinorMatrix; x++)
		{
			minorMatrix[y][x] = pow(-1 , countForDegree) * GetMinor(matrix , x , y);
			countForDegree++;
		}
	}

	return minorMatrix;
}

Matrix MatrixOperations::GetTransposeMatrix(const Matrix & matrix)
{
	Matrix transposeMatrix = matrix;
	const size_t sizeTransposeMatrix = matrix.size();
	for (size_t y = 0; y < sizeTransposeMatrix; y++)
	{
		for (size_t x = y; x < sizeTransposeMatrix; x++)
		{		
			std::swap(transposeMatrix[y][x] , transposeMatrix[x][y]);
		}
	};

	return transposeMatrix;
}

Matrix MatrixOperations::GetInvertMatrix(const Matrix & matrix)
{
	const double determinate = MatrixOperations::GetDeterminate(matrix, 1, 1);// TODO : delete the function

	if (determinate != 0)
	{
		Matrix transposeMatrix = MatrixOperations::GetTransposeMatrix(matrix);
		Matrix minorMatrix = MatrixOperations::GetMinorMatrix(transposeMatrix);

		for (auto &DataForProgram : minorMatrix)
		{
			for (auto &element : DataForProgram)
			{
				element /= determinate;
			}
		}

		return minorMatrix;
	}	
	throw std::invalid_argument(MESSAGE_ZERO_DETERMINATE);
}


Matrix MatrixOperations::GetAdditionalMatrix(const Matrix & matrix, Matrix & result)
{
	return GetAdditionalMatrix(matrix, result, Vector2UL(), Vector2UL(matrix.size(), matrix[0].size()));
}

Matrix MatrixOperations::GetAdditionalMatrix(const Matrix & matrix, Matrix & result, Vector2UL start, Vector2UL end)
{

	for (size_t y = start.y; y < end.y; ++y)
	{
		for (size_t x = start.x; x < end.x; ++x)
		{
			size_t first =  x - start.x;
			size_t second = y -  start.y ;

			result[second][first] = GetMinor(matrix, x, y);
		}
	}
	return result;
}


void MatrixOperations::PrintMatrix(const Matrix &matrix, std::ostream & str)
{
	str << std::setprecision(3);
	for (auto &DataForProgram : matrix)
	{
		for (auto &element : DataForProgram)
		{
			str << element << " ";
		}
		str << std::endl;
	}
}
