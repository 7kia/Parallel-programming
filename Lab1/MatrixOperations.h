#pragma once

#include <vector>
#include <iomanip>// for setw()
#include <fstream>
#include <iostream>
#include "ConsistendMatrixCalculator.h"

namespace MatrixOperations
{
	static const std::string MESSAGE_ZERO_DETERMINATE = "Determinate the matrix = 0!";

	void	PrintMatrix(const Matrix & matrix, std::ostream & str);

}