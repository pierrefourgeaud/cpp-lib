
CMAKE_MINIMUM_REQUIRED ( VERSION 2.6 )

# ---------- CppLib ----------
PROJECT( CppLib )

# --------- Setup the Executable output Directory -------------
SET ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin CACHE PATH "Single Directory for all Executables." )

#
SET ( LIBRARY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src )

###
# Useful Macro
###

MACRO ( ASSERT_FIND TEST COMMENT )
	IF ( NOT EXISTS ${TEST} )
		MESSAGE ( "Assertion failed : ${COMMENT}" )
	ENDIF ( NOT EXISTS ${TEST} )
ENDMACRO ( ASSERT_FIND )

# BenchMark
MACRO ( SETUP_BENCHMARK COMPONENT_NAME )
	include_directories(
		${LIBRARY_INCLUDE_DIR}
	)

	SET ( TARGET_NAME BenchMark_${COMPONENT_NAME} )

	add_executable( ${TARGET_NAME}
		BenchMark${COMPONENT_NAME}.cpp
	)
ENDMACRO ( SETUP_BENCHMARK )

ADD_SUBDIRECTORY ( "benchmark" )