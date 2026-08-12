# PostAnvil Android toolchain 入口。
# 优先使用 POSTANVIL_ANDROID_NDK，其次使用 Android 常见环境变量。
set(_postanvil_ndk_candidates)

if(POSTANVIL_ANDROID_NDK)
	list(APPEND _postanvil_ndk_candidates "${POSTANVIL_ANDROID_NDK}")
endif()
if(CMAKE_ANDROID_NDK)
	list(APPEND _postanvil_ndk_candidates "${CMAKE_ANDROID_NDK}")
endif()
if(DEFINED ENV{ANDROID_NDK_HOME} AND NOT "$ENV{ANDROID_NDK_HOME}" STREQUAL "")
	list(APPEND _postanvil_ndk_candidates "$ENV{ANDROID_NDK_HOME}")
endif()
if(DEFINED ENV{ANDROID_NDK_ROOT} AND NOT "$ENV{ANDROID_NDK_ROOT}" STREQUAL "")
	list(APPEND _postanvil_ndk_candidates "$ENV{ANDROID_NDK_ROOT}")
endif()

list(REMOVE_DUPLICATES _postanvil_ndk_candidates)
set(_postanvil_ndk_matches)

foreach(_postanvil_ndk_candidate IN LISTS _postanvil_ndk_candidates)
	file(TO_CMAKE_PATH "${_postanvil_ndk_candidate}" _postanvil_ndk_candidate)
	get_filename_component(_postanvil_ndk_candidate
		"${_postanvil_ndk_candidate}" ABSOLUTE)

	if(EXISTS "${_postanvil_ndk_candidate}/build/cmake/android.toolchain.cmake")
		list(APPEND _postanvil_ndk_matches "${_postanvil_ndk_candidate}")
		continue()
	endif()

	# 兼容解压后外层目录下只有一个版本子目录的情况。
	file(GLOB _postanvil_ndk_children LIST_DIRECTORIES true
		"${_postanvil_ndk_candidate}/*")
	foreach(_postanvil_ndk_child IN LISTS _postanvil_ndk_children)
		if(IS_DIRECTORY "${_postanvil_ndk_child}" AND
			EXISTS "${_postanvil_ndk_child}/build/cmake/android.toolchain.cmake")
			list(APPEND _postanvil_ndk_matches "${_postanvil_ndk_child}")
		endif()
	endforeach()
endforeach()

list(REMOVE_DUPLICATES _postanvil_ndk_matches)
list(LENGTH _postanvil_ndk_matches _postanvil_ndk_match_count)

if(_postanvil_ndk_match_count EQUAL 0)
	message(FATAL_ERROR
		"Android NDK was not found. Set POSTANVIL_ANDROID_NDK or "
		"ANDROID_NDK_HOME to an NDK root containing "
		"build/cmake/android.toolchain.cmake. If Visual Studio was already "
		"running when the environment variable changed, restart Visual Studio.")
endif()
if(_postanvil_ndk_match_count GREATER 1)
	list(JOIN _postanvil_ndk_matches "\n  " _postanvil_ndk_match_text)
	message(FATAL_ERROR
		"Multiple Android NDK installations were found:\n  "
		"${_postanvil_ndk_match_text}\n"
		"Set POSTANVIL_ANDROID_NDK to the required NDK root explicitly.")
endif()

list(GET _postanvil_ndk_matches 0 _postanvil_ndk_root)
set(POSTANVIL_ANDROID_NDK "${_postanvil_ndk_root}" CACHE PATH
	"Android NDK root used by PostAnvil" FORCE)
set(CMAKE_ANDROID_NDK "${_postanvil_ndk_root}" CACHE PATH
	"Android NDK root" FORCE)
set(ENV{ANDROID_NDK_HOME} "${_postanvil_ndk_root}")
list(APPEND CMAKE_TRY_COMPILE_PLATFORM_VARIABLES
	POSTANVIL_ANDROID_NDK
	CMAKE_ANDROID_NDK)
list(REMOVE_DUPLICATES CMAKE_TRY_COMPILE_PLATFORM_VARIABLES)

message(STATUS "PostAnvil Android NDK: ${_postanvil_ndk_root}")
include("${_postanvil_ndk_root}/build/cmake/android.toolchain.cmake")

unset(_postanvil_ndk_candidate)
unset(_postanvil_ndk_candidates)
unset(_postanvil_ndk_child)
unset(_postanvil_ndk_children)
unset(_postanvil_ndk_match_count)
unset(_postanvil_ndk_matches)
unset(_postanvil_ndk_match_text)
unset(_postanvil_ndk_root)
