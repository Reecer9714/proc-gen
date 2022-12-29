#include "Room.hpp"
#include <sstream>
#include <string>

auto Room::addConnection(const std::string& direction, Room& toConnect, bool hidden, bool locked) -> void
{
  toConnect.addOneWayConnection(direction, *this, hidden, locked);
  addOneWayConnection(direction, toConnect, hidden, locked);
}

auto Room::addOneWayConnection(const std::string& direction, Room& toConnect, bool hidden, bool locked) -> void
{
  auto newConnection = Connection{direction, toConnect, locked, hidden};
  auto it = std::find_if(connections.cbegin(), connections.cend(),
                         [newConnection](const Connection& ptr) { return newConnection.getName() == ptr.getName(); });
  if (it != connections.cend()) return;   // Don't allow duplicate connections
  if (exits.count(direction) > 0) return; // Don't allow overwriting an existing exit
  auto [connected, _] = connections.emplace(newConnection);
  exits.insert_or_assign(direction, &(*connected));
}

[[nodiscard]] auto Room::describeExits() const -> std::string
{
  std::ostringstream exitStream;
  exitStream << "Exits:\n";
  bool hasVisibleExits = false;
  for (const auto& [direction, connection] : exits) {
    if (!connection->isHidden()) {
      exitStream << fmt::format("\t{}: {}, \n", direction, connection->describe());
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

[[nodiscard]] auto Room::getExits() const -> const std::unordered_map<std::string, const Connection*>&
{
  return exits;
}

auto Room::operator==(const Room& rhs) const -> bool
{
  return this->getName() == rhs.getName() && this->getDescription() == rhs.getDescription() &&
         this->connections == rhs.connections && this->exits == rhs.exits;
}
