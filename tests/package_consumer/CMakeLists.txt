cmake_minimum_required(VERSION 3.25)
project(PostAnvilPackageConsumer LANGUAGES CXX)

find_package(PostAnvil CONFIG REQUIRED)

option(POSTANVIL_CONSUMER_BUILD_SHARED
	"Build the shared-library package consumer" ON)

add_executable(postanvil_package_consumer main.cpp)
target_compile_features(postanvil_package_consumer PRIVATE cxx_std_20)
target_link_libraries(postanvil_package_consumer PRIVATE PostAnvil::static)

enable_testing()
add_test(NAME postanvil.package.static COMMAND postanvil_package_consumer)

if(POSTANVIL_CONSUMER_BUILD_SHARED)
	if(NOT TARGET PostAnvil::shared)
		message(FATAL_ERROR
			"POSTANVIL_CONSUMER_BUILD_SHARED requires PostAnvil::shared")
	endif()

	add_executable(postanvil_package_consumer_shared main.cpp)
	target_compile_features(postanvil_package_consumer_shared PRIVATE cxx_std_20)
	target_link_libraries(postanvil_package_consumer_shared PRIVATE PostAnvil::shared)
	if(WIN32)
		add_custom_command(TARGET postanvil_package_consumer_shared POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
				"$<TARGET_FILE:PostAnvil::shared>"
				"$<TARGET_FILE_DIR:postanvil_package_consumer_shared>")
	endif()
	add_test(NAME postanvil.package.shared
		COMMAND postanvil_package_consumer_shared)
endif()
