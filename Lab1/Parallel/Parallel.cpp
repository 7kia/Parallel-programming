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
	Matrix *input = nullptr;
	Matrix output;

	Vector2UL startMatrix;
	Vector2UL endMatrix;
};


DWORD WINAPI ComputeMinorsMatrix(void *data)
{
	//преобразуем полученные данные к типу структуры
	DataForProgram *r = (DataForProgram *)data;
	
	r->output.resize(r->endMatrix.y - r->startMatrix.y + 1, MatrixRow(r->endMatrix.x - r->startMatrix.x + 1));
	MatrixOperations::GetAdditionalMatrix(*r->input, r->output, r->startMatrix, r->endMatrix);
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
	HANDLE thread[AMOUNT_THREAD];
	DWORD thrId[AMOUNT_THREAD];

	DataForProgram sourcesData;
	sourcesData.input = &INPUT_MATRIX;
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
		Vector2UL startMatrix = Vector2UL((i * SIZE_SECTION)  % INPUT_MATRIX.size()
										, (i * SIZE_SECTION) / INPUT_MATRIX.size() * SIZE_SECTION);

		Vector2UL endMatrix = startMatrix;
		endMatrix.x += SIZE_SECTION - 1;
		endMatrix.y += SIZE_SECTION - 1;

		dataForThread[i].startMatrix = startMatrix;
		dataForThread[i].endMatrix = endMatrix;

		// TODO : enable threads after write necesssary data
		//////////////////////////////////
		// Record from source matrix
		dataForThread[i].input = &INPUT_MATRIX;
		dataForThread[i].output.resize(SIZE_SECTION, MatrixRow(SIZE_SECTION));

		
		//dataForThread[i].input = 
		//////////////////////////////////
		// TODO : rewrite value
		SetThreadAffinityMask(thread[i], i);
		SetThreadPriority(thread[i], THREAD_PRIORITY_ABOVE_NORMAL);

		thread[i] = CreateThread(NULL, 0, &ComputeMinorsMatrix, &dataForThread[i], CREATE_SUSPENDED, NULL);
		ResumeThread(thread[i]);
	}

	
	//ждем, пока все эти потоки завершатся
	WaitForMultipleObjects(AMOUNT_THREAD, thread, TRUE, INFINITE);

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

	strTime = boost::timer::format(timer.elapsed() / float(AMOUNT_THREAD), ROUNDING_NUMBER, "%u");

	return 0;
}