
#include <Windows.h>
#include <iostream>
#include <fstream>

#include <deque>

#include "Common.h"

using namespace std;

fstream fo;

void AddDeque()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	QueryPerformanceCounter( &before );
	deque<int> d;

	for ( int i = 0; i < 250000; i++ )
	{
		d.push_back( i );
	}
	QueryPerformanceCounter( &after );
	fo << "Add :\t\t" << after.QuadPart - before.QuadPart << std::endl;
}

void IterationDeque()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	deque<int> d;

	for ( int i = 0; i < 250000; i++ )
	{
		d.push_back( i );
	}

	QueryPerformanceCounter( &before );
	unsigned int size = d.size();
	for ( unsigned int i = 0; i < size; i++ )
	{
		d[i];
	}

	QueryPerformanceCounter( &after );
	fo << "Iteration :\t" << after.QuadPart - before.QuadPart << std::endl;
}

void PopDeque()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	deque<int> d;

	for ( int i = 0; i < 250000; i++ )
	{
		d.push_back( i );
	}

	QueryPerformanceCounter( &before );
	while ( !d.empty() )
	{
		d.pop_front();
	}

	QueryPerformanceCounter( &after );
	fo << "Pop :\t\t" << after.QuadPart - before.QuadPart << std::endl;
}

void DeleteDeque()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	deque<int>* d = new deque<int>();

	for ( int i = 0; i < 250000; i++ )
	{
		d->push_back( i );
	}

	QueryPerformanceCounter( &before );
	
	delete d;

	QueryPerformanceCounter( &after );
	fo << "Delete :\t" << after.QuadPart - before.QuadPart << std::endl;
}

int main( int argc, char** argv )
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	fo.open( BENCHMARK_FILENAME, std::fstream::out | std::fstream::app );

	fo << "[STD::DEQUE]" << std::endl;
	QueryPerformanceCounter( &before );
	AddDeque();
	IterationDeque();
	PopDeque();
	DeleteDeque();
	QueryPerformanceCounter( &after );
	fo << "######################## Total time : " << after.QuadPart - before.QuadPart << std::endl << std::endl;
	
	if ( fo.is_open() )
		fo.close();
	return 0;
}