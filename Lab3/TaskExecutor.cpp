#include "stdafx.h"
#include "TaskExecutor.h"

CTaskExecutor::CTaskExecutor(HANDLE & mutex)
	:m_mutex(mutex)
{
}


CTaskExecutor::~CTaskExecutor()
{
	CloseHandle(m_mutex);
}

double CTaskExecutor::GetPi(size_t amountProcess, size_t amountIteration) const
{
	return 4.0 * CalculateHits(amountIteration) / amountIteration;
}

double CTaskExecutor::RandomNumber()
{
	return double(rand()) / RAND_MAX;
}

bool CTaskExecutor::InCircle(double x, double y)
{
	return (x*x + y*y) <= 1;
}

int CTaskExecutor::CalculateHits(size_t numIter)
{
	size_t numHits = 0;
	for (size_t index = 0; index < numIter; ++index)
	{
		numHits += InCircle(RandomNumber(), RandomNumber());// TODO : see can it replace to boost function
	}
	return numHits;
}

