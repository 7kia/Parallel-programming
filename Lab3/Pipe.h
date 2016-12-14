#pragma once

#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <assert.h>
#include <sstream>

static const size_t BUFFER_PIPE_SIZE = 256;

/*
The code from https://habrahabr.ru/post/166155/
Repository https://github.com/xpavlov/libNamedPipe

An interface for using namedpipes in a crossplatform way
*/

#define THROW_LAST_ERROR(e)									\
{															\
	int error = GetLastError();								\
	std::stringstream err;									\
	err << e << ", GLE=" << error;							\
	throw std::runtime_error(err.str().data());				\
}
// Last line to the /\ macros \\
//err.clear();											\/// /TODO : see need the line


class CPipe 
{
public:
	CPipe();// TODO : see need all constructors?
	~CPipe();

//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void			ReadBytes(void* buffer, size_t size);
	virtual void			WriteBytes(const void* buffer, size_t size);

	virtual void			Open(const std::string& name);
	virtual void			Close();// TODO : see need the method separately

//////////////////////////////////////////////////////////////////////
// Data
protected:
	std::string		m_name;
	std::string		m_nameExe;//TODO : check correcntness

	HANDLE			m_hPipe;
	size_t			m_bufSize;
};
