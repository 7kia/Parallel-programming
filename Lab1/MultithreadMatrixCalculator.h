#pragma once

#include "ConsistendMatrixCalculator.h"

#include <Windows.h>

class CMultithreadMatrixCalculator
	: public CConsistendMatrixCalculator
{
public:
	// Place for constructor and destructor

	struct DataForProgram
	{
		const Matrix *input = nullptr;
		Matrix output;

		Vector2UL startMatrix;
		Vector2UL endMatrix;
	};

	struct DataForThread
	{
		CMultithreadMatrixCalculator::DataForProgram data;
		CMultithreadMatrixCalculator* pCalc;
	};

//////////////////////////////////////////////////////////////////////
// Methods
public:
	std::vector<int>	GetAffinityMasks() const;

	void				SetAmountThread(size_t value);
	void				SetAmountCpu(size_t value);

	Matrix				ComputeMinorsMatrix(const Matrix & matrix);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	DataForProgram		m_data;// Need for work threads

//////////////////////////////////////////////////////////////////////
// Methods
private:
	int					GetAffinityMask(int threadIndex) const;

	DWORD WINAPI		ComputeMinorsMatrix();

	void				CreateThreads(const Matrix & matrix);
//////////////////////////////////////////////////////////////////////
// Data
private:
	size_t				m_amountThread = 1;
	size_t				m_amountCpu = 1;

	std::vector<DataForThread> m_dataForThread;
	std::vector<HANDLE> thread;
	std::vector<DWORD>	thrId;

};
