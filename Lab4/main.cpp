#include "stdafx.h"
#include "main.h"
#include "ProcessRunner.h"

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
		for (size_t index = 1; index < argc; ++index)
		{		
			if (argv[index] == HELP_PARAMETER)
			{
				return true;
			}		
		}
		
		return false;
	}	

}


int main(int argc, _TCHAR* argv[])
{
	try
	{

		setlocale(LC_ALL, "RUS");


		if (CheckAdditionalParametr(argc, argv))
		{
			PrintHelp();

			if (argc == 2)
			{
				return 0;
			}
		}

		CheckParametrs(argc);

		CProcessRunner runner;
		runner.Run(atoi(argv[1]), atoi(argv[2]));
	}
	catch (const std::exception & exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}
