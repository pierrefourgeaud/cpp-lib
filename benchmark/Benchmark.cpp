
#include <Windows.h>
#include <fstream>
#include <iostream>

#include "Common.h"

using namespace std;

void CleanOutputFile()
{
	fstream fo( BENCHMARK_FILENAME, fstream::out );
	fo.close();
}

int main( int argc, char** argv )
{
	CleanOutputFile();

	std::cout << "--------------------" << std::endl;
	std::cout << "[STD::LIST]" << std::endl;
	system( "BenchMark_StdList.exe" );
	std::cout << "[STD::VECTOR] Warning : Can't pop front, using pop_back instead." << std::endl;
	system( "BenchMark_StdVector.exe" );
	std::cout << "[STD::QUEUE] Warning : Seems to be difficult to access to the second element." << std::endl;
	system( "BenchMark_StdQueue.exe" );
	std::cout << "[STD::DEQUE]" << std::endl;
	system( "BenchMark_StdDeque.exe" );
	std::cout << "[FAST_LIST]" << std::endl;
	system( "BenchMark_FastList.exe" );

	system( "pause" );
	return 0;
}