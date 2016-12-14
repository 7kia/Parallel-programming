#include "stdafx.h"
#include "TaskExecutor.h"

CTaskExecutor::CTaskExecutor()
{
}

CTaskExecutor::~CTaskExecutor()
{
}

double CTaskExecutor::GetPi(size_t amountIteration, size_t numberProcess)
{
	double result =  4.0 * CalculateHits(amountIteration) / amountIteration;

	CPostman::SendPackage(GetFinalMessage(numberProcess, amountIteration, result), numberProcess);

	return result;
}

double CTaskExecutor::RandomNumber()
{
	return double(rand()) / RAND_MAX;
}

bool CTaskExecutor::InCircle(double x, double y)
{
	return (x*x + y*y) <= 1;
}

size_t CTaskExecutor::CalculateHits(size_t numIter)
{
	size_t numHits = 0;
	for (size_t index = 0; index < numIter; ++index)
	{
		numHits += InCircle(RandomNumber(), RandomNumber());// TODO : see can it replace to boost function
	}
	return numHits;
}

// Evenly distributes indexes on processors
std::string CTaskExecutor::GetFinalMessage(size_t amountIteration
									, size_t numberProcess
									, double result)
{
	std::string message = "Id thread "
		+ std::to_string(numberProcess) + "\n"
		+ "Amount iteration = " + std::to_string(amountIteration) + "\n"
		+ "Result = " + std::to_string(result) + "\n";

	return message;
}