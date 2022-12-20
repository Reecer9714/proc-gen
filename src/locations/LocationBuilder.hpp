#pragma once

#include "Location.hpp"

class LocationBuilder {
public:
  auto setName(const std::string& name) -> LocationBuilder&
  {
    location.setName(name);
    return *this;
  }

  auto setDescription(const std::string& description) -> LocationBuilder&
  {
    location.setDescription(description);
    return *this;
  }

  auto addConnection(Location* toConnect, bool hidden = false,
                     bool locked = false) -> LocationBuilder&
  {
    location.addConnection(toConnect, hidden, locked);
    return *this;
  }

  auto build() -> Location
  {
    return location;
  }

private:
  Location location{};
};