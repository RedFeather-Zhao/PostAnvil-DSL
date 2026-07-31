find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

if(NOT TARGET postanvil_static)
    message(FATAL_ERROR "Python binding requires POSTANVIL_BUILD_STATIC=ON")
endif()

pybind11_add_module(postanvil_python MODULE module.cpp)
target_compile_features(postanvil_python PRIVATE cxx_std_20)
target_link_libraries(postanvil_python PRIVATE PostAnvil::static)
set_target_properties(postanvil_python PROPERTIES OUTPUT_NAME "_postanvil")

if(MSVC)
    target_compile_options(postanvil_python PRIVATE /utf-8)
endif()

install(TARGETS postanvil_python
    LIBRARY DESTINATION postanvil
    RUNTIME DESTINATION postanvil)
