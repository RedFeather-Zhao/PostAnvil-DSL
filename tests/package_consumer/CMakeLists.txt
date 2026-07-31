cmake_minimum_required(VERSION 3.25)
project(PostAnvilPackageConsumer LANGUAGES CXX)

find_package(PostAnvil CONFIG REQUIRED)

add_executable(postanvil_package_consumer main.cpp)
target_compile_features(postanvil_package_consumer PRIVATE cxx_std_20)
target_link_libraries(postanvil_package_consumer PRIVATE PostAnvil::static)

add_executable(postanvil_package_consumer_shared main.cpp)
target_compile_features(postanvil_package_consumer_shared PRIVATE cxx_std_20)
target_link_libraries(postanvil_package_consumer_shared PRIVATE PostAnvil::shared)
if(WIN32)
	add_custom_command(TARGET postanvil_package_consumer_shared POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"$<TARGET_FILE:PostAnvil::shared>"
			"$<TARGET_FILE_DIR:postanvil_package_consumer_shared>")
endif()
