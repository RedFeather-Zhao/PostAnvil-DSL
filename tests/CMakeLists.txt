set(POSTANVIL_TEST_SOURCES
	ApiTests.cpp
	BasicFilterRuleTests.cpp
	CompileDiagnosticsTests.cpp
	ControlFlowTests.cpp
	IntegrationTests.cpp
	SortFunctionTests.cpp
	TestAttributeCollection.cpp
	TestSupport.cpp
	ValueBuiltinTests.cpp
	main.cpp)

add_executable(postanvil_tests ${POSTANVIL_TEST_SOURCES})
target_compile_features(postanvil_tests PRIVATE cxx_std_20)
target_include_directories(postanvil_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_precompile_headers(postanvil_tests PRIVATE pch.h)

if(TARGET postanvil_static)
	target_link_libraries(postanvil_tests PRIVATE PostAnvil::static)
else()
	target_link_libraries(postanvil_tests PRIVATE PostAnvil::shared)
endif()

if(MSVC)
	target_compile_options(postanvil_tests PRIVATE /utf-8 /W4)
else()
	target_compile_options(postanvil_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME postanvil.all COMMAND postanvil_tests)
