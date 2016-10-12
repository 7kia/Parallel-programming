#pragma once

#include <vector>
#include "MyStructs.h"

typedef std::vector<double> MatrixRow;
typedef std::vector<MatrixRow> Matrix;

class CConsistendMatrixCalculator
{
public:
	// Place for constructor and destructor
//////////////////////////////////////////////////////////////////////
// Methods
public:
	Matrix	GetAdditionalMatrix(const Matrix &matrix
								, Matrix & result);
	Matrix	GetAdditionalMatrix(const Matrix &matrix
								, Matrix & result
								, Vector2UL start
								, Vector2UL end);

//////////////////////////////////////////////////////////////////////
// Methods
private:
	double	GetMinor(const Matrix &matrix, size_t x, size_t y);
	double	GetDeterminate(const Matrix &matrix, size_t x, size_t y);

//////////////////////////////////////////////////////////////////////
// Data
private:
};