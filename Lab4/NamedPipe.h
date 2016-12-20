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
	void			ReadBytes(void* buffer, size_t size) override;
	void			WriteBytes(const void* buffer, size_t size) override;

	bool			Open(const std::string& name) override;
	void			Close() override;

};