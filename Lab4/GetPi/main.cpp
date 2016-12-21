// GetPi.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "main.h"

using namespace std;

void CheckParametrs(int argc)
{
	if (argc != AMOUNT_ARGUMENTS)
	{
		throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS
			+ to_string(AMOUNT_ARGUMENTS));
	}
}


int main(int argc, char *argv[])
{
	try
	{
		setlocale(LC_ALL, "RUS");

		CheckParametrs(argc);

		boost::timer::cpu_timer timer;

		size_t amountIteration = atoi(argv[1]);
		size_t processsNumber = atoi(argv[2]);

		CClientApplication taskExecutor(processsNumber);

		taskExecutor.WaitCommand();

		timer.start();
		cout << taskExecutor.GetPi(amountIteration) << std::endl;
		timer.stop();

		// TODO : see need comment low
		double time = timer.elapsed().wall * pow(10.f, -9.f);// / amountThread;
		std::cout << "time = " << time << std::endl;
		system("pause");
		//taskExecutor.m_outputChannel.Close();
	}
	catch (const std::exception & exception)
	{
		std::cout << exception.what() << std::endl;
		system("pause");
		return 1;
	}

	return 0;
}

