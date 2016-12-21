#pragma once

#include <string>
#include <vector>
#include "NamedPipe.h"

static const int READY_MESSAGE = 1;
static const int UNREADY_MESSAGE = 0;


static const std::string NAME_PIPE = "\\\\.\\Pipe\\mypipe";

class CPostman
{
public:
	static void SendPackage(std::string const &message, size_t numberProcess);
};