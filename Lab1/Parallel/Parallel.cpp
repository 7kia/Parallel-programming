// Parallel.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Parallel.h"
#include "../MatrixOperations.h"
#include <array>

#include <string>

#include <stdio.h>
#include <Windows.h>
#include <time.h>

// For timer
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <boost/algorithm/string.hpp>

static const int MATRIX_SIZE = 500;
static const int AMOUNT_THREAD = 4;
static const size_t SIZE_SECTION = INPUT_MATRIX.size() / AMOUNT_THREAD * size_t(2);
static const int ROUNDING_NUMBER = 5;

struct DataForProgram
{
	Matrix input;
	Matrix output;
};


DWORD WINAPI ComputeMinorsMatrix(void *data)
{
	//преобразуем полученные данные к типу структуры
	DataForProgram *r = (DataForProgram *)data;
	

	return 0;
}

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

												// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
						_In_opt_ HINSTANCE hPrevInstance,
						_In_ LPWSTR    lpCmdLine,
						_In_ int       nCmdShow) 
{
	//инициализируем генератор случайных чисел
	srand(time(NULL));
	//определяем дескрипторы потоков,
	//идентификаторы потоков и структуры для строк матрицы
	HANDLE thread[MATRIX_SIZE];
	DWORD thrId[MATRIX_SIZE];

	DataForProgram sourcesData;
	sourcesData.input = INPUT_MATRIX;
	sourcesData.output.resize(INPUT_MATRIX.size(), MatrixRow(INPUT_MATRIX.size()));

	boost::timer::cpu_timer timer;

	//
	// Start
	// 
	timer.start();
	

	///*
	std::array<DataForProgram, AMOUNT_THREAD> dataForThread;
	for (int i = 0; i < AMOUNT_THREAD; i++)
	{
		//создаем потоки
		Vector2UL startMatrix = Vector2UL((i % INPUT_MATRIX.size()) * SIZE_SECTION, (i / INPUT_MATRIX.size()) * SIZE_SECTION);
		thread[i] = CreateThread(NULL, 0, &ComputeMinorsMatrix, &sourcesData, 0, &thrId[i]);
	}
	//ждем, пока все эти потоки завершатся
	WaitForMultipleObjects(MATRIX_SIZE, thread, TRUE, INFINITE);

	std::string input;

	//выводим результат работы программы на экран
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			//input += " " + std::to_string(rows[i].value[j]);
			//printf(" %d", rows[i].value[j]);
		}
		//printf(" | multipl = %d\n", rows[i].result);
		//input += " | multipl = " + std::to_string(rows[i].result) + "\n";
	}
	//*/

	/*
		// OLD main
	char * ch = "A\0";
	char * ch2 = "B\0";

	std::string input;

	HANDLE * handles = new HANDLE[2];
	handles[0] = CreateThread(NULL, 0, &ThreadProc, ch, CREATE_SUSPENDED, NULL);
	handles[1] = CreateThread(NULL, 0, &ThreadProc, ch2, CREATE_SUSPENDED, NULL);

	ResumeThread(handles[0]);
	ResumeThread(handles[1]);

	WaitForMultipleObjects(2, handles, true, INFINITE);

	*/




	timer.stop();
	//
	// End
	//

	std::string strTime;
	strTime = boost::timer::format(timer.elapsed(), ROUNDING_NUMBER, "%u");

	return 0;
}