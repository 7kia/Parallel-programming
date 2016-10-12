#include "stdafx.h"
#include "MatrixOperations.h"

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
