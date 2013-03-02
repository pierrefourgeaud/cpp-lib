
#include <Windows.h>
#include <iostream>
#include <fstream>

#include <vector>

#include "Common.h"

using namespace std;

fstream fo;

void AddVector()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	QueryPerformanceCounter( &before );
	vector<int> v;

	for ( int i = 0; i < 250000; i++ )
	{
		v.push_back( i );
	}
	QueryPerformanceCounter( &after );
	fo << "Add :\t\t" << after.QuadPart - before.QuadPart << std::endl;
}

void IterationVector()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	vector<int> v;

	for ( int i = 0; i < 250000; i++ )
	{
		v.push_back( i );
	}

	QueryPerformanceCounter( &before );
	unsigned int size = v.size();
	for ( unsigned int i = 0; i < size; i++ )
	{
		v[i];
	}

	QueryPerformanceCounter( &after );
	fo << "Iteration :\t" << after.QuadPart - before.QuadPart << std::endl;
}

void PopVector()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	vector<int> v;

	for ( int i = 0; i < 250000; i++ )
	{
		v.push_back( i );
	}

	QueryPerformanceCounter( &before );
	while ( !v.empty() )
	{
		v.pop_back();
	}

	QueryPerformanceCounter( &after );
	fo << "Pop :\t\t" << after.QuadPart - before.QuadPart << std::endl;
}

void DeleteVector()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	vector<int>* v = new vector<int>();

	for ( int i = 0; i < 250000; i++ )
	{
		v->push_back( i );
	}

	QueryPerformanceCounter( &before );
	
	delete v;

	QueryPerformanceCounter( &after );
	fo << "Delete :\t" << after.QuadPart - before.QuadPart << std::endl;
}

int main( int argc, char** argv )
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	fo.open( BENCHMARK_FILENAME, std::fstream::out | std::fstream::app );

	fo << "[STD::VECTOR] Warning : Can't pop front, using pop_back instead." << std::endl;
	QueryPerformanceCounter( &before );
	AddVector();
	IterationVector();
	PopVector();
	DeleteVector();
	QueryPerformanceCounter( &after );
	fo << "######################## Total time : " << after.QuadPart - before.QuadPart << std::endl << std::endl;
	
	if ( fo.is_open() )
		fo.close();
	return 0;
}