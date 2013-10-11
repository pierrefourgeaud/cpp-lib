#ifndef CPPLIB_INCLUDE_LOGGER_ILOGLISTENER_HPP
# define CPPLIB_INCLUDE_LOGGER_ILOGLISTENER_HPP

#include <string>

namespace CppLib
{

enum ELogLevel {
	logCRITICAL,
	logERROR,
	logWARNING,
	logINFO,
	logDEBUG,
	logDEBUG1,
	logDEBUG2
};

class ILogListener
{
public:
	virtual ~ILogListener() {};
	virtual void Notify( const std::string& iLog, ELogLevel iLevel ) = 0;
};

} // namespace CppLib

#endif // !CPPLIB_INCLUDE_LOGGER_ILOGLISTENER_HPP