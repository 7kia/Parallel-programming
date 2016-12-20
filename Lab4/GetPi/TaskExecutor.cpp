#include "stdafx.h"
#include "TaskExecutor.h"

CTaskExecutor::CTaskExecutor(size_t numberProcess)
	: m_numberProcess(numberProcess)
{
	m_outputChannel.Open(NAME_PIPE + std::to_string(m_numberProcess) );

}

CTaskExecutor::~CTaskExecutor()
{
	m_inputChannel.Close();
	m_outputChannel.Close();
}

void CTaskExecutor::WaitCommand()
{
	int message = READRY_MESSAGE;

	while (!m_outputChannel.ReadBytes(&message, sizeof(message)))//!m_outputChannel.ReadBytes(&message, sizeof(message)))
	{
		Sleep(1000);
	}

	if (message != READRY_MESSAGE)
	{
		throw std::runtime_error("Incorrect message");
	}
}

double CTaskExecutor::GetPi(size_t amountIteration)
{
	srand(UINT(m_numberProcess));// TODO : transfer to other place

	double result =  4.0 * CalculateHits(amountIteration) / amountIteration;

	std::string message = GetFinalMessage(amountIteration, result);

	//m_inputChannel
	m_inputChannel.Open(NAME_PIPE + std::to_string(m_numberProcess) + "0");

	m_inputChannel.WriteBytes(message.data(), message.size());

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
std::string CTaskExecutor::GetFinalMessage(size_t amountIteration, double result)
{
	std::string message = "Id process "
		+ std::to_string(m_numberProcess) + "\n"
		+ "Amount iteration = " + std::to_string(amountIteration) + "\n"
		+ "Result = " + std::to_string(result) + "\n";

	return message;
}