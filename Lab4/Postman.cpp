#include "stdafx.h"
#include "Postman.h"

void CPostman::SendPackage(std::string const & message, size_t numberProcess)
{
	std::string namePipe = NAME_PIPE;

	CPipe pipe;
	pipe.Open(namePipe + std::to_string(numberProcess));

	pipe.WriteBytes(message.data(), message.size());
	pipe.Close();
}

