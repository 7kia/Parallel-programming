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
class CPipe 
{
public:
	CPipe();// TODO : see need all constructors?
	~CPipe();

//////////////////////////////////////////////////////////////////////
// Methods
public:
	void			ReadBytes(void* buffer, size_t size);
	void			WriteBytes(const void* buffer, size_t size);

	void			Open(const std::string& name);
	void			Close();// TODO : see need the method separately

//////////////////////////////////////////////////////////////////////
// Data
private:
	std::string		m_name;
	std::string		m_nameExe;//TODO : check correcntness

	HANDLE			m_hPipe;
	size_t			m_bufSize;
};
