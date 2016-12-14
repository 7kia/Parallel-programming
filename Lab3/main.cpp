#include "stdafx.h"
#include "main.h"
#include "Postman.h"
#include "TaskExecutor.h"

using namespace std;

namespace
{
void CheckParametrs(int argc)
{
	if ((argc != AMOUNT_ARGUMENTS) && (argc != AMOUNT_ARGUMENTS_WITH_ADDITIONAL))
	{
		throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS
			+ to_string(AMOUNT_ARGUMENTS)
			+ " or "
			+ to_string(AMOUNT_ARGUMENTS_WITH_ADDITIONAL)
			+ "\n If use additional parametr");
	}
}

void PrintHelp()
{
	std::cout <<
		R"(Help
@param 1 - execute exe-file
@param 2 - number process
@param 3 - amount iteration
@param 4(addirional) - amount iteration
		)" << std::endl;
}

bool CheckAdditionalParametr(int argc, _TCHAR * argv[])
{
	if (argc == AMOUNT_ARGUMENTS_WITH_ADDITIONAL)
	{
		if (argv[3] == HELP_PARAMETER)
		{
			return true;
		}
	}
	return false;
}


	void WaitMessages(SDataProcesses &info)
	{
		std::vector<std::string> messages;
		CPostman::WaitPackage(messages, info.processesNumber);


		for (auto const &message : messages)
		{
			std::cout << message << std::endl;
		}

	}



	std::string GetCommandLineArguments(std::string exeName, size_t amountIteration, size_t processesNumber)
	{
		std::string name = exeName + ".exe "
			+ std::to_string(amountIteration) + " "
			+ std::to_string(processesNumber);
		return name;
	}

	void SettingProcess(STARTUPINFO &si)
	{
		si.dwFlags = STARTF_USESIZE | STARTF_USESHOWWINDOW;
		si.dwXSize = 500;
		si.dwYSize = 300;
		si.wShowWindow = SW_SHOW;
	}

	void RunProcess(SDataProcesses &info)
	{
		for (size_t i = 0; i != info.processesNumber; ++i)
		{
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&si, sizeof(si));
			std::string commandLine = GetCommandLineArguments("GetPi", info.amountIteration, info.processesNumber);

			SettingProcess(si);

			if (!CreateProcess(NULL, (LPSTR)commandLine.data(), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
			{
				std::cout << "Could't create a process. Program will continue to work without it" << std::endl;
				continue;
			}


			info.startUpInfos.push_back(si);
			info.processInformations.push_back(pi);
			info.handles.push_back(pi.hThread);
		}



	}

	void CloseProcesses(SDataProcesses &info)
	{
		for (size_t i = 0; i != info.processesNumber; ++i)
		{
			CloseHandle(info.processInformations[i].hProcess);
			CloseHandle(info.processInformations[i].hThread);
		}
	}

}


int main(int argc, _TCHAR* argv[])
{
	try
	{

		setlocale(LC_ALL, "RUS");

		CheckParametrs(argc);

		if (CheckAdditionalParametr(argc, argv))
		{
			PrintHelp();
		}

		SDataProcesses info;
		info.processesNumber = atoi(argv[1]);
		info.amountIteration = atoi(argv[2]);
		RunProcess(info);

		WaitMessages(info);
		CloseProcesses(info);
	}
	catch (const std::exception & exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	system("pause");
	return 0;
}
