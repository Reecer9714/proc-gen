#include <fmt/format.h>
#include <iostream>

#include "CommandParser.hpp"
#include "locations/DungeonGenerator.hpp"

auto main() -> int
{
  auto running = true;
  auto dungeon = DungeonGenerator::generateDungeon(DungeonGenerator::SmallSize);

  CommandParser parser;
  // GameState state; //Captured by commands that require mutating state

  // Register some commands and their corresponding handler functions
  parser.registerCommand({"go", "move"}, [&dungeon](const std::vector<std::string>& args) {
    auto result = dungeon.move(args[0]);
    switch (result) {
    case Dungeon::MoveResult::Success:
      fmt::print("Going to {}\n{}", args[0], dungeon.describe());
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
    if (args.empty()) {
      fmt::print("{}\n", dungeon.describe());
    } else {
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