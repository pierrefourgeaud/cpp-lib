#ifndef CPPLIB_INCLUDE_LOGGER_H
# define CPPLIB_INCLUDE_LOGGER_H

#include "FileLogger.h"

// Logging code based on Petru Marginean's design
// http://www.drdobbs.com/cpp/201804215?pgno=1

#include <sstream>
#include <vector>
#include <algorithm>

#define LOG(level)                              \
	if ( level > Logger::ReportingLevel() ) ;   \
	else Logger().Get(level)

#define LOGC  LOG(logCRITICAL)
#define LOGE  LOG(logERROR)
#define LOGW  LOG(logWARNING)
#define LOGI  LOG(logINFO)
#define LOGD  LOG(logDEBUG)
#define LOGD1 LOG(logDEBUG1)
#define LOGD2 LOG(logDEBUG2)

namespace CppLib
{

class Logger
{
public:
	Logger();
	virtual ~Logger();

	std::ostringstream& Get( ELogLevel iLevel = logINFO );

	static bool AddListener( ILogListener* iListener );
	static bool RemoveListener( ILogListener* iListener );

	static inline std::vector<ILogListener*>& Listeners();
	static inline ELogLevel& ReportingLevel();
	static inline std::string ToString( ELogLevel iLevel );
	static ELogLevel FromString( const std::string& iLevel );
protected:
	std::ostringstream m_Os;

private:
	// Prevent against copy
	Logger( const Logger& );
	Logger& operator=( const Logger& );

	bool NotifyListeners();

	ELogLevel m_Level;
	static std::vector<ILogListener*> m_Listeners;
};

////////////////////////////////////////////////////////////////////////////////
//
inline std::vector<ILogListener*>& Logger::Listeners()
{
	static std::vector<ILogListener*> listeners;
	return listeners;
}

////////////////////////////////////////////////////////////////////////////////
//
inline ELogLevel& Logger::ReportingLevel()
{
	static ELogLevel reportingLevel = logDEBUG2;
	return reportingLevel;
}

////////////////////////////////////////////////////////////////////////////////
//
inline std::string Logger::ToString( ELogLevel iLevel )
{
	static const char* const buffer[] = {"CRITICAL", "ERROR", "WARNING", "INFO", "DEBUG", "DEBUG1", "DEBUG2"};
	return buffer[iLevel];
}

inline std::string NowTime();

////////////////////////////////////////////////////////////////////////////////
//
// FOWARD DECLARATION
class Notifier
{
public:
	Notifier( std::string& iLog, ELogLevel iLevel ) :
		m_Log(iLog),
		m_Level(iLevel)
	{}

	void operator()( ILogListener* iListener )
	{
		iListener->Notify( m_Log, m_Level );
	}
	
private:
	std::string m_Log;
	ELogLevel m_Level;
};

////////////////////////////////////////////////////////////////////////////////
//
Logger::Logger()
{
}

////////////////////////////////////////////////////////////////////////////////
//
Logger::~Logger()
{
	this->NotifyListeners();
}

////////////////////////////////////////////////////////////////////////////////
//
std::ostringstream& Logger::Get( ELogLevel iLevel )
{
	this->m_Os << NowTime();
	this->m_Os << " " << Logger::ToString( iLevel ) << ": ";
	this->m_Os << std::string( iLevel > logDEBUG ? iLevel - logDEBUG : 0, '\t' );
	this->m_Level = iLevel;
	return this->m_Os;
}

////////////////////////////////////////////////////////////////////////////////
//
bool Logger::AddListener( ILogListener* iListener )
{
	std::vector<ILogListener*>::iterator tmp =
		std::find( m_Listeners.begin(), m_Listeners.end(), iListener );

	// Return false if the listener is already in the vector. This is not expected
	// but there is nothing really wrong either.
	if ( tmp != m_Listeners.end() )
		return false;

	m_Listeners.push_back( iListener );
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
bool Logger::RemoveListener( ILogListener* iListener )
{
	std::vector<ILogListener*>::iterator tmp =
		std::find( m_Listeners.begin(), m_Listeners.end(), iListener );

	// Return false if the listener could not be found
	if ( tmp == m_Listeners.end() )
		return false;
	else
		m_Listeners.erase( std::remove( m_Listeners.begin(), m_Listeners.end(), iListener ) );
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
// Really important method : It triggers all Notify() methods of all listeners.
bool Logger::NotifyListeners()
{
	std::for_each( this->m_Listeners.begin(), this->m_Listeners.end(), Notifier( this->m_Os.str(), this->m_Level ) );

	// Return false if there are no listeners in the vector
	return ( this->m_Listeners.size() > 0 );
}

////////////////////////////////////////////////////////////////////////////////
//
ELogLevel Logger::FromString( const std::string& iLevel )
{
	if ( iLevel == "DEBUG2" )
		return logDEBUG2;
	if ( iLevel == "DEBUG1" )
		return logDEBUG1;
	if ( iLevel == "DEBUG" )
		return logDEBUG;
	if ( iLevel == "INFO" )
		return logINFO;
	if ( iLevel == "WARNING" )
		return logWARNING;
	if ( iLevel == "ERROR" )
		return logERROR;
	if ( iLevel == "CRITICAL" )
		return logCRITICAL;
	
	// If the log level is not found, we return the default one (logINFO)
	LOGW << "Unknown logging level '" << iLevel << "'. Using INFO level as default.";
	return logINFO;
}


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <windows.h>

////////////////////////////////////////////////////////////////////////////////
//
inline std::string NowTime()
{
    const int MAX_LEN = 200;
    char buffer[MAX_LEN];
    if ( GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, 
            "HH':'mm':'ss", buffer, MAX_LEN) == 0 )
        return "Error in NowTime()";

    char result[100] = {0};
    static DWORD first = GetTickCount();
    std::sprintf( result, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000 ); 
    return result;
}

#else

#include <sys/time.h>

////////////////////////////////////////////////////////////////////////////////
//
inline std::string NowTime()
{
    char buffer[11];
    time_t t;
    time( &t );
    tm r = {0};
    strftime( buffer, sizeof(buffer), "%X", localtime_r( &t, &r ) );
    struct timeval tv;
    gettimeofday( &tv, 0 );
    char result[100] = {0};
    std::sprintf( result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000 ); 
    return result;
}

#endif //WIN32

} // namespace CppLib

#endif // !CPPLIB_INCLUDE_LOGGER_H
