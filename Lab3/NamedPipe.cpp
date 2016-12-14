#include "stdafx.h"
#include "NamedPipe.h"

CNamedPipe::CNamedPipe()
	: CPipe()
{
}

CNamedPipe::~CNamedPipe()
{
	Close();
}


void CNamedPipe::Open(const std::string& name)
{
	m_name = name;

	m_hPipe = CreateNamedPipe(m_name.data(),// им€ создаваемого канала          
		PIPE_ACCESS_DUPLEX,       // разрешен доступ на чтение и запись 
		PIPE_TYPE_BYTE |   //читаем побайтово
		PIPE_WAIT,                // блокирующий режим 
		PIPE_UNLIMITED_INSTANCES, // число экземпл€ров канала неограниченно  
		BUFFER_PIPE_SIZE,                  // размер буфера исход€щих сообщений 
		BUFFER_PIPE_SIZE,                  // размер буфера вход€щих сообщений 
		0,                        // тайм-аут ожидани€ (0=бесконечно) 
		NULL);


	if (m_hPipe == INVALID_HANDLE_VALUE)
	{
		THROW_LAST_ERROR("Error for open pipe " + m_name);
	}
}


void CNamedPipe::ReadBytes(void * buffer, size_t size)
{

	if (ConnectNamedPipe(m_hPipe, NULL) != FALSE)
	{

		DWORD dwRead;
		BOOL bSuccess = ReadFile(m_hPipe, buffer, DWORD(size), &dwRead, NULL);

		if (!bSuccess || (dwRead == 0))
		{
			throw std::runtime_error("Read error");
		}


	}
	DisconnectNamedPipe(m_hPipe);

}

void CNamedPipe::WriteBytes(const void * buffer, size_t size)
{
	if (ConnectNamedPipe(m_hPipe, NULL) != FALSE)
	{

		DWORD dwWritten;
		BOOL bSuccess = WriteFile(m_hPipe, buffer, DWORD(size), &dwWritten, NULL);

		if (!bSuccess)
		{
			throw std::runtime_error("Read error");
		}

	}
	DisconnectNamedPipe(m_hPipe);

}

void CNamedPipe::Close()
{
	DisconnectNamedPipe(m_hPipe);
	CloseHandle(m_hPipe); //May throw an exception if a debugger is attached to the process!
	m_hPipe = nullptr;
}