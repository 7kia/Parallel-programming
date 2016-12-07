#pragma once

#include <string>
#include <algorithm>// For string tolower
#include <clocale>

#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <boost/algorithm/string.hpp>



static const std::string MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";
static const std::string MESSAGE_INCORRECT_RUNTIME_ARGUMENTS = "Incorrect runtime argument! See help, before run enter additional argument ?.";

static const std::string HELP_PARAMETER = "\\?";

// @param 1 - execute exe-file
// @param 2 - number process
// @param 3 - amount iteration
// @param 4(addirional) - amount iteration
static const int AMOUNT_ARGUMENTS = 3;
static const int AMOUNT_ARGUMENTS_WITH_ADDITIONAL = AMOUNT_ARGUMENTS + 1;

static const size_t AMOUNT_CPU = 3;


// Name for handels
static const LPTSTR MUTEX_NAME = "\\.\\pipe\\TaskExecutorPipe";