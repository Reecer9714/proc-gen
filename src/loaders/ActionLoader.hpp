#pragma once

#include "../components/Action.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

class ActionLoader {
public:
  static auto loadActions(const std::string& directoryPath) -> std::vector<Action>;

private:
  static auto loadJsonFromFile(const std::string& filePath) -> nlohmann::json;
};
