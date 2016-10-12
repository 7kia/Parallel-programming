#include "stdafx.h"
#include "MultithreadMatrixCalculator.h"

namespace
{
	DWORD WINAPI ComputeMinorsMatrix(void* data)
	{
		//auto data = static_cast<std::pair<CMultithreadMatrixCalculator*, int>*>(pvParam);
		//return data->first->CalculateLine((PVOID)&data->second);

		auto pP = static_cast<CMultithreadMatrixCalculator::DataForThread*>(data);
		CMultithreadMatrixCalculator* pCalc = static_cast<CMultithreadMatrixCalculator::DataForThread*>(data)->pCalc;
		CMultithreadMatrixCalculator::DataForProgram *pData = &pCalc->m_data;

		//преобразуем полученные данные к типу структуры
		//DataForProgram *pData = &m_data;

		pData->output.resize(pData->endMatrix.y - pData->startMatrix.y + 1, MatrixRow(pData->endMatrix.x - pData->startMatrix.x + 1));
		pCalc->GetAdditionalMatrix(*pData->input, pData->output, pData->startMatrix, pData->endMatrix);

		return 0;
	}
}

std::vector<int> CMultithreadMatrixCalculator::GetAffinityMasks() const
{
	std::vector<int> masks;
	for (size_t i = 0; i < m_amountThread; i++)
	{
		masks.push_back(GetAffinityMask(i));
	}
	return masks;
}

int CMultithreadMatrixCalculator::GetAffinityMask(int threadIndex) const
{
	int mask = 0x0000;
	if (m_amountThread / m_amountCpu == 0)
	{
		return 1;
	}

	int cpuIndex = (threadIndex) / (m_amountThread / m_amountCpu);
	if ((m_amountThread % m_amountCpu == 1) && (cpuIndex > 0))
	{
		cpuIndex--;
	}
	return int(pow(2.f, cpuIndex));
}

void CMultithreadMatrixCalculator::SetAmountThread(size_t value)
{
	m_amountThread = value;
}

void CMultithreadMatrixCalculator::SetAmountCpu(size_t value)
{
	m_amountCpu = value;
}

Matrix CMultithreadMatrixCalculator::ComputeMinorsMatrix(const Matrix & matrix)
{
	CreateThreads(matrix);

	for (size_t i = 0; i < m_amountThread; i++)
	{
		ResumeThread(thread[i]);
	}

	// ждем, пока все эти потоки завершатся
	WaitForMultipleObjects(m_amountThread, thread.data(), TRUE, INFINITE);

	return Matrix();
}


DWORD WINAPI CMultithreadMatrixCalculator::ComputeMinorsMatrix()
{
	//преобразуем полученные данные к типу структуры
	DataForProgram *pData = &m_data;

	m_data.output.resize(m_data.endMatrix.y - m_data.startMatrix.y + 1, MatrixRow(m_data.endMatrix.x - m_data.startMatrix.x + 1));
	GetAdditionalMatrix(*m_data.input, m_data.output, m_data.startMatrix, m_data.endMatrix);

	return 0;
}

void CMultithreadMatrixCalculator::CreateThreads(const Matrix & matrix)
{
	m_data.input = &matrix;
	size_t sizeSourceMatrix = m_data.input->size();
	size_t SIZE_SECTION = sizeSourceMatrix / m_amountThread * size_t(2);

	//определяем дескрипторы потоков,
	//идентификаторы потоков и структуры для строк матрицы
	thread.resize(m_amountThread);
	thrId.resize(m_amountThread);

	DataForThread sourcesData;
	sourcesData.data.input = m_data.input;
	sourcesData.data.output.resize(sizeSourceMatrix, MatrixRow(sizeSourceMatrix));

	m_dataForThread.resize(m_amountThread);
	for (size_t i = 0; i < m_amountThread; i++)
	{
		//создаем потоки
		Vector2UL startMatrix = Vector2UL((i * SIZE_SECTION) % sizeSourceMatrix
			, (i * SIZE_SECTION) / sizeSourceMatrix * SIZE_SECTION);

		Vector2UL endMatrix = startMatrix;
		endMatrix.x += SIZE_SECTION - 1;
		endMatrix.y += SIZE_SECTION - 1;

		m_dataForThread[i].pCalc = this;
		m_dataForThread[i].data.startMatrix = startMatrix;
		m_dataForThread[i].data.endMatrix = endMatrix;

		//////////////////////////////////
		// Record from source matrix
		m_dataForThread[i].data.input = m_data.input;
		m_dataForThread[i].data.output.resize(SIZE_SECTION, MatrixRow(SIZE_SECTION));


		//m_dataForThread[i].input = 
		//////////////////////////////////
		// TODO : rewrite value

		thread[i] = CreateThread(NULL, 0, &::ComputeMinorsMatrix, &m_dataForThread[i], CREATE_SUSPENDED, NULL);
		SetThreadAffinityMask(thread[i], GetAffinityMask(i));

	}
}

