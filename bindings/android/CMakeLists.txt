if(NOT TARGET postanvil_static)
    message(FATAL_ERROR "Android JNI binding requires POSTANVIL_BUILD_STATIC=ON")
endif()

find_package(Java 11 REQUIRED COMPONENTS Development)

set(POSTANVIL_JAVA_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/java/org/postanvil/NativeBridge.java")
set(POSTANVIL_JAVA_CLASSES_DIR "${CMAKE_CURRENT_BINARY_DIR}/java-classes")
set(POSTANVIL_JAVA_JAR "${CMAKE_CURRENT_BINARY_DIR}/postanvil-java.jar")

add_custom_command(
    OUTPUT "${POSTANVIL_JAVA_JAR}"
    COMMAND "${CMAKE_COMMAND}" -E rm -rf "${POSTANVIL_JAVA_CLASSES_DIR}"
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${POSTANVIL_JAVA_CLASSES_DIR}"
    COMMAND "${Java_JAVAC_EXECUTABLE}" --release 8
        -d "${POSTANVIL_JAVA_CLASSES_DIR}" "${POSTANVIL_JAVA_SOURCE}"
    COMMAND "${Java_JAR_EXECUTABLE}" --create
        --file "${POSTANVIL_JAVA_JAR}" -C "${POSTANVIL_JAVA_CLASSES_DIR}" .
    DEPENDS "${POSTANVIL_JAVA_SOURCE}"
    COMMENT "Compiling PostAnvil Java binding"
    VERBATIM)
add_custom_target(postanvil_java ALL DEPENDS "${POSTANVIL_JAVA_JAR}")

add_library(postanvil_jni SHARED postanvil_jni.cpp)
target_compile_features(postanvil_jni PRIVATE cxx_std_20)
target_link_libraries(postanvil_jni PRIVATE PostAnvil::static android log)
set_target_properties(postanvil_jni PROPERTIES OUTPUT_NAME "postanvil_jni")
add_dependencies(postanvil_jni postanvil_java)

install(TARGETS postanvil_jni
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(FILES java/org/postanvil/NativeBridge.java
	DESTINATION "${CMAKE_INSTALL_DATADIR}/PostAnvil/android/java/org/postanvil")
install(FILES "${POSTANVIL_JAVA_JAR}"
	DESTINATION "${CMAKE_INSTALL_DATADIR}/PostAnvil/android")
