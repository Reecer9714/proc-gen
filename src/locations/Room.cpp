#include "Room.hpp"
#include <sstream>
#include <string>

auto Room::addConnection(const std::string& direction, Room& toConnect, bool hidden, bool locked) -> const Connection&
{
  toConnect.addOneWayConnection(direction, *this, hidden, locked);
  return addOneWayConnection(direction, toConnect, hidden, locked);
}

auto Room::addOneWayConnection(const std::string& direction, Room& toConnect, bool hidden, bool locked)
    -> const Connection&
{
  auto newConnection = Connection{toConnect, locked, hidden};
  auto it = std::find_if(connections.cbegin(), connections.cend(),
                         [newConnection](const Connection& ptr) { return newConnection == ptr; });
  if (it != connections.cend()) return *it;
  auto [connection, _] = exits.emplace(direction, newConnection);
  return connection->second;
}

[[nodiscard]] auto Room::describeExits() const -> std::string
{
  std::ostringstream exitStream;
  exitStream << "Exits:\n";
  bool hasVisibleExits = false;
  for (const auto& [direction, connection] : exits) {
    if (!connection.isHidden()) {
      exitStream << '\t' << direction << ": " << connection.describe() << ", \n";
      hasVisibleExits = true;
    }
  }
  if (hasVisibleExits) {
    [[likely]]
    // Remove the final ", " from the string
    exitStream.seekp(-3, std::ios_base::end);
    exitStream << "";
  } else {
    exitStream.str("");
    exitStream << "There are no visible exits.";
  }
  return exitStream.str();
}

[[nodiscard]] auto Room::describe() const -> std::string
{
  return fmt::format("{}\n{}", Describable::describe(), describeExits());
}

[[nodiscard]] auto Room::getExits() const -> const std::unordered_map<std::string, Connection&>&
{
  return exits;
}

auto Room::operator==(const Room& rhs) const -> bool
{
  return this->name == rhs.name && this->description == rhs.description && this->connections == rhs.connections &&
         this->exits == rhs.exits;
}
