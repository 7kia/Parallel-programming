#pragma once

class CTaskExecutor
{
public:
	CTaskExecutor(HANDLE & mutex);
	~CTaskExecutor();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	double GetPi(size_t amountProcess, size_t amountIteration) const;
private:
	static double	RandomNumber();
	static bool		InCircle(double x, double y);
	static int		CalculateHits(size_t numIter);
//////////////////////////////////////////////////////////////////////
// Data
private:
	HANDLE& m_mutex;
};

