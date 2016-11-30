#pragma once

#include "INamedpipe.h"
#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>

static const size_t BUFFER_PIPE_SIZE = 5120;

/*
The code from https://habrahabr.ru/post/166155/
Repository https://github.com/xpavlov/libNamedPipe

An interface for using namedpipes in a crossplatform way
*/

// TODO : rename
class WinNamedPipe :
	public INamedPipe
{
public:
	WinNamedPipe(HANDLE pipe);
	WinNamedPipe(const std::string& name, bool server);
	~WinNamedPipe();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void			Close();
	WinNamedPipe*	WaitForConnection();
	WinNamedPipe*	WaitForConnection(unsigned int timeout);

protected:
	void Connect();
	void Open();
	void InternalReadBytes(void* buf, size_t size);
	void InternalWriteBytes(const void* buf, size_t size);
	void InternalFlush();
//////////////////////////////////////////////////////////////////////
// Data
private:
	HANDLE	m_hPipe;
	size_t	m_bufSize;
	bool	m_server_with_client;

};
