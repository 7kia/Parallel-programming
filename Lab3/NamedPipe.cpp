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

NamedPipe::NamedPipe(const std::string& name) 
{
	Open(name);// TODO: see need replace
}

void NamedPipe::Open(const std::string& name) 
{
	m_name = name;

	///*
		m_hPipe = CreateFile(
		m_name.data(),
		GENERIC_ALL,//GENERIC_READ
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_READONLY,
		NULL);

	//*/

	/*
		m_hPipe = CreateNamedPipe(
		(LPSTR)m_name.data(),   // pipe name 
		PIPE_ACCESS_DUPLEX,       // разрешен доступ на чтение и запись 
		PIPE_TYPE_BYTE |   //читаем побайтово
		PIPE_WAIT,                // блокирующий режим 
		PIPE_UNLIMITED_INSTANCES, // число экземпл€ров канала неограниченно  
		BUFFER_PIPE_SIZE,                  // размер буфера исход€щих сообщений 
		BUFFER_PIPE_SIZE,                  // размер буфера вход€щих сообщений 
		0,                        // тайм-аут ожидани€ (0=бесконечно) 
		NULL);

	//*/
		/*CreateNamedPipe
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
	*/

	if (m_hPipe == INVALID_HANDLE_VALUE)
	{
		THROW_LAST_ERROR("Error for open pipe " + m_name);
	}
}

/*
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

*/

void NamedPipe::InternalFlush()
{
	FlushFileBuffers(m_hPipe);
}

/*void  NamedPipe::InternalWriteBytes(const void* buf, size_t size)
{
	DWORD cbWritten;
	BOOL fSuccess = FALSE;

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


*/

NamedPipe::~NamedPipe(void)
{
	Close();
}

void NamedPipe::ReadBytes(void * buffer, size_t size)
{
	/*
	BOOL fSuccess = FALSE;
	DWORD dwMode = PIPE_READMODE_MESSAGE;
	DWORD cbBytesRead = 0;
	size_t readValue = 0;

	fSuccess = ReadFile(
		m_hPipe,        // handle to pipe 
		&readValue,    // buffer to receive data 
		sizeof(size_t), // size of buffer 
		&cbBytesRead, // number of bytes read 
		NULL);        // not overlapped I/O 
	/*
		fSuccess = SetNamedPipeHandleState(
		m_hPipe,    // pipe handle 
		&dwMode,  // new pipe mode 
		NULL,     // don't set maximum bytes 
		NULL);    // don't set maximum time 

	

	if (!fSuccess)
	{
		THROW_LAST_ERROR("SetNamedPipeHandleState failed.");
	}
	*/
	/*
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
	//*/
	//CHAR chBuf[BUFFFER_SIZE];
	DWORD dwRead;
	BOOL bSuccess = ReadFile(m_hPipe, buffer, size, &dwRead, NULL);

	if (!bSuccess || dwRead == 0)//
	{
		throw std::runtime_error("Read error");
	}

}

void NamedPipe::WriteBytes(const void * buffer, size_t size)
{
	//InternalWriteBytes(buffer, size);

	/*
	LPDWORD
	cbToWrite = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR);
	_tprintf(TEXT("Sending %d byte message: \"%s\"\n"), cbToWrite, lpvMessage);

	fSuccess = WriteFile(
		hPipe,                  // pipe handle 
		lpvMessage,             // message 
		size,              // message length 
		&buffer,             // bytes written 
		NULL);                  // not overlapped 

	if (!fSuccess)
	{
		_tprintf(TEXT("WriteFile to pipe failed. GLE=%d\n"), GetLastError());
		return -1;
	}
	*/
	//CHAR chBuf[BUFFFER_SIZE];
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