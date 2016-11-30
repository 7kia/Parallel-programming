#pragma once

#include <string>
#include <algorithm>// For string tolower


static const std::string MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";
static const std::string MESSAGE_INCORRECT_RUNTIME_ARGUMENTS = "Incorrect runtime argument! See help, before run enter additional argument ?.";

static const std::string COMPUTE_PARAMETER = "c";
static const std::string EXIT_PARAMETER = "e";
static const std::string YES_PARAMETER = "y";
static const std::string NO_PARAMETER = "n";
static const std::string HELP_PARAMETER = "\\?";

// @param 1 - execute exe-file
// @param 2 - number process
// @param 3 - amount iteration
// @param 4(addirional) - amount iteration
static const int AMOUNT_ARGUMENTS = 3;
static const int AMOUNT_ARGUMENTS_WITH_ADDITIONAL = AMOUNT_ARGUMENTS + 1;