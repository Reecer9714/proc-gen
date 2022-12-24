#include "Dungeon.hpp"

auto Dungeon::Room::addConnection(const std::string& direction, Room& toConnect, bool hidden, bool locked)
    -> Connection&
{
  toConnect.addOneWayConnection(direction, *this, hidden, locked);
  return addOneWayConnection(direction, toConnect, hidden, locked);
};

auto Dungeon::Room::addOneWayConnection(const std::string& direction, Room& toConnect, bool hidden, bool locked)
    -> Connection&
{
  auto [newConnection, success] = exits.try_emplace(direction, toConnect);
  newConnection->second.hidden = hidden;
  newConnection->second.locked = locked;
  return newConnection->second;
};

[[nodiscard]] auto Dungeon::Room::describeExits() const -> std::string
{
  std::ostringstream exitStream;
  exitStream << "Exits:\n";
  bool hasVisibleExits = false;
  for (const auto& [direction, connection] : exits) {
    if (!connection.hidden) {
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