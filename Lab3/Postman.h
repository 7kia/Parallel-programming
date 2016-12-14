#pragma once

#include <string>
#include <vector>
#include "Pipe.h"

class CPostman
{
public:
	static void SendPackage(std::string const &message, size_t indexProcess);
	static void WaitPackage(std::vector<std::string> &messages, size_t amountMessages);
};