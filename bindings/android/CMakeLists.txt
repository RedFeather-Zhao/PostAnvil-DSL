if(NOT TARGET postanvil_static)
    message(FATAL_ERROR "Android JNI binding requires POSTANVIL_BUILD_STATIC=ON")
endif()

add_library(postanvil_jni SHARED postanvil_jni.cpp)
target_compile_features(postanvil_jni PRIVATE cxx_std_20)
target_link_libraries(postanvil_jni PRIVATE PostAnvil::static android log)
set_target_properties(postanvil_jni PROPERTIES OUTPUT_NAME "postanvil_jni")

install(TARGETS postanvil_jni
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(FILES java/org/postanvil/NativeBridge.java
	DESTINATION "${CMAKE_INSTALL_DATADIR}/PostAnvil/android/java/org/postanvil")
