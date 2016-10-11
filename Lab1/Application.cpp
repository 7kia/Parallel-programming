#include "stdafx.h"
#include "Application.h"

#include <array>

#include <string>

#include <stdio.h>
#include <Windows.h>
#include <time.h>

// For timer
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

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

int GetAffinityMask(int threadIndex)
{
	int mask = 0x0000;
	if (AMOUNT_THREAD / AMOUNT_CPU == 0)
	{
		return 1;
	}

	int cpuIndex = (threadIndex) / (AMOUNT_THREAD / AMOUNT_CPU);
	if ((AMOUNT_THREAD % AMOUNT_CPU == 1) && (cpuIndex > 0))
	{
		cpuIndex--;
	}
	return int(pow(2.f, cpuIndex));
}

void RunProgram(int argc, char * argv[])
{
	CheckParametrs(argc);
	
	//Matrix INPUT_MATRIX;
	//MatrixOperations::FillMatrixFromFile(argv[1], INPUT_MATRIX);
	AMOUNT_THREAD = atoi(argv[1]);
	AMOUNT_CPU = atoi(argv[2]);

	size_t SIZE_SECTION = INPUT_MATRIX.size() / AMOUNT_THREAD * size_t(2);

	//инициализируем генератор случайных чисел
	srand(time(NULL));
	//определяем дескрипторы потоков,
	//идентификаторы потоков и структуры для строк матрицы
	std::vector<HANDLE> thread(AMOUNT_THREAD);
	std::vector<DWORD> thrId(AMOUNT_THREAD);

	//HANDLE thread[AMOUNT_THREAD];
	//DWORD thrId[AMOUNT_THREAD];

	DataForProgram sourcesData;
	sourcesData.input = &INPUT_MATRIX;
	sourcesData.output.resize(INPUT_MATRIX.size(), MatrixRow(INPUT_MATRIX.size()));

	boost::timer::cpu_timer timer;


	// TODO : delete
	std::vector<int> masks;
	for (size_t i = 0; i < AMOUNT_THREAD; i++)
	{
		masks.push_back(GetAffinityMask(i));
	}
	///*
	std::vector<DataForProgram> dataForThread(AMOUNT_THREAD);
	for (size_t i = 0; i < AMOUNT_THREAD; i++)
	{
		//создаем потоки
		Vector2UL startMatrix = Vector2UL((i * SIZE_SECTION) % INPUT_MATRIX.size()
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

		thread[i] = CreateThread(NULL, 0, &ComputeMinorsMatrix, &dataForThread[i], CREATE_SUSPENDED, NULL);
		SetThreadAffinityMask(thread[i], GetAffinityMask(i));

	}
	//
	// Start
	// 
	timer.start();

	for (size_t i = 0; i < AMOUNT_THREAD; i++)
	{
		ResumeThread(thread[i]);
	}

	// ждем, пока все эти потоки завершатся
	WaitForMultipleObjects(AMOUNT_THREAD, thread.data(), TRUE, INFINITE);

	timer.stop();
	//
	// End
	//

	std::string strTime;

	double time = timer.elapsed().user * pow(10.f, -9.f) / AMOUNT_THREAD;
	strTime = boost::timer::format(timer.elapsed(), ROUNDING_NUMBER, "%u");

}

void CompputeAdditionalMatrixAndPrint(const Matrix & matrix, std::ostream & strm)
{
	Matrix additionalMatrix;
	Vector2UL start(0, 0);
	Vector2UL end(matrix.size(), matrix.size());
	additionalMatrix.resize(end.y - start.y, MatrixRow(end.x - start.x));

	additionalMatrix = MatrixOperations::GetAdditionalMatrix(matrix, additionalMatrix);

	MatrixOperations::PrintMatrix(additionalMatrix, strm);
}

void CheckParametrs(int argc)
{
	if (argc != AMOUNT_ARGUMENTS)
	{
		throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS + to_string(AMOUNT_ARGUMENTS));
	}
}

void MatrixOperations::FillMatrixFromFile(string nameFile, Matrix &matrix)
{
	ifstream inputFile;
	inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	inputFile.open(nameFile);
	if (!inputFile.is_open())
	{
		throw MESSAGE_FAILED_OPEN + nameFile + MESSAGE_FAILED_OPEN_FOR_READING;
	}

	size_t width;
	size_t height;
	inputFile >> width;
	inputFile >> height;

	if ((width != height) || (width == 0) || (height == 0))
	{
		throw std::runtime_error("Matrix must have size more zero and be square");
	}

	MatrixRow row;
	for (size_t y = 0; y < width; y++)
	{
		for (size_t x = 0; x < height; x++)
		{
			double addNumber = 0;
			inputFile >> addNumber;
			row.push_back(addNumber);
		}
		matrix.push_back(row);
		row.clear();
	}

	/*
		if (!inputFile.eof())
	{
		string passString;
		inputFile >> passString;
		if (!passString.empty())
		{
			throw MESSAGE_INCORRECT_DATA;
		}
	}
	*/

	


}