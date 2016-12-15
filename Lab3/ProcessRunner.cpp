#include "stdafx.h"
#include "ProcessRunner.h"

CProcessRunner::CProcessRunner()
{
}

void CProcessRunner::Run(size_t processesNumber, size_t amountIteration)
{
	m_info.processesNumber = processesNumber;
	m_info.amountIteration = amountIteration;

	for (size_t index = 0; index != m_info.processesNumber; ++index)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		ZeroMemory(&pi, sizeof(pi));
		std::string commandLine = GetCommandLineArguments("GetPi", m_info.amountIteration, index + 1);

		SettingProcess(si);

		if (!CreateProcess(NULL//Имя приложения
			, (LPSTR)commandLine.data()// Аргументы командной строки
			, NULL// Указатель на структуру SECURITY_ATTRIBUTES
			, NULL// Указатель на структуру SECURITY_ATTRIBUTES
			, TRUE// Флаг наследования текущего процесса
			, CREATE_NEW_CONSOLE// Флаги способов создания процесса
			, NULL// Указатель на блок среды
			, NULL// Текущий диск или каталог
			, &si// Указатель нас структуру STARTUPINFO
			, &pi)// Указатель нас структуру PROCESS_INFORMATION
			)
		{
			std::cout << "Could't create a process. Program will continue to work without it" << std::endl;
			continue;
		}

		m_info.startUpInfos.push_back(si);
		m_info.processInformations.push_back(pi);
		m_info.handles.push_back(pi.hThread);
	}

	WaitMessages();
	CloseProcesses();
}

void CProcessRunner::WaitMessages()
{
	std::vector<std::string> messages;
	CPostman::WaitPackage(messages, m_info.processesNumber);

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

void CProcessRunner::SettingProcess(STARTUPINFO &si)
{
	si.dwFlags = STARTF_USESIZE | STARTF_USESHOWWINDOW;
	si.dwXSize = 500;
	si.dwYSize = 300;
	si.wShowWindow = SW_SHOW;
}

void CProcessRunner::CloseProcesses()
{
	for (size_t index = 0; index != m_info.processesNumber; ++index)
	{
		CloseHandle(m_info.processInformations[index].hProcess);
		CloseHandle(m_info.processInformations[index].hThread);
	}
}