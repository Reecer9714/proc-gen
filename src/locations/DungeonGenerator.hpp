#pragma once

#include "Dungeon.hpp"
#include <memory>
#include <random>

class DungeonGenerator {
public:
  static auto generateDungeon(size_t size) -> Dungeon
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(1, size - 1);

    // Create a dungeon location
    Dungeon::Room rootLocation;
    rootLocation.setName("Dungeon");
    rootLocation.setDescription("A bustling dungeon filled with shops and people.");
    Dungeon dungeon(rootLocation);

    // Generate additional locations
    auto dungeonRooms = dungeon.getRooms();
    for (auto i = 0U; i < size; ++i) {
      auto& room = dungeonRooms.emplace_back();
      room.setName("Location " + std::to_string(i + 1));
    }

    // Add random connections between the locations
    for (auto& room : dungeonRooms) {
      auto numConnections = dis(gen);
      for (auto i = 0U; i < numConnections; ++i) {
        auto& connectedLocation = dungeonRooms[dis(gen)];
        room.addConnection("direction" + std::to_string(i), connectedLocation);
      }
    }

    // Ensure that at least one location connects to the root location
    dungeon.getRoot().addConnection("entrance", dungeonRooms[0]);

    return dungeon;
  }
};
