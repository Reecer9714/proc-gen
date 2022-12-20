#pragma once

#include <string>
#include <vector>

#include "../Describable.hpp"

class Location : public Describable {
public:
  struct Connection : public Describable {
    bool hidden = false;
    bool locked = false;
    Location* connectedLocation;

    explicit Connection(Location* toConnect) : connectedLocation(toConnect){};
    ~Connection() override = default;
  };

  ~Location() override = default;
  auto addConnection(Location* toConnect, bool hidden = false,
                     bool locked = false) -> Connection*;

  inline auto describe() const -> std::string override
  {
    return fmt::format("{}\n{}", Describable::describe(), describeExits());
  }

  inline auto describeExits() const -> std::string
  {
    return fmt::format("{}\n{}", Describable::describe(), );
  }

private:
  std::vector<Connection> exits;
};
