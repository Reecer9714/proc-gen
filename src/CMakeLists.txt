find_package(fmt REQUIRED)

add_library(cmake_cpp_boilerplate_lib
    locations/Location.hpp
    locations/LocationBuilder.hpp
    locations/LocationFactory.hpp
    locations/TownGenerator.hpp
    )
set_target_properties(cmake_cpp_boilerplate_lib PROPERTIES LINKER_LANGUAGE CXX)

add_library(cmake_cpp_boilerplate::lib ALIAS cmake_cpp_boilerplate_lib)
target_link_libraries(cmake_cpp_boilerplate_lib
        PUBLIC cmake_cpp_boilerplate::compiler_options fmt::fmt)
target_include_directories(cmake_cpp_boilerplate_lib PUBLIC "${PROJECT_SOURCE_DIR}/include")

if(${BP_BUILD_TESTS_COVERAGE})
    target_compile_options(cmake_cpp_boilerplate_lib PUBLIC -fprofile-arcs -ftest-coverage)
    target_link_libraries(cmake_cpp_boilerplate_lib PUBLIC gcov)
endif()

add_executable(cmake_cpp_boilerplate_app "main.cpp")
target_link_libraries(cmake_cpp_boilerplate_app PRIVATE cmake_cpp_boilerplate::lib)
