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

NamedPipe::NamedPipe(HANDLE pipe)
	: m_hPipe(pipe)
{
}

NamedPipe::NamedPipe(const std::string& prefix, const std::string& name)
{
	Open(prefix, name);// TODO: see need replace
}

void NamedPipe::Open(const std::string& prefix, const std::string& name)
{
	m_name = prefix;
	m_name.append(name);

	m_hPipe = CreateNamedPipe
	(
		(LPSTR)m_name.data()						// pipe name
		, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED	// read/write access
		, PIPE_TYPE_BYTE | PIPE_WAIT				// blocking mode
		, PIPE_UNLIMITED_INSTANCES					// max. instances
		, BUFFER_PIPE_SIZE							// output buffer size
		, BUFFER_PIPE_SIZE							// input buffer size 
		, 0											// client time-out 
		, NULL										// default security attribute 
	);

	if (m_hPipe == INVALID_HANDLE_VALUE)
	{
		THROW_LAST_ERROR("CreateNamedPipe failed");
	}
}


void  NamedPipe::InternalReadBytes(void* buf, size_t size)
{
	DWORD cbBytesRead = 0;
	BOOL fSuccess = false;
	// Read from the pipe. 
	fSuccess = ReadFile
	(
		m_hPipe// handle to pipe 
		, buf // buffer to receive data 
		, DWORD(size)// size of buffer 
		, &cbBytesRead// number of bytes read 
		, NULL // not overlapped I/O 
	);

	if (!fSuccess || (cbBytesRead == 0) || (cbBytesRead != size))// TODO : check correctness , was without ()
	{
		if (GetLastError() == ERROR_BROKEN_PIPE)
		{
			THROW_LAST_ERROR("pipe disconnected");
		}
		else
		{
			THROW_LAST_ERROR("read failed");
		}
	}

}

void NamedPipe::InternalFlush()
{
	FlushFileBuffers(m_hPipe);
}

void  NamedPipe::InternalWriteBytes(const void* buf, size_t size)
{
	DWORD cbWritten;
	BOOL fSuccess = false;

	fSuccess = WriteFile
	(
		m_hPipe			// handle to pipe 
		, buf			// buffer to write from 
		, DWORD(size)	// number of bytes to write
		, &cbWritten	// number of bytes written 
		, NULL			// not overlapped I/O
	);

	if (!fSuccess || (size != cbWritten))
	{
		THROW_LAST_ERROR("WriteFile failed");
	}
}

NamedPipe::~NamedPipe(void)
{
	Close();
}

void NamedPipe::ReadBytes(void * buffer, size_t size)
{
	DWORD cbBytesRead = 0;
	BOOL fSuccess = false;
	// Read from the pipe. 
	fSuccess = ReadFile
	(
			m_hPipe			// handle to pipe
		,	buffer			// buffer to receive data
		,	size			// size of buffer
		,	&cbBytesRead	// number of bytes read
		,	NULL			// not overlapped I/O
	);        

	if (!fSuccess || (cbBytesRead == 0) || (cbBytesRead != size))
	{
		if (GetLastError() == ERROR_BROKEN_PIPE)
		{
			THROW_LAST_ERROR("pipe disconnected");
		}
		else
		{
			THROW_LAST_ERROR("read failed");
		}
	}

}

void NamedPipe::WriteBytes(const void * buffer, size_t size)
{
	DWORD cbWritten;// TODO : check correctness
	BOOL fSuccess = false;

	fSuccess = WriteFile
	(
			m_hPipe		// handle to pipe
		,	buffer		// buffer to write from
		,	size		// number of bytes to write
		,	&cbWritten	// number of bytes written
		,	NULL		// not overlapped I/O 
	);        

	if (!fSuccess || (size != cbWritten))
	{
		THROW_LAST_ERROR("WriteFile failed");
	}
}

void NamedPipe::Close()
{
	DisconnectNamedPipe(m_hPipe);
	CloseHandle(m_hPipe); //May throw an exception if a debugger is attached to the process!
	m_hPipe = nullptr;
}