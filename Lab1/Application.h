#pragma once

#include <string>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <time.h> // for clock()

#include "MatrixOperations.h"

static const std::string MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";
static const std::string MESSAGE_FAILED_OPEN = "Failed to open ";
static const std::string MESSAGE_FAILED_OPEN_FOR_READING = " for reading!";
static const std::string MESSAGE_INCORRECT_DATA = "File consist excess data!";

static const int ERROR_CODE = -1;
static const int AMOUNT_ARGUMENTS = 2;
static const int SIZE_MATRIX = 3;

void RunProgram(int argc, char * argv[]);
void CheckParametrs(int argc);
