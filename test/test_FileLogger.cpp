
#include "../include/logger.hpp"

#include <iostream>
#include <fstream>

using namespace CppLib;

const std::string g_FileName = "TestFileLogger.txt";

#define START_TESTSUITE()                                                     \
	int TestExecuted = 0;                                                     \
	int TestPassed   = 0;                                                     \

#define EXECUTE_TEST( TestName )                                              \
    if ( TestName() ) { TestPassed++; }                                       \
	TestExecuted++;                                                           \
	ClearFile();                                                              \

#define END_TESTSUITE()                                                       \
	std::cout << "Tests Executed: " << TestExecuted <<                        \
		" - Test Passed: " << TestPassed << std::endl;                        \

bool fileTester(const std::string& iBuffer)
{
	// Function which reads the file and compare to the buffer
	std::ifstream file(g_FileName);

	std::stringstream fileBuffer;
	fileBuffer << file.rdbuf();

	file.close();

	bool result = fileBuffer.str().find( iBuffer ) != std::string::npos;
	if ( !result )
	{
		std::cout << "Comparison failed: Actual: \"" << fileBuffer.str() << "\", Expected: \"" << iBuffer << "\"." << std::endl;
	}

	return result;
}

void ClearFile()
{
	return;
	std::fstream file;

	file.open(g_FileName, std::fstream::ios_base::out | std::fstream::ios_base::trunc);

	file.close();
}

bool testErrorLogLevelLowerThanReportingLevel()
{
	ILogListener* fileLogger = new FileLogger( g_FileName );
	Logger::AddListener( fileLogger );

	Logger::ReportingLevel() = logDEBUG;

	LOGE << "test log error" << std::endl;

	return fileTester( "test log error" );
}

int main(void)
{
	START_TESTSUITE()

	EXECUTE_TEST( testErrorLogLevelLowerThanReportingLevel );

	END_TESTSUITE()
	return 0;
}