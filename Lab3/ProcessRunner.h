#pragma once

#include <Windows.h>

#include <string>
#include <vector>

#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <boost/algorithm/string.hpp>

#include "Postman.h"


class CProcessRunner
{
public:
	CProcessRunner();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	struct SDataProcesses
	{
		std::vector<STARTUPINFO> startUpInfos;
		std::vector<PROCESS_INFORMATION> processInformations;
		HANDLE hPipe;
		std::vector<HANDLE> handles;
		size_t processesNumber;
		size_t amountIteration;
	};

	void			Run(size_t processesNumber, size_t amountIteration);
	void			WaitMessages();
	void			SettingProcess(STARTUPINFO & si);
	void			CloseProcesses();

	static std::string		GetCommandLineArguments(std::string exeName
													, size_t amountIteration
													, size_t processesNumber);
//////////////////////////////////////////////////////////////////////
// Data
private:
	SDataProcesses  m_info;

};