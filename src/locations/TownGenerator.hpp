#pragma once

#include "Location.hpp"

class TownGenerator {
public:
  static auto generateTown() -> Location
  {
    // Create a town location
    Location location;
    location.setName("Town");
    location.setDescription("A bustling town filled with shops and people.");
    // Add connections and other characteristics specific to a town location
    return location;
  }
};
