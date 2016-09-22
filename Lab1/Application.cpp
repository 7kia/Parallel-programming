#include "stdafx.h"
#include "Application.h"

using namespace std;

void RunProgram(int argc, char * argv[])
{
	CheckParametrs(argc);
	
	//Matrix INPUT_MATRIX;
	//MatrixOperations::FillMatrixFromFile(argv[1], INPUT_MATRIX);

	boost::timer::cpu_timer timer;

	timer.start();
	CompputeAdditionalMatrixAndPrint(INPUT_MATRIX, cout);
	timer.stop();

	std::cout << boost::timer::format(timer.elapsed(), ROUNDING_NUMBER, "%u") << std::endl;

}

void CompputeAdditionalMatrixAndPrint(const Matrix & matrix, std::ostream & strm)
{
	Matrix additionalMatrix;
	Vector2UL start(0, 0);
	Vector2UL end(matrix.size(), matrix.size());
	additionalMatrix.resize(end.y - start.y, MatrixRow(end.x - start.x));

	additionalMatrix = MatrixOperations::GetAdditionalMatrix(matrix, additionalMatrix);

	MatrixOperations::PrintMatrix(additionalMatrix, strm);
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

	if ((width != height) || (width == 0) || (height == 0))
	{
		throw std::runtime_error("Matrix must have size more zero and be square");
	}

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