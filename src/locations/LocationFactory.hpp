#pragma once

#include "Location.hpp"
#include "TownGenerator.hpp"
#include <memory>

class LocationFactory {
public:
  enum LocationType { DUNGEON, TOWN, FOREST, CAVERN };

  static auto createLocation(LocationType type) -> std::unique_ptr<Location>
  {
    switch (type) {
    case DUNGEON:
      return createDungeon();
    case TOWN:
      return createTown();
    case FOREST:
      return createForest();
    case CAVERN:
      return createCavern();
    default:
      return nullptr;
    }
  }

private:
  static auto createDungeon() -> std::unique_ptr<Location>
  {
    // Create a dungeon location
    auto location = std::make_unique<Location>();
    location->setName("Dungeon");
    location->setDescription("A dark and dangerous underground labyrinth.");
    // Add connections and other characteristics specific to a dungeon location
    return location;
  }

  static auto createTown() -> std::unique_ptr<Location>
  {
    // Generate a town location using the TownGenerator
    return std::make_unique<Location>(TownGenerator::generateTown());
  }

  static auto createForest() -> std::unique_ptr<Location>
  {
    // Create a forest location
    auto location = std::make_unique<Location>();
    location->setName("Forest");
    location->setDescription("A dense forest filled with tall trees and a "
                             "variety of plants and animals.");
    // Add connections and other characteristics specific to a forest location
    return location;
  }

  static auto createCavern() -> std::unique_ptr<Location>
  {
    // Create a forest location
    auto location = std::make_unique<Location>();
    location->setName("Cavern");
    location->setDescription("A large cavern smelling of damp, stale air.");
    // Add connections and other characteristics specific to a cavern location
    return location;
  }
};
