#include "stdafx.h"

#include "Pipe.h"

CPipe::CPipe()
	: m_hPipe(NULL)
{
}

bool CPipe::Open(const std::string& name)
{
	m_name = name;

	m_hPipe = CreateFile(
				m_name.data(),
				GENERIC_ALL,//GENERIC_READ
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_READONLY,
				NULL);
	///*
		// If not open then wait client
	if (m_hPipe == INVALID_HANDLE_VALUE)
	{
		//THROW_LAST_ERROR("Error for open pipe " + m_name);

		if (!WaitNamedPipe(m_name.data(), NMPWAIT_WAIT_FOREVER))// TODO : see might need set concrete time
		{
			//THROW_LAST_ERROR("Error for open pipe " + m_name);
			return false;
		}
		THROW_LAST_ERROR("Error for open pipe " + m_name);
		return false;
	}
	//*/
	/*
	if (m_hPipe != INVALID_HANDLE_VALUE)
		return;

	// Exit if an error other than ERROR_PIPE_BUSY occurs. 

	if (GetLastError() != ERROR_PIPE_BUSY)
	{
		THROW_LAST_ERROR(TEXT("Could not open pipe. GLE=%d\n"), GetLastError());
	}

	// All pipe instances are busy, so wait for 20 seconds. 

	if (!WaitNamedPipe(m_name.data(), 20000))
	{
		THROW_LAST_ERROR("Could not open pipe: 20 second wait timed out.");
	}
	*/
	
	return true;
}

CPipe::~CPipe(void)
{
	Close();
}

bool CPipe::ReadBytes(void * buffer, size_t size)
{
	DWORD dwRead;
	BOOL bSuccess = ReadFile(m_hPipe, buffer, DWORD(size), &dwRead, NULL);

	if (!bSuccess || (dwRead == 0))
	{
		throw std::runtime_error("Read error");
		return false;
	}

	return true;
}

bool CPipe::WriteBytes(const void * buffer, size_t size)
{
	DWORD dwWritten;
	BOOL bSuccess = WriteFile(m_hPipe, buffer, DWORD(size), &dwWritten, NULL);

	if (!bSuccess || (dwWritten == 0))
	{
		throw std::runtime_error("Read error");
		return false;
	}

	return true;
}

void CPipe::Close()
{
	CloseHandle(m_hPipe); //May throw an exception if a debugger is attached to the process!
	m_hPipe = nullptr;
}