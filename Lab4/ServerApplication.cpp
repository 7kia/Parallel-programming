#include "stdafx.h"
#include "ServerApplication.h"

CServerApplication::CServerApplication()
{
}

CServerApplication::~CServerApplication()
{
	CloseChannels();
}

void CServerApplication::Run(size_t processesNumber, size_t amountIteration)
{
	m_inputChannels.resize(processesNumber, CPipe());
	m_outputChannels.resize(processesNumber, CNamedPipe());

	WaitClients();
	WaitAndRunClients();
	WaitMessages();
}

void CServerApplication::CloseChannels()
{
	for (size_t index = 0; index < m_inputChannels.size(); ++index)
	{
		m_inputChannels[0].Close();
		m_outputChannels[0].Close();
	}
}

void CServerApplication::WaitClients()
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

void CServerApplication::WaitAndRunClients()
{
	std::string message;
	while (message != RUN_MESSAGE)
	{
		std::cout << "For run clients print \"r\""<< std::endl;
		std::cin >> message;
	}
	
	int run = READY_MESSAGE;
	for (size_t index = 0; index < m_inputChannels.size(); index++)
	{
		while (!m_inputChannels[index].WriteBytes(&run, sizeof(run)))
		{
		}

	}
}

void CServerApplication::WaitMessages()
{
	std::vector<std::string> messages;
	WaitPackage(messages);

	for (auto const &message : messages)
	{
		std::cout << message << std::endl;
	}
}



std::string CServerApplication::GetCommandLineArguments(std::string exeName, size_t amountIteration, size_t processesNumber)
{
	std::string name = exeName + ".exe "
		+ std::to_string(amountIteration) + " "
		+ std::to_string(processesNumber);
	return name;
}



void CServerApplication::WaitPackage(std::vector<std::string> &messages)
{
	for (size_t index = 0; index < m_inputChannels.size(); ++index)
	{
		char buffer[BUFFER_PIPE_SIZE] = "";

		while (!m_outputChannels[index].ReadBytes(buffer, BUFFER_PIPE_SIZE))
		{
		}
		messages.push_back(buffer);
	}
}