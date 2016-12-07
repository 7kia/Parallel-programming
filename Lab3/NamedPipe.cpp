#include "stdafx.h"

#include "NamedPipe.h"
#include <sstream>

#define THROW_LAST_ERROR(e)									\
{															\
	int error = GetLastError();								\
	std::stringstream err;									\
	err << e << ", GLE=" << error;							\
	throw std::runtime_error(err.str().data());				\
}
// Last line to the /\ macros \\
//err.clear();											\/// /TODO : see need the line


NamedPipe::NamedPipe()
	: m_hPipe(NULL)
{
}

void NamedPipe::Open(const std::string& name) 
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


	if (m_hPipe == INVALID_HANDLE_VALUE)
	{
		THROW_LAST_ERROR("Error for open pipe " + m_name);
	}
}

NamedPipe::~NamedPipe(void)
{
	Close();
}

void NamedPipe::ReadBytes(void * buffer, size_t size)
{
	DWORD dwRead;
	BOOL bSuccess = ReadFile(m_hPipe, buffer, size, &dwRead, NULL);

	if (!bSuccess || dwRead == 0)//
	{
		throw std::runtime_error("Read error");
	}

}

void NamedPipe::WriteBytes(const void * buffer, size_t size)
{
	DWORD dwRead = sizeof(size_t);
	DWORD dwWritten;

	BOOL bSuccess = WriteFile(m_hPipe, buffer, size, &dwWritten, NULL);

	if (!bSuccess)
	{
		throw std::runtime_error("Read error");
	}
}

void NamedPipe::Close()
{
	DisconnectNamedPipe(m_hPipe);
	CloseHandle(m_hPipe); //May throw an exception if a debugger is attached to the process!
	m_hPipe = nullptr;
}