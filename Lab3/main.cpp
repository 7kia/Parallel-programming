#include "stdafx.h"
#include "main.h"

using namespace std;

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
	if ((argc == AMOUNT_ARGUMENTS_WITH_ADDITIONAL))
	{
		if (argv[3] == HELP_PARAMETER)
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}


int main(int argc, _TCHAR* argv[])
{
	CheckParametrs(argc);

	if (CheckAdditionalParametr(argc, argv))
	{
		PrintHelp();
	}

	return 0;
}
