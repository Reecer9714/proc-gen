#include <fmt/format.h>

#include "locations/DungeonGenerator.hpp"

auto main() -> int
{
  auto dungeon = DungeonGenerator::generateDungeon(5);

  fmt::print("You begin in a {}", dungeon.describe());
}