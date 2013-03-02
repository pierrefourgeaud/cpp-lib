
#include <Windows.h>
#include <iostream>
#include <fstream>

#include <queue>

#include "Common.h"

using namespace std;

fstream fo;

void AddQueue()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	QueryPerformanceCounter( &before );
	queue<int> q;

	for ( int i = 0; i < 250000; i++ )
	{
		q.push( i );
	}
	QueryPerformanceCounter( &after );
	fo << "Add :\t\t" << after.QuadPart - before.QuadPart << std::endl;
}

void IterationQueue()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	queue<int> q;

	for ( int i = 0; i < 250000; i++ )
	{
		q.push( i );
	}

	QueryPerformanceCounter( &before );

	while ( !q.empty() )
	{
		q.back();
		q.pop();
	}

	QueryPerformanceCounter( &after );
	fo << "Iteration :\t" << after.QuadPart - before.QuadPart << std::endl;
}

void PopQueue()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	queue<int> q;

	for ( int i = 0; i < 250000; i++ )
	{
		q.push( i );
	}

	QueryPerformanceCounter( &before );

	while ( !q.empty() )
	{
		q.pop();
	}

	QueryPerformanceCounter( &after );
	fo << "Pop :\t\t" << after.QuadPart - before.QuadPart << std::endl;
}

void DeleteQueue()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	queue<int>* q = new queue<int>();

	for ( int i = 0; i < 250000; i++ )
	{
		q->push( i );
	}

	QueryPerformanceCounter( &before );
	
	delete q;

	QueryPerformanceCounter( &after );
	fo << "Delete :\t" << after.QuadPart - before.QuadPart << std::endl;
}

int main( int argc, char** argv )
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	fo.open( BENCHMARK_FILENAME, std::fstream::out | std::fstream::app );

	fo << "[STD::QUEUE] Warning : Seems to be difficult to access to the second element. Impossible to iterate without saving the queue before." << std::endl;
	QueryPerformanceCounter( &before );
	AddQueue();
	IterationQueue();
	PopQueue();
	DeleteQueue();
	QueryPerformanceCounter( &after );
	fo << "######################## Total time : " << after.QuadPart - before.QuadPart << std::endl << std::endl;
	
	if ( fo.is_open() )
		fo.close();
	return 0;
}