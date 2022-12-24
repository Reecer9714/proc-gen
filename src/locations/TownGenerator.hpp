#pragma once

#include "Location.hpp"
#include <memory>
#include <random>

class TownGenerator {
public:
  static auto generateTown(size_t size) -> Location
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(1, size - 1);

    // Create a town location
    Location rootLocation;
    rootLocation.setName("Town");
    rootLocation.setDescription("A bustling town filled with shops and people.");

    return rootLocation;
  }
};
