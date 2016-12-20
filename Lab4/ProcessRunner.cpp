#include "stdafx.h"
#include "ProcessRunner.h"

CProcessRunner::CProcessRunner()
{
}

CProcessRunner::~CProcessRunner()
{
	CloseChannels();
}

void CProcessRunner::Run(size_t processesNumber, size_t amountIteration)
{
	m_inputChannels.resize(processesNumber, CPipe());
	m_outputChannels.resize(processesNumber, CNamedPipe());

	WaitClients();
	WaitAndRunClients();
	WaitMessages();
}

void CProcessRunner::CloseChannels()
{
	for (size_t index = 0; index < m_inputChannels.size(); ++index)
	{
		m_inputChannels[0].Close();
		m_outputChannels[0].Close();
	}
}

void CProcessRunner::WaitClients()
{
	std::cout << "Wait clients" << std::endl;
	for (size_t index = 0; index < m_inputChannels.size(); index++)
	{
		while (!m_inputChannels[index].Open(NAME_PIPE + std::to_string(index)))
		{
		}
		while (!m_outputChannels[index].Open(NAME_PIPE + std::to_string(index) + "0"))
		{

		}
		std::cout << "Client " << index  << " is connect"<< std::endl;
	}


}

void CProcessRunner::WaitAndRunClients()
{
	std::string message;
	while (message != RUN_MESSAGE)
	{
		std::cout << "For run clients print \"r\""<< std::endl;
		std::cin >> message;
	}
	
	int run = READRY_MESSAGE;
	for (size_t index = 0; index < m_inputChannels.size(); index++)
	{
		while (!m_inputChannels[index].WriteBytes(&run, sizeof(run)))
		{
		}

	}
}

void CProcessRunner::WaitMessages()
{
	std::vector<std::string> messages;
	WaitPackage(messages);

	for (auto const &message : messages)
	{
		std::cout << message << std::endl;
	}
}



std::string CProcessRunner::GetCommandLineArguments(std::string exeName, size_t amountIteration, size_t processesNumber)
{
	std::string name = exeName + ".exe "
		+ std::to_string(amountIteration) + " "
		+ std::to_string(processesNumber);
	return name;
}



void CProcessRunner::WaitPackage(std::vector<std::string> &messages)
{
	//CPostman::SendPackage(messages, messages.size());
	//*
	for (size_t index = 0; index < m_inputChannels.size(); ++index)
	{
		char buffer[BUFFER_PIPE_SIZE] = "";

		while (!m_outputChannels[index].ReadBytes(buffer, BUFFER_PIPE_SIZE))
		{
		}

		//m_outputChannels[index].ReadBytes(buffer, BUFFER_PIPE_SIZE);
		messages.push_back(buffer);

		m_outputChannels[index].Close();

	}

	//*/
}