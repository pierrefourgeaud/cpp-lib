
#include <Windows.h>
#include <iostream>
#include <fstream>

#include <list>

#include "Common.h"

using namespace std;

fstream fo;

void AddList()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	QueryPerformanceCounter( &before );
	list<int> l;

	for ( int i = 0; i < 250000; i++ )
	{
		l.push_back( i );
	}
	QueryPerformanceCounter( &after );
	fo << "Add :\t\t" << after.QuadPart - before.QuadPart << std::endl;
}

void IterationList()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	list<int> l;

	for ( int i = 0; i < 250000; i++ )
	{
		l.push_back( i );
	}

	QueryPerformanceCounter( &before );
	list<int>::iterator it = l.begin();
	list<int>::iterator ite = l.end();

	for ( ; it != ite; ++it )
	{
		(*it);
	}

	QueryPerformanceCounter( &after );
	fo << "Iteration :\t" << after.QuadPart - before.QuadPart << std::endl;
}

void PopList()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	list<int> l;

	for ( int i = 0; i < 250000; i++ )
	{
		l.push_back( i );
	}

	QueryPerformanceCounter( &before );
	while ( !l.empty() )
	{
		l.pop_front();
	}

	QueryPerformanceCounter( &after );
	fo << "Pop :\t\t" << after.QuadPart - before.QuadPart << std::endl;
}

void DeleteList()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	list<int>* l = new list<int>();

	for ( int i = 0; i < 250000; i++ )
	{
		l->push_back( i );
	}

	QueryPerformanceCounter( &before );
	
	delete l;

	QueryPerformanceCounter( &after );
	fo << "Delete :\t" << after.QuadPart - before.QuadPart << std::endl;
}

int main( int argc, char** argv )
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	fo.open( BENCHMARK_FILENAME, std::fstream::out | std::fstream::app );

	fo << "[STD::LIST]" << std::endl;
	QueryPerformanceCounter( &before );
	AddList();
	IterationList();
	PopList();
	DeleteList();
	QueryPerformanceCounter( &after );
	fo << "######################## Total time : " << after.QuadPart - before.QuadPart << std::endl << std::endl;
	
	if ( fo.is_open() )
		fo.close();
	return 0;
}