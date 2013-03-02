
#include <Windows.h>
#include <iostream>
#include <fstream>

#include <fast_list.h>

#include "Common.h"

std::fstream fo;

void AddFastList()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	QueryPerformanceCounter( &before );
	FastList<int> list;

	for ( int i = 0; i < 250000; i++ )
	{
		list.Push( i );
	}
	QueryPerformanceCounter( &after );
	fo << "Add :\t\t" << after.QuadPart - before.QuadPart << std::endl;
}

void IterationFastList()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	FastList<int> list;

	for ( int i = 0; i < 250000; i++ )
	{
		list.Push( i );
	}
	
	QueryPerformanceCounter( &before );
	FastList<int>::iterator it = list.Begin();

	for ( ; !it.End(); it.Next() )
	{
		it.Data();
	}

	QueryPerformanceCounter( &after );
	fo << "Iteration :\t" << after.QuadPart - before.QuadPart << std::endl;
}

void RemoveFastList()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	FastList<int> list;

	for ( int i = 0; i < 250000; i++ )
	{
		list.Push( i );
	}

	QueryPerformanceCounter( &before );
	while ( !list.Empty() )
	{
		list.Pop();
	}

	QueryPerformanceCounter( &after );
	fo << "Pop :\t\t" << after.QuadPart - before.QuadPart << std::endl;
}

void DeleteFastList()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	FastList<int>* list = new FastList<int>();

	for ( int i = 0; i < 250000; i++ )
	{
		list->Push( i );
	}

	QueryPerformanceCounter( &before );
	
	delete list;

	QueryPerformanceCounter( &after );
	fo << "Delete :\t" << after.QuadPart - before.QuadPart << std::endl;
}

int main( int argc, char** argv )
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	fo.open( BENCHMARK_FILENAME, std::fstream::out | std::fstream::app );

	fo << "[FAST_LIST]" << std::endl;
	QueryPerformanceCounter( &before );
	AddFastList();
	IterationFastList();	
	RemoveFastList();
	DeleteFastList();
	QueryPerformanceCounter( &after );
	fo << "######################## Total time : " << after.QuadPart - before.QuadPart << std::endl << std::endl;

	if ( fo.is_open() )
		fo.close();
	return 0;
}

