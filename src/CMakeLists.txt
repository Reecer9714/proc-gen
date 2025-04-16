find_package(fmt REQUIRED)
find_package(sol2 REQUIRED)
find_package(nlohmann_json REQUIRED)

add_library(proc_gen_lib
    CommandParser.cpp
    CommandParser.hpp
    RandomPickList.hpp
    TemplateParser.cpp
    TemplateParser.hpp
    Describable.hpp
    LuaEngine.hpp
    locations/Connection.cpp
    locations/Connection.hpp
    locations/Dungeon.cpp
    locations/Dungeon.hpp
    locations/DungeonGenerator.hpp
    locations/Room.cpp
    locations/Room.hpp
    components/Action.hpp
    components/Character.hpp
    components/Class.hpp
    components/Level.hpp
    components/Module.hpp
    components/StatBlock.hpp
    loaders/ActionLoader.hpp
    loaders/ModuleLoader.hpp
    )
set_target_properties(proc_gen_lib PROPERTIES LINKER_LANGUAGE CXX)

add_library(proc_gen::lib ALIAS proc_gen_lib)
target_link_libraries(proc_gen_lib
        PUBLIC cmake_cpp_boilerplate::compiler_options fmt::fmt-header-only sol2::sol2 nlohmann_json::nlohmann_json)
target_include_directories(proc_gen_lib PUBLIC "${PROJECT_SOURCE_DIR}/include")

if(${BP_BUILD_TESTS_COVERAGE})
    target_compile_options(proc_gen_lib PUBLIC -fprofile-arcs -ftest-coverage)
    target_link_libraries(proc_gen_lib PUBLIC gcov)
endif()

add_executable(proc_gen_app "main.cpp")
target_link_libraries(proc_gen_app PRIVATE proc_gen::lib)
