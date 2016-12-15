#pragma once

#include <string>
#include <vector>
#include "NamedPipe.h"

static const std::string NAME_PIPE = "\\\\.\\Pipe\\mypipe";

class CPostman
{
public:
	static void SendPackage(std::string const &message);
	static void WaitPackage(std::vector<std::string> &messages, size_t amountMessages);
};