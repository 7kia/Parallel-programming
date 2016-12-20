#pragma once

#include "Pipe.h"

class CNamedPipe : public CPipe
{
public:
	CNamedPipe();// TODO : see need all constructors?
	~CNamedPipe();

//////////////////////////////////////////////////////////////////////
// Methods
public:
	bool			ReadBytes(void* buffer, size_t size) override;
	bool			WriteBytes(const void* buffer, size_t size) override;

	bool			Open(const std::string& name) override;
	void			Close() override;

};