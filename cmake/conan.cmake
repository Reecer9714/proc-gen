macro(run_conan)
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan_provider.cmake")
        message(STATUS "Downloading conan_provider.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://https://raw.githubusercontent.com/conan-io/cmake-conan/refs/heads/develop2/conan_provider.cmake"
                "${CMAKE_BINARY_DIR}/conan_provider.cmake")
    endif()

    include(${CMAKE_BINARY_DIR}/conan_provider.cmake)
endmacro()