#pragma once

#include <vector>
#include <string>
#include <Windows.h>
#include <ctime>
#include <string>
#include <iostream>

#include "../Pipe.h"

class CTaskExecutor
{
public:
	CTaskExecutor();
	~CTaskExecutor();

	
		
	
//////////////////////////////////////////////////////////////////////
// Methods
public:
	double							GetPi(size_t amountIteration, size_t numberProcess);
private:

	static void							PrintFinalResult(size_t amountIteration
													, size_t numberProcess
													, double result);
//////////////////////////////////////////////////////////////////////
// Static Methods
public:
	static size_t		CalculateHits(size_t numIter);

private:

	static double		RandomNumber();
	static bool			InCircle(double x, double y);
//////////////////////////////////////////////////////////////////////
// Data
private:
	size_t			m_amountIterations;
	std::string		m_namePipe;
	CPipe			m_pipe;
};

