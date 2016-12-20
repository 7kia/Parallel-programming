#pragma once

#include <Windows.h>

#include <string>
#include <vector>

#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <boost/algorithm/string.hpp>

#include "Postman.h"

static const std::string RUN_MESSAGE = "r";

class CProcessRunner
{
public:
	CProcessRunner();
//////////////////////////////////////////////////////////////////////
// Methods
public:

	void			Run(size_t processesNumber, size_t amountIteration);

	void			WaitClients();
	void			WaitAndRunClients();
	void			WaitMessages();

	void			WaitPackage(std::vector<std::string> &messages);


	static std::string		GetCommandLineArguments(std::string exeName
													, size_t amountIteration
													, size_t processesNumber);
//////////////////////////////////////////////////////////////////////
// Data
private:
	std::vector<CPipe>		m_pipes;
};