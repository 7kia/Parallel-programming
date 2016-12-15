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

void CPostman::WaitPackage(std::vector<std::string> &messages, size_t amountMessages)
{
	std::string namePipe = NAME_PIPE;
	for (size_t index = 0; index < amountMessages; ++index)
	{

		CPipe pipe;
	pipe.Open(namePipe + std::to_string(index));


		char buffer[BUFFER_PIPE_SIZE] = "";
		pipe.ReadBytes(buffer, BUFFER_PIPE_SIZE);
		messages.push_back(buffer);

		pipe.Close();

	}
}
