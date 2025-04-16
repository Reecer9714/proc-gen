#include <filesystem>
#include <fmt/format.h>
#include <iostream>

#include "CommandParser.hpp"
#include "loaders/ModuleLoader.hpp"
#include "locations/DungeonGenerator.hpp"

auto main() -> int
{
  // Load Modules
  auto modules = load_available_modules_list(std::filesystem::current_path() / "data");
  // Print loaded modules
  for (const auto& module : modules.available) {
    fmt::print("Available module: {}\n", module.id);
    fmt::print("Path: {}\n", module.path.string());
    fmt::print("Priority: {}\n", module.priority);
    fmt::print("Enabled: {}\n", module.enabled ? "true" : "false");
    fmt::print("Dependencies: {}\n", fmt::join(module.dependencies, ", "));
  }
  fmt::print("Available {} modules\n", modules.available.size());

  // Load the enabled modules
  for (const auto& module : modules.enabled) {
    fmt::print("Loading module: {}\n", module->id);
    load_module(*module);
  }

  auto running = true;
  auto dungeon = DungeonGenerator::generateDungeon(DungeonGenerator::SmallSize);

  CommandParser parser;
  // GameState state; //Captured by commands that require mutating state

  // Register some commands and their corresponding handler functions
  parser.registerCommand({"go", "move"}, [&dungeon](const std::vector<std::string>& args) {
    auto result = dungeon.move(args[0]);
    switch (result) {
    case Dungeon::MoveResult::Success:
      fmt::print("Going to {}\n You are now in {}", args[0], dungeon.describe());
      break;
    case Dungeon::MoveResult::NoConnection:
      fmt::print("There is nothing to {}\n", args[0]);
      break;
    case Dungeon::MoveResult::Locked:
      fmt::print("Can't get through. Its locked.\n");
      break;
    }
  });
  parser.registerCommand({"look"}, [dungeon](const std::vector<std::string>& args) {
    if (args.empty()) { fmt::print("{}\n", dungeon.describe()); }
    else {
      fmt::print("Looking at {}\n", args[0]);
    }
  });
  parser.registerCommand({"exit", "stop"}, [&running](const std::vector<std::string>& args) {
    fmt::print("Goodbye!", args[0]);
    running = false;
  });

  // Read and parse commands from the user
  fmt::print("You begin in a {}", dungeon.describe());
  while (running) {
    std::string input;
    std::getline(std::cin, input);
    parser.parseAndExecute(input);
  }
}