#include "../components/Module.hpp"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include <fmt/core.h>

struct ModList {
  std::vector<ModuleInfo*> enabled;
  std::vector<ModuleInfo> available;
};

// Load and validate all modules
inline auto load_available_modules_list(const std::filesystem::path& root) -> ModList
{
  ModList modList;

  for (const auto& dir : std::filesystem::directory_iterator(root)) {
    if (!dir.is_directory()) continue;

    auto metaPath = dir.path() / "meta.json";
    if (!std::filesystem::exists(metaPath)) continue;

    std::ifstream in(metaPath);
    nlohmann::json j = nlohmann::json::parse(in, nullptr, false);
    if (j.is_discarded()) {
      fmt::print("Failed to parse meta for {}\n", metaPath.string());
      continue;
    }

    ModuleInfo mod(std::filesystem::relative(dir, std::filesystem::current_path()).string(), dir);
    mod.priority = j.value("load_priority", 0);
    mod.enabled = j.value("enabled", true);
    mod.dependencies = j.value("dependencies", std::vector<std::string>{});

    modList.available.push_back(std::move(mod));
    // If enabled, add a pointer to the enabledModules vector
    if (modList.available.back().enabled) { modList.enabled.push_back(&modList.available.back()); }
  }

  // Sort by priority
  std::sort(modList.enabled.begin(), modList.enabled.end(),
            [](const auto& a, const auto& b) { return a->priority < b->priority; });

  return modList;
}

inline auto load_module(const ModuleInfo& info) -> void
{
  (void)info; // Mark the parameter as intentionally unused
  // Call other loaders as needed
}