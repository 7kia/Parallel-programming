#pragma once

#include <vector>
#include <iomanip>// for setw()
#include <fstream>
#include <iostream>
#include "MyFunctions.h"

typedef std::vector<double> MatrixRow;
typedef std::vector<MatrixRow> Matrix;

namespace MatrixOperations
{
	static const std::string MESSAGE_ZERO_DETERMINATE = "Determinate the matrix = 0!";

	double	GetDeterminate(const Matrix &matrix, size_t x, size_t y);
	double	GetSecondDeterminate(const Matrix &matrix, size_t x, size_t y);// TODO : rename

	double	GetDeterminate(const Matrix &matrix);

	double	GetMinor(const Matrix &matrix , size_t x , size_t y);
	Matrix	GetMinorMatrix(const Matrix &matrix);
	Matrix	GetTransposeMatrix(const Matrix &matrix);
	Matrix	GetInvertMatrix(const Matrix &matrix);

	void	PrintMatrix(const Matrix & matrix, std::ostream & str);
	void	FillMatrixFromFile(std::string nameFile, Matrix &matrix);

	// TODO : rewrite
	Matrix	GetAdditionalMatrix(const Matrix &matrix, Matrix & result);
	Matrix	GetAdditionalMatrix(const Matrix &matrix, Matrix & result, Vector2UL start, Vector2UL end);
}

// TODO : see can do const
// const
static Matrix INPUT_MATRIX =
{
	{ 1, 3, 0.2, 4, 5, 9, 1, 2 }
	,{ 3, 3, 0.2, 4, 5, 9, 1, 2 }
	,{ 1, 3, 0.2, 4, 5, 9, 1, 2, }
	,{ 3, 3, 0.2, 4, 5, 9, 1, 2, }
	,{ 1, 3, 0.2, 4, 5, 9, 1, 2, }
	,{ 3, 3, 0.2, 4, 5, 9, 1, 2, }
	,{ 1, 3, 2, 4, 5, 9, 10, 2, }
	,{ 3, 3, 0.2, 4, 5, 9, 1, 2, }
};