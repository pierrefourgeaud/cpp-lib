
#include "../include/logger.hpp"

using namespace CppLib;

void test1()
{
	ILogListener* bufferLogger = new BufferLogger();
	Logger::AddListener(bufferLogger);

	Logger::ReportingLevel() = logDEBUG;

	LOGE << "test log error" << std::endl;
}

int main(void)
{
	test1();
	return 0;
}