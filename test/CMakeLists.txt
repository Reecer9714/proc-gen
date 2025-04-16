set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(proc_gen_test TemplateParser.test.cpp)

find_package(Catch2 REQUIRED)
target_link_libraries(proc_gen_test proc_gen::lib Catch2::Catch2WithMain)
target_include_directories(proc_gen_test PUBLIC "${PROJECT_SOURCE_DIR}/src")

CMAKE_DEPENDENT_OPTION(BP_BUILD_TESTS_COVERAGE
        "Build the project with code coverage support for tests" OFF
        "BP_BUILD_TESTS" OFF)
if (${BP_BUILD_TESTS_COVERAGE})
    include("../cmake/CodeCoverage.cmake")
    APPEND_COVERAGE_COMPILER_FLAGS("-g -O0 -fprofile-arcs -ftest-coverage")
    set(COVERAGE_LCOV_EXCLUDES '/usr/*' '*/.conan/*' '*/test/*' 'test/*')
    SETUP_TARGET_FOR_COVERAGE_LCOV(
            NAME proc_gen_coverage                    # New target name
            EXECUTABLE proc_gen_test
            DEPENDENCIES proc_gen_test  # Dependencies to build first
    )
endif ()

enable_testing()

add_test(NAME proc_gen_test COMMAND "${CMAKE_BINARY_DIR}/bin/proc_gen_test")
