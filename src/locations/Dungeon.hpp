#pragma once

#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../Describable.hpp"
#include "Room.hpp"

class Dungeon : public Describable {
public:
  enum class MoveResult { Success, NoConnection, Locked };

  explicit Dungeon(Room start) : rootRoom(std::move(start)), currentRoom(&rootRoom){};
  ~Dungeon() override = default;

  [[nodiscard]] inline auto describe() const -> std::string override
  {
    return currentRoom->describe();
  }

  [[nodiscard]] inline auto getRoot() -> Room&
  {
    return rootRoom;
  };

  [[nodiscard]] inline auto getRooms() -> std::vector<Room>&
  {
    return rooms;
  };

  auto addRoom(const Room& room) -> bool;

  auto move(const std::string& direction) -> MoveResult;

private:
  Room rootRoom;
  const Room* currentRoom;
  std::vector<Room> rooms;
};
