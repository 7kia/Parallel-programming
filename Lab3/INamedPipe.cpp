#include "stdafx.h"
#include "INamedPipe.h"

INamedPipe::INamedPipe(const std::string prefix
					, const std::string& name
					, bool server)
	: m_name(prefix)
	, m_server(server)
{
	m_name.append(name);
}

void INamedPipe::ConnectOrOpen()
{
	if (m_server)
	{
		Open();
	}
	else
	{
		Connect();
	}
}

void INamedPipe::ReadBytes(void* buf, size_t size)
{
	if (!m_server)
	{
		if (size < 1)
		{
			throw std::out_of_range("Size is 0 or less");
		}
		InternalReadBytes(buf, size);
	}
	else
	{
		throw std::runtime_error("This operation is not supported on server pipe");
	}
}

void INamedPipe::WriteBytes(const void* buf, size_t size)
{
	if (!m_server)
	{
		if (size < 1)
		{
			throw std::out_of_range("Size is 0 or less");
		}
		InternalWriteBytes(buf, size);
	}
	else
	{
		throw std::runtime_error("This operation is not supported on server pipe");
	}
}

void INamedPipe::Flush()
{
	InternalFlush();
}