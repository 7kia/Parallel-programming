#include "stdafx.h"
#include "TaskExecutor.h"

CTaskExecutor::CTaskExecutor(HANDLE & mutex)
	: m_mutex(mutex)
{
}


CTaskExecutor::~CTaskExecutor()
{
	CloseHandle(m_mutex);
}

double CTaskExecutor::GetPi(size_t amountProcess
	, size_t amountIteration
	, size_t amountCpu)
{
	m_amountProcess = amountProcess;
	m_amountIteration = amountIteration;
	m_amountCpu = amountCpu;
	if (m_amountProcess == 1)
	{
		return 4.0 * CalculateHits(m_amountIteration) / m_amountIteration;
	}

	CreateThreads();
	ResumeThreads();

	PrintThreadInformation();
	PrintFinalResult();

	return 0;
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
int CTaskExecutor::GetAffinityMask(size_t amountThread
	, size_t threadIndex
	, size_t amountCpu)
{
	int mask = 0x0000;

	if (amountThread / amountCpu == 0)
	{
		return 1;
	}

	int cpuIndex = (threadIndex) / (amountThread / amountCpu);
	if ((amountThread % amountCpu == 1) && (cpuIndex > 0))
	{
		cpuIndex--;
	}
	return int(pow(2.f, cpuIndex));
}

void CTaskExecutor::CreateThreads()
{
	_TCHAR exePath[MAX_PATH];
	if (GetModuleFileName(NULL, exePath, MAX_PATH) == 0)
	{
		throw std::runtime_error("GetModuleFileName failed. Error " + GetLastError());
	}

	m_dataForThreads.resize(m_amountProcess);
	for (size_t index = 0; index < m_amountProcess; ++index)
	{
		auto & data = m_dataForThreads[index];
		data.amountIterations = m_amountIteration / m_amountProcess;
		data.idThread = index;
		data.namePipe = exePath;

		m_threads.push_back(CreateThread(NULL, 0, &ThreadFunction, &data, CREATE_SUSPENDED, NULL));
		SetThreadAffinityMask(m_threads.back(), GetAffinityMask(m_amountProcess, index, m_amountCpu));
	}
}

void CTaskExecutor::ResumeThreads()
{
	for (auto & thread : m_threads)
	{
		ResumeThread(thread);
	}
	// ждем, пока все эти потоки завершатся
	WaitForMultipleObjects(m_threads.size(), m_threads.data(), TRUE, INFINITE);
}

void CTaskExecutor::PrintThreadInformation()
{
	for (size_t index = 0; index < m_dataForThreads.size(); ++index)
	{
		size_t result;
		
		m_dataForThreads[index].pipe.Open(m_dataForThreads[index].namePipe);
		m_dataForThreads[index].pipe.ReadBytes(&result, sizeof(size_t));
		m_commonAmountIteration += result;

		std::cout << "Id thread " << std::to_string(index) << std::endl
			<< "Amount iteration = " << std::to_string(m_dataForThreads[index].amountIterations) << std::endl
			<< "Result(amount hit) = " << result << std::endl
			<< std::endl;
	}
}

void CTaskExecutor::PrintFinalResult()
{
	std::cout << "Final result "
		<< std::to_string(4.0 * m_commonAmountIteration / m_amountIteration)
		<< std::endl;
}

DWORD CTaskExecutor::ThreadFunction(LPVOID lpParam)
{
	auto pDataForThread = (SDataForThread*)(lpParam);
	srand(time(NULL));// TODO : transfer to other place

	//pDataForThread->pipe.Open("Pipe" + std::to_string(pDataForThread->idThread) + ".txt");
	pDataForThread->namePipe = "Pipe" + std::to_string(pDataForThread->idThread) + ".txt";
	pDataForThread->pipe.Open(pDataForThread->namePipe);

	size_t result = CalculateHits(pDataForThread->amountIterations);
	//pDataForThread->pipe.ReadBytes(&result, sizeof(size_t));
	//char *buffer = reinterpret_cast<char *>(result);
	//auto stringPresentation = std::to_string(result);
	//const char *buffer = stringPresentation.data();
	pDataForThread->pipe.WriteBytes(&result, sizeof(size_t));
	pDataForThread->pipe.Close();
	return 0;
}
