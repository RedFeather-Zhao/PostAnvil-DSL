cmake_minimum_required(VERSION 3.25)

project(PostAnvil VERSION 0.8.0 LANGUAGES CXX)

include(CMakePackageConfigHelpers)      # 用于生成库的 CMake 导入配置文件
include(GNUInstallDirs)                 # 统一跨平台安装目录规范


# 编译开关
option(POSTANVIL_BUILD_STATIC "Build the PostAnvil static library" ON)
option(POSTANVIL_BUILD_SHARED "Build the PostAnvil shared library" ON)
option(POSTANVIL_BUILD_TESTS "Build the portable PostAnvil test suite" ON)
option(POSTANVIL_BUILD_PYTHON "Build the Python extension module" OFF)
option(POSTANVIL_BUILD_ANDROID_JNI "Build the Android JNI adapter" OFF)

if(NOT POSTANVIL_BUILD_STATIC AND NOT POSTANVIL_BUILD_SHARED)
	message(FATAL_ERROR "At least one of POSTANVIL_BUILD_STATIC or POSTANVIL_BUILD_SHARED must be ON")
endif()

# Antlr4 CPP Runtime 与 PostAnvil.g4 Antlr4 生成目录
set(POSTANVIL_RUNTIME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/antlr4-runtime/src")
set(POSTANVIL_GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generated/antlr")

# CONFIGURE_DEPENDS 配置依赖确保语法变动时刷新
file(GLOB_RECURSE POSTANVIL_ANTLR_RUNTIME_SOURCES CONFIGURE_DEPENDS
	"${POSTANVIL_RUNTIME_DIR}/*.cpp")

set(POSTANVIL_GENERATED_SOURCES
	"${POSTANVIL_GENERATED_DIR}/PostAnvilBaseListener.cpp"
	"${POSTANVIL_GENERATED_DIR}/PostAnvilLexer.cpp"
	"${POSTANVIL_GENERATED_DIR}/PostAnvilListener.cpp"
	"${POSTANVIL_GENERATED_DIR}/PostAnvilParser.cpp")

# 中间目标：Runtime 与生成解析器只编译一次，静态库和动态库复用同一批对象文件。
add_library(postanvil_core_objects OBJECT
	${POSTANVIL_ANTLR_RUNTIME_SOURCES}
	${POSTANVIL_GENERATED_SOURCES})
set_target_properties(postanvil_core_objects PROPERTIES
	POSITION_INDEPENDENT_CODE ON)   # 强制生成位置无关代码，Linux/macOS/Android 编译动态库用
target_compile_features(postanvil_core_objects PUBLIC cxx_std_20)   # 请勿低于 c++20
target_compile_definitions(postanvil_core_objects PRIVATE ANTLR4CPP_STATIC)
target_include_directories(postanvil_core_objects PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
	"${POSTANVIL_GENERATED_DIR}"
	"${POSTANVIL_RUNTIME_DIR}")

if(MSVC)
	target_compile_options(postanvil_core_objects PRIVATE /utf-8 /bigobj /wd4251 /wd4275)
else()
	target_compile_options(postanvil_core_objects PRIVATE -Wno-overloaded-virtual)
endif()

find_package(Threads REQUIRED) # ANTLR4 C++ 运行时依赖系统线程库

# 通用配置函数
function(postanvil_configure_library target_name)
	target_compile_features(${target_name} PUBLIC cxx_std_20)
	target_include_directories(${target_name}
		PUBLIC
			"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
			"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
	target_link_libraries(${target_name} PRIVATE Threads::Threads)
	set_target_properties(${target_name} PROPERTIES
		DEBUG_POSTFIX "_d"                            # Debug 库自动加后缀 _d
		VERSION "${PROJECT_VERSION}"                  # 动态库版本号
		SOVERSION "${PROJECT_VERSION_MAJOR}")         # 主版本号
	if(MSVC)
		target_compile_options(${target_name} PRIVATE /utf-8)
	endif()
endfunction()

if(POSTANVIL_BUILD_STATIC)
	add_library(postanvil_static STATIC
		src/api.cpp
		$<TARGET_OBJECTS:postanvil_core_objects>)
	add_library(PostAnvil::static ALIAS postanvil_static)   # PostAnvil::static 别名
	set_target_properties(postanvil_static PROPERTIES
		OUTPUT_NAME postanvil_static
		EXPORT_NAME static
		POSITION_INDEPENDENT_CODE ON)
	target_compile_definitions(postanvil_static
		PRIVATE ANTLR4CPP_STATIC POSTANVIL_STATIC
		INTERFACE POSTANVIL_STATIC)
	target_include_directories(postanvil_static PRIVATE
		"${POSTANVIL_GENERATED_DIR}"
		"${POSTANVIL_RUNTIME_DIR}")
	postanvil_configure_library(postanvil_static)
endif()

if(POSTANVIL_BUILD_SHARED)
	add_library(postanvil_shared SHARED
		src/api.cpp
		$<TARGET_OBJECTS:postanvil_core_objects>)
	add_library(PostAnvil::shared ALIAS postanvil_shared)   # PostAnvil::shared 别名
	set_target_properties(postanvil_shared PROPERTIES
		OUTPUT_NAME postanvil               # postanvil 名称简化
		EXPORT_NAME shared                  # 
		WINDOWS_EXPORT_ALL_SYMBOLS ON)      # Windows 下自动导出全部符号，无需手动写 __declspec(dllexport)
	target_compile_definitions(postanvil_shared PRIVATE
		ANTLR4CPP_STATIC POSTANVIL_BUILD_SHARED)
	target_include_directories(postanvil_shared PRIVATE
		"${POSTANVIL_GENERATED_DIR}"
		"${POSTANVIL_RUNTIME_DIR}")
	postanvil_configure_library(postanvil_shared)
endif()

# 显式生成目标，修改 grammar 后按需运行，不强迫普通构建依赖 Java。
# cmake --build . --target postanvil_generate_parser
find_package(Java QUIET COMPONENTS Runtime)
if(Java_Runtime_FOUND)
	add_custom_target(postanvil_generate_parser
		COMMAND "${Java_JAVA_EXECUTABLE}" -jar
			"${CMAKE_CURRENT_SOURCE_DIR}/tools/antlr/antlr-4.13.2-complete.jar"
			-Dlanguage=Cpp -listener -visitor -Xexact-output-dir
			-o "${POSTANVIL_GENERATED_DIR}"
			"${CMAKE_CURRENT_SOURCE_DIR}/grammar/PostAnvil.g4"
		COMMENT "Generating PostAnvil parser with ANTLR 4.13.2"
		VERBATIM)
endif()

# 测试样例
if(POSTANVIL_BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()

# python绑定
if(POSTANVIL_BUILD_PYTHON)
	add_subdirectory(bindings/python)
endif()

# 安卓jni绑定
if(POSTANVIL_BUILD_ANDROID_JNI)
	if(NOT ANDROID)
		message(FATAL_ERROR "POSTANVIL_BUILD_ANDROID_JNI requires an Android CMake toolchain")
	endif()
	add_subdirectory(bindings/android)
endif()

# 动态/静态库
set(POSTANVIL_INSTALL_TARGETS)
if(TARGET postanvil_static)
	list(APPEND POSTANVIL_INSTALL_TARGETS postanvil_static)
endif()
if(TARGET postanvil_shared)
	list(APPEND POSTANVIL_INSTALL_TARGETS postanvil_shared)
endif()

# 动态收集当前开启的库，统一安装
install(TARGETS ${POSTANVIL_INSTALL_TARGETS}
	EXPORT PostAnvilTargets
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

install(FILES include/PostAnvil.h
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(FILES   # 仅暴露必要接口
	include/postanvil/api.hpp
	include/postanvil/detail.hpp
	include/postanvil/error.hpp
	include/postanvil/instance.hpp
	include/postanvil/scene.hpp
	include/postanvil/type.hpp
	include/postanvil/utils.hpp
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/postanvil")

# 生成并安装 CMake Config 文件
configure_package_config_file(
	cmake/PostAnvilConfig.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/PostAnvilConfig.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/PostAnvil")
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/PostAnvilConfigVersion.cmake"
	VERSION "${PROJECT_VERSION}"
	COMPATIBILITY SameMajorVersion)

install(EXPORT PostAnvilTargets
	FILE PostAnvilTargets.cmake
	NAMESPACE PostAnvil::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/PostAnvil")
install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/PostAnvilConfig.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/PostAnvilConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/PostAnvil")
install(FILES LICENSE.txt DESTINATION "${CMAKE_INSTALL_DATADIR}/licenses/PostAnvil")

# find_package(PostAnvil REQUIRED)
# target_link_libraries(your_app PRIVATE PostAnvil::static)

set(CPACK_PACKAGE_NAME PostAnvil)
set(CPACK_PACKAGE_VENDOR RedFeather-Zhao)
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_FILE_NAME
	"PostAnvil-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_GENERATOR "ZIP;TGZ")
include(CPack)
