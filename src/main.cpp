#include <fmt/core.h>

#include "locations/LocationFactory.hpp"

auto main() -> int
{
  auto forest =
      LocationFactory::createLocation(LocationFactory::LocationType::FOREST);

  fmt::print("You begin in a {}", forest->describe());
}