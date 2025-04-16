#pragma once

#include "../Describable.hpp"
#include <nlohmann/json.hpp>
#include <sol/sol.hpp>
#include <sol/types.hpp>
#include <string>

struct Action : public Describable {
  sol::function effect = sol::lua_nil_t{}; // Placeholder for actual function type

  explicit Action(std::string name) : Describable(std::move(name)) {}

  auto from_json(const nlohmann::json& j) -> Action;
};
