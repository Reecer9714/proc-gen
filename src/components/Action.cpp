#include "Action.hpp"
#include "../LuaEngine.hpp"
#include <sol/load_result.hpp>

auto Action::from_json(const nlohmann::json& j) -> Action
{
  Action action{j.at("name").get<std::string>()};

  auto effectCode = j.at("effect").get<std::string>();
  auto functionWrap = "function(user, target) " + effectCode + " end";
  action.effect = LuaEngine::getInstance().getState().script(functionWrap);
  return action;
}