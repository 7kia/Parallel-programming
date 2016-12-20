#include "stdafx.h"
#include "ProcessRunner.h"

CProcessRunner::CProcessRunner()
{
}

void CProcessRunner::Run(size_t processesNumber, size_t amountIteration)
{
	m_pipes.resize(processesNumber, CNamedPipe());


	WaitClients();
	WaitAndRunClients();
	WaitMessages();
}

void CProcessRunner::WaitClients()
{
	std::cout << "Wait clients" << std::endl;
	for (size_t index = 0; index < m_pipes.size(); index++)
	{
		while (!m_pipes[index].Open(NAME_PIPE + std::to_string(index)))
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

	for (size_t index = 0; index < messages.size(); ++index)
	{

		char buffer[BUFFER_PIPE_SIZE] = "";
		m_pipes[index].ReadBytes(buffer, BUFFER_PIPE_SIZE);
		messages.push_back(buffer);

		m_pipes[index].Close();

	}
}