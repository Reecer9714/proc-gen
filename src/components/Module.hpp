#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

struct ModuleInfo {
  std::string id;
  std::filesystem::path path;
  int priority = 0;
  bool enabled = true;
  std::vector<std::string> dependencies;
  std::unordered_map<std::string, std::string> meta;

  explicit ModuleInfo(std::string _id, std::filesystem::path _path) : id(std::move(_id)), path(std::move(_path)) {}
};
