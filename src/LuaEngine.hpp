#pragma once

#include <sol/sol.hpp>

class LuaEngine {
public:
  // Delete copy constructor and assignment operator
  LuaEngine(const LuaEngine&) = delete;
  auto operator=(const LuaEngine&) -> LuaEngine& = delete;

  // Access the singleton instance
  static auto getInstance() -> LuaEngine&
  {
    static LuaEngine instance;
    return instance;
  }

  // Access the sol::state
  auto getState() -> sol::state&
  {
    return luaState;
  }

private:
  // Private constructor
  LuaEngine()
  {
    // Initialize the Lua state
    luaState.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string);
  }

  // Private destructor
  ~LuaEngine() = default;

  sol::state luaState;
};
