#pragma once

#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <assert.h>

static const size_t BUFFER_PIPE_SIZE = 5120;

/*
The code from https://habrahabr.ru/post/166155/
Repository https://github.com/xpavlov/libNamedPipe

An interface for using namedpipes in a crossplatform way
*/

// TODO : rename
class NamedPipe 
{
public:
	NamedPipe();// TODO : see need all constructors?
	NamedPipe(HANDLE pipe);
	NamedPipe(const std::string& name);
	~NamedPipe();

	static const size_t BUFFFER_SIZE = 4096;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void			ReadBytes(void* buffer, size_t size);
	void			WriteBytes(const void* buffer, size_t size);

	void			Open(const std::string& name);
	void			Close();// TODO : see need the method separately

protected:
	//void			InternalReadBytes(void* buf, size_t size);
	//void			InternalWriteBytes(const void* buf, size_t size);
	void			InternalFlush();// TODO : see need
//////////////////////////////////////////////////////////////////////
// Data
private:
	std::string		m_name;
	std::string		m_nameExe;//TODO : check correcntness

	HANDLE			m_hPipe;
	size_t			m_bufSize;
};
