#pragma once
#include <stdexcept>
#include <string>

/*
 The code from https://habrahabr.ru/post/166155/
 Repository https://github.com/xpavlov/libNamedPipe

 An interface for using namedpipes in a crossplatform way
*/
class INamedPipe
{
public:
	INamedPipe(const std::string prefix
			, const std::string& name
			, bool server);

	~INamedPipe() {};

//////////////////////////////////////////////////////////////////////
// Methods
public:
	/*!
	* \brief
	* Creates server pipe or connects to an existing one
	*
	* \throws std::exception
	*/
	void ConnectOrOpen();
	/*!
	* \brief
	* Performs a read operation from pipe. Client only
	*
	* \param buf
	* A pointer to store read data
	*
	* \param size
	* The number of bytes to be read
	*
	* \param has_extra_bytes
	* a pointer to bool value. It will be set into true if pipe has extra unread bytes after performing read operation
	*
	* \returns
	* The number of read bytes
	*
	* \throws std::exception
	*/
	virtual void ReadBytes(void* buf, size_t size);
	/*!
	* \brief
	* Performs a write operation to pipe. Client only
	*
	* \param buf
	* A pointer to buffer with data to be written
	*
	* \param size
	* The size of buffer

	* \returns
	* The number of written bytes
	*
	* \throws std::exception
	*/
	virtual void WriteBytes(const void* buffer, size_t size);
	virtual void Flush();
	virtual void Close() = 0;
	/*!
	* \brief
	* Blocks current thread until new connection and returns new INamedPipe associatend with connected client
	*/
	virtual INamedPipe* WaitForConnection() = 0;// TODO : see need  it
	virtual INamedPipe* WaitForConnection(unsigned int timeout) = 0;
protected:
	/*!
	* \brief
	* A virtual function that connects to an existing pipe. client only
	*
	* \throws std::exception
	*/
	virtual void Connect() = 0;
	/*!
	* \brief
	* A virtual function that creates a new pipe. server only
	*
	* \throws std::exception
	*/
	virtual void Open() = 0;
	/*!
	* \brief
	* A default constructor for internal purposes;
	*/
	INamedPipe() {};// TODO : see must it be there(might bug in source example(not my error)
	virtual void  InternalReadBytes(void* buf, size_t size) = 0;
	virtual void InternalWriteBytes(const void* buf, size_t size) = 0;
	virtual void InternalFlush() = 0;

//////////////////////////////////////////////////////////////////////
// Data
protected:
	///the pipe name
	std::string m_name;
	///is this a server pipe?
	bool m_server;// TODO : see need it
};

