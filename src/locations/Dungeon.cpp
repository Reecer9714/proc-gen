#include "Dungeon.hpp"
#include <algorithm>

auto Dungeon::addRoom(const Room& room) -> bool
{
  // Check if the room is already in the dungeon
  if (std::find(rooms.cbegin(), rooms.cend(), room) != rooms.cend()) { return false; }

  rooms.push_back(room);
  return true;
}

auto Dungeon::move(const std::string& direction) -> MoveResult
{
  // Check if there is a connection in the given direction
  auto exits = currentRoom->getExits();
  auto it = exits.find(direction);
  if (it == exits.end()) { return MoveResult::NoConnection; }

  // Check if the connection is locked
  if (it->second.isLocked()) { return MoveResult::Locked; }

  // Update the current room
  currentRoom = &it->second.getRoom();
  return MoveResult::Success;
}
