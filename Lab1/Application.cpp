#include "stdafx.h"
#include "Application.h"

using namespace std;

void RunProgram(int argc, char * argv[])
{
	CheckParametrs(argc);
	
	Matrix inputMatrix;
	MatrixOperations::FillMatrixFromFile(argv[1], inputMatrix);

	Matrix invertMatrix = MatrixOperations::GetAdditionalMatrix(inputMatrix);

	MatrixOperations::PrintMatrix(invertMatrix);	
}

void CheckParametrs(int argc)
{
	if (argc != AMOUNT_ARGUMENTS)
	{
		throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS + to_string(AMOUNT_ARGUMENTS));
	}
}

void MatrixOperations::FillMatrixFromFile(string nameFile, Matrix &matrix)
{
	ifstream inputFile;
	inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	inputFile.open(nameFile);
	if (!inputFile.is_open())
	{
		throw MESSAGE_FAILED_OPEN + nameFile + MESSAGE_FAILED_OPEN_FOR_READING;
	}

	size_t width;
	size_t height;
	inputFile >> width;
	inputFile >> height;

	MatrixRow row;
	for (size_t y = 0; y < width; y++)
	{
		for (size_t x = 0; x < height; x++)
		{
			double addNumber = 0;
			inputFile >> addNumber;
			row.push_back(addNumber);
		}
		matrix.push_back(row);
		row.clear();
	}

	/*
		if (!inputFile.eof())
	{
		string passString;
		inputFile >> passString;
		if (!passString.empty())
		{
			throw MESSAGE_INCORRECT_DATA;
		}
	}
	*/

	


}

Matrix MatrixOperations::GetAdditionalMatrix(Matrix & matrix)
{
	Matrix result = matrix;
	for (size_t y = 0; y < matrix.size(); ++y)
	{
		for (size_t x = 0; x < matrix[0].size(); ++x)
		{
			result[y][x] = GetMinor(matrix, x, y);
		}
	}
	return result;
}
