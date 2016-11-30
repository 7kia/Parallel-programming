#include "stdafx.h"

#include "WinNamedPipe.h"
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


WinNamedPipe::WinNamedPipe(HANDLE pipe)
	: m_hPipe(pipe)
	, m_server_with_client(true)
{
	m_server = false;
}

WinNamedPipe::WinNamedPipe(const std::string& name, bool server) 
	: m_hPipe(NULL)
	, m_server_with_client(false)
	, INamedPipe("\\\\.\\pipe\\", name, server)
{
}

void WinNamedPipe::Open()
{
	m_hPipe = CreateNamedPipe
	(
			(LPSTR)m_name.data()						// pipe name
		,	PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED	// read/write access
		,	PIPE_TYPE_BYTE | PIPE_WAIT				// blocking mode
		,	PIPE_UNLIMITED_INSTANCES					// max. instances
		,	BUFFER_PIPE_SIZE							// output buffer size
		,	BUFFER_PIPE_SIZE							// input buffer size 
		,	0											// client time-out 
		,	NULL										// default security attribute 
	);                    

	if (m_hPipe == INVALID_HANDLE_VALUE)
	{
		THROW_LAST_ERROR("CreateNamedPipe failed");
	}
}

void WinNamedPipe::Connect()
{
	for (;;)
	{
		WaitNamedPipe((LPSTR)m_name.data(), NMPWAIT_WAIT_FOREVER);
		m_hPipe = CreateFile
		(
				(LPSTR)m_name.data()	// pipe name 
			,	GENERIC_READ | GENERIC_WRITE // read and write access 
			,	0						// no sharing 
			,	NULL					// default security attributes
			,	OPEN_EXISTING			// opens existing pipe
			,	0						// default attributes 
			,	NULL					// no template file 
		);      


		// Break if the pipe handle is valid or error != 232
		if ((m_hPipe != INVALID_HANDLE_VALUE) || (GetLastError() != ERROR_PIPE_BUSY))
		{
			break;
		}
	}
	if (m_hPipe == INVALID_HANDLE_VALUE)
	{
		THROW_LAST_ERROR("Could not open pipe");
	}
	// The pipe connected; change to message-read mode. 

	DWORD dwMode = PIPE_TYPE_BYTE;
	BOOL fSuccess = SetNamedPipeHandleState
	(
			m_hPipe	// pipe handle 
		,	&dwMode	// new pipe mode
		,	NULL	// don't set maximum bytes 
		,	NULL	// don't set maximum time			 
	);    

	if (!fSuccess)
	{
		THROW_LAST_ERROR("SetNamedPipeHandleState failed");
	}
}

WinNamedPipe* WinNamedPipe::WaitForConnection()
{
	if (m_server)
	{
		if (ConnectNamedPipe(m_hPipe, NULL) || (GetLastError() == ERROR_PIPE_CONNECTED))
		{
			HANDLE client = m_hPipe;
			Open();
			return new WinNamedPipe(client);
		}
		else
		{
			THROW_LAST_ERROR("WaitForConnection failed");
		}
	}
	else
	{
		throw std::runtime_error("WaitForConnection is not supported on server pipe\n");
	}
}

void WinNamedPipe::Close()
{
	if (m_server || m_server_with_client)
	{
		DisconnectNamedPipe(m_hPipe);
		CloseHandle(m_hPipe); //May throw an exception if a debugger is attached to the process!
		m_hPipe = NULL;
	}
}

void  WinNamedPipe::InternalReadBytes(void* buf, size_t size)
{
	DWORD cbBytesRead = 0;
	BOOL fSuccess = false;
	// Read from the pipe. 
	fSuccess = ReadFile
	(
			m_hPipe// handle to pipe 
		,	buf // buffer to receive data 
		,	DWORD(size)// size of buffer 
		,	&cbBytesRead// number of bytes read 
		,	NULL // not overlapped I/O 
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

void WinNamedPipe::InternalFlush()
{
	FlushFileBuffers(m_hPipe);
}

void  WinNamedPipe::InternalWriteBytes(const void* buf, size_t size)
{
	DWORD cbWritten;
	BOOL fSuccess = false;

	fSuccess = WriteFile
	(
			m_hPipe			// handle to pipe 
		,	buf				// buffer to write from 
		,	DWORD(size)			// number of bytes to write
		,	&cbWritten		// number of bytes written 
		,	NULL			// not overlapped I/O
	);         

	if (!fSuccess || (size != cbWritten))
	{
		THROW_LAST_ERROR("WriteFile failed");
	}
}

WinNamedPipe::~WinNamedPipe(void)
{
	Close();
}

WinNamedPipe*  WinNamedPipe::WaitForConnection(unsigned int timeout)
{
	if (m_server)
	{
		OVERLAPPED lpOverlapped = { 0 };
		lpOverlapped.hEvent = CreateEvent(0, 1, 1, 0);
		if (ConnectNamedPipe(m_hPipe, &lpOverlapped) == 0)
		{
			if (GetLastError() == ERROR_PIPE_CONNECTED)
			{
				if (!SetEvent(lpOverlapped.hEvent))
				{
					THROW_LAST_ERROR("AsyncWaitForConnection failed");
				}
			}
			int result = WaitForSingleObject(lpOverlapped.hEvent, timeout);
			if (WAIT_OBJECT_0 == result)
			{
				HANDLE client = m_hPipe;
				Open();
				return new WinNamedPipe(client);
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			THROW_LAST_ERROR("AsyncWaitForConnection failed");
		}
	}
	else
	{
		throw std::runtime_error("WaitForConnection is not supported on client pipe\n");
	}
}