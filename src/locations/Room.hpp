#pragma once

#include "../Describable.hpp"
#include "Connection.hpp"
#include <unordered_set>

struct Room : public Describable {

  explicit Room(const std::string& name) : Describable(name){};

  auto addConnection(const std::string& direction, Room& toConnect, bool hidden = false, bool locked = false) -> void;

  auto addOneWayConnection(const std::string& direction, Room& toConnect, bool hidden = false, bool locked = false)
      -> void;

  [[nodiscard]] auto describeExits() const -> std::string;
  [[nodiscard]] auto describe() const -> std::string override;
  [[nodiscard]] auto getExits() const -> const std::unordered_map<std::string, const Connection*>&;

  auto operator==(const Room& rhs) const -> bool;

private:
  std::unordered_map<std::string, const Connection*> exits;
  std::unordered_set<Connection, Connection::ConnectionHash> connections;
};
