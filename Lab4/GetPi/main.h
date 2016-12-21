#pragma once

#include <string>
#include <algorithm>// For string tolower
#include <clocale>

#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <boost/algorithm/string.hpp>

#include "ClientApplication.h"

static const std::string MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";

static const int AMOUNT_ARGUMENTS = 3;
