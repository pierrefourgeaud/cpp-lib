
CMAKE_MINIMUM_REQUIRED ( VERSION 2.6 )

# ---------- CppLib ----------
PROJECT( BenchMark )

SETUP_BENCHMARK ( FastList )
SETUP_BENCHMARK ( StdList )
SETUP_BENCHMARK ( StdVector )
SETUP_BENCHMARK ( StdQueue )
SETUP_BENCHMARK ( StdDeque )

ADD_EXECUTABLE (
	BenchMark
	Benchmark.cpp
)

add_dependencies( BenchMark
	BenchMark_FastList
	BenchMark_StdList
	BenchMark_StdVector
	BenchMark_StdQueue
	BenchMark_StdDeque
)