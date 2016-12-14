#include "stdafx.h"
#include "Postman.h"

void CPostman::SendPackage(std::string const & message)
{
	std::string namePipe = "\\\\.\\pipe\\myPipe";

	CPipe pipe;
	pipe.Open(namePipe);

	pipe.WriteBytes(message.data(), message.size());
	pipe.Close();
}

void CPostman::WaitPackage(std::vector<std::string> &messages, size_t amountMessages)
{
	std::string namePipe = "\\\\.\\Pipe\\mypipe";
	CNamedPipe pipe;
	pipe.Open(namePipe);


	for (size_t index = 0; index < amountMessages; ++index)
	{
		char buffer[BUFFER_PIPE_SIZE] = "";
		pipe.ReadBytes(buffer, BUFFER_PIPE_SIZE);
		messages.push_back(buffer);
	}
}
