#pragma once

#include <vector>
#include <string>
#include <Windows.h>
#include <ctime>

class CTaskExecutor
{
public:
	CTaskExecutor(HANDLE & mutex);
	~CTaskExecutor();

	struct SDataForThread
	{
		size_t result;
		size_t amountIterations;
	};
//////////////////////////////////////////////////////////////////////
// Methods
public:
	double							GetPi(size_t amountProcess
										, size_t amountIteration
										, size_t amountCpu);
private:

	void							CreateThreads();
	void							ResumeThreads();
	void							PrintThreadInformation();
	void							PrintFinalResult();
//////////////////////////////////////////////////////////////////////
// Static Methods
public:
	static size_t		CalculateHits(size_t numIter);

private:
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);

	static double		RandomNumber();
	static bool			InCircle(double x, double y);
	static int			GetAffinityMask(size_t amountThread
										, size_t threadIndex
										, size_t amountCpu);
//////////////////////////////////////////////////////////////////////
// Data
private:
	HANDLE& m_mutex;
	std::vector<HANDLE>				m_threads;
	std::vector<SDataForThread>		m_dataForThreads;

	size_t							m_amountCpu = 1;
	size_t							m_amountProcess = 1;
	size_t							m_amountIteration = 1;

};

