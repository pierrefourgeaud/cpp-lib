#ifndef CPPLIB_INCLUDE_LOGGER_BUFFERLOGGER_HPP
# define CPPLIB_INCLUDE_LOGGER_BUFFERLOGGER_HPP

#include "iloglistener.hpp"
#include <string>
#include <sstream>

namespace CppLib
{

class BufferLogger : public ILogListener
{
public:
	////////////////////////////////////////////////////////////////////////////////
	//
	BufferLogger() {}

	////////////////////////////////////////////////////////////////////////////////
	//
	virtual ~BufferLogger() {}

	////////////////////////////////////////////////////////////////////////////////
	//
	std::string GetBuffer( bool iClearBuffer = true )
	{
		std::string buffer = m_Buffer.str();

		if ( iClearBuffer )
		{
			ClearBuffer();
		}

		return buffer;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	void ClearBuffer()
	{
		m_Buffer.str("");
		m_Buffer.clear();
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	virtual void Notify( const std::string& iMsg, ELogLevel iLevel )
	{
		m_Buffer << iMsg;
	}

private:
	std::ostringstream m_Buffer;
};

}

#endif // !CPPLIB_INCLUDE_LOGGER_BUFFERLOGGER_HPP
