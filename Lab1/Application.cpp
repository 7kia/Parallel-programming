#include "stdafx.h"
#include "Application.h"

#include <array>

#include <string>

#include <stdio.h>
#include <time.h>

// For timer
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

void RunProgram(int argc, char * argv[])
{
	CheckParametrs(argc);
	
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

	CMultithreadMatrixCalculator matrixCalculator;

	size_t amountThread = size_t(atoi(argv[1]));
	size_t amountCpu = size_t(atoi(argv[2]));

	matrixCalculator.SetAmountThread(amountThread);
	matrixCalculator.SetAmountCpu(amountCpu);

	boost::timer::cpu_timer timer;

	timer.start();

	matrixCalculator.ComputeMinorsMatrix(INPUT_MATRIX);

	timer.stop();

	double time = timer.elapsed().user * pow(10.f, -9.f) / amountThread;
	std::cout << boost::timer::format(timer.elapsed(), ROUNDING_NUMBER, "%u") << std::endl;

}

void CheckParametrs(int argc)
{
	if (argc != AMOUNT_ARGUMENTS)
	{
		throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS + to_string(AMOUNT_ARGUMENTS));
	}
}

