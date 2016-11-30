#include "stdafx.h"
#include "main.h"
#include "TaskExecutor.h"

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
	try
	{
		setlocale(LC_ALL, "RUS");

		CheckParametrs(argc);

		if (CheckAdditionalParametr(argc, argv))
		{
			PrintHelp();
		}

		size_t amountProcess = size_t(atoi(argv[1]));
		size_t amountIteration = size_t(atoi(argv[2]));

		boost::timer::cpu_timer timer;

		// TODO : delete the this and low comment
		// the mutex will use in future
		HANDLE mutex = CreateMutex(NULL, false, MUTEX_NAME);
		CTaskExecutor taskExecutor(mutex);

		timer.start();

		cout << taskExecutor.GetPi(amountProcess, amountIteration) << std::endl;

		timer.stop();

		// TODO : see need comment low
		double time = timer.elapsed().user * pow(10.f, -9.f);// / amountThread;
		std::cout << time << std::endl;
	}
	catch (const std::exception & exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}
