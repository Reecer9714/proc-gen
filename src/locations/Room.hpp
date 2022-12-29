#pragma once

#include "../Describable.hpp"
#include "Connection.hpp"
#include <unordered_set>

struct Room : public Describable {

  auto addConnection(const std::string& direction, Room& toConnect, bool hidden = false, bool locked = false)
      -> const Connection&;

  auto addOneWayConnection(const std::string& direction, Room& toConnect, bool hidden = false, bool locked = false)
      -> const Connection&;

  [[nodiscard]] auto describeExits() const -> std::string;
  [[nodiscard]] auto describe() const -> std::string override;
  [[nodiscard]] auto getExits() const -> const std::unordered_map<std::string, Connection&>&;

  auto operator==(const Room& rhs) const -> bool;

private:
  std::unordered_map<std::string, Connection&> exits;
  std::unordered_set<Connection, Connection::ConnectionHash> connections;
};
