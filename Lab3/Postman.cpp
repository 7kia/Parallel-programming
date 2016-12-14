#include "stdafx.h"
#include "Postman.h"

void CPostman::SendPackage(std::string const & message, size_t indexProcess)
{
	/*
	std::string namePipe = "\\\\.\\Pipe\\" + std::to_string(indexProcess);

	CPipe pipe;
	pipe.Open(namePipe);

	pipe.WriteBytes(message.data(), message.size());
	pipe.Close();
	*/
	HANDLE hPipe;

	do
	{
		hPipe = CreateFile("\\\\.\\pipe\\myPipe",
			GENERIC_ALL,//GENERIC_READ
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_READONLY,
			NULL);
	} while (hPipe == INVALID_HANDLE_VALUE);

	DWORD dwWritten = static_cast<DWORD>(message.size());
	if (hPipe != INVALID_HANDLE_VALUE)
	{
		while (WriteFile(hPipe,
			message.data(),
			static_cast<DWORD>(message.size()),   // = length of string + terminating '\0' !!!
			&dwWritten,
			NULL) == FALSE)
		{
		}

		CloseHandle(hPipe);
	}
}

void CPostman::WaitPackage(std::vector<std::string> &messages, size_t amountMessages)
{
	///*
		HANDLE hPipe = CreateNamedPipe("\\\\.\\pipe\\myPipe",
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		1024, 1024, 5000, NULL);

	if (hPipe == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed" << std::endl;
		return;
	}

	//*/

	/*
		std::string namePipe = "\\\\.\\Pipe\\pipe";

	CPipe pipe;
	pipe.Open(namePipe);

	*/

	
	for (size_t index = 0; index < amountMessages; ++index)
	{
		//pipe.ReadBytes(&messages[index], messages[index].size());
		///*
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)
		{
			char buffer[1024];
			DWORD dwRead;
			if (ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL) == TRUE)
			{
				buffer[dwRead] = '\0';
			}
			messages.push_back(buffer);
		}
		DisconnectNamedPipe(hPipe);
		//*/
	}
	CloseHandle(hPipe);
	//pipe.Close();

}
