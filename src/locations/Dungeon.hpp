#pragma once

#pragma once

#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../Describable.hpp"

class Dungeon : public Describable {
public:
  struct Room : public Describable {
    struct Connection : public Describable {
      bool hidden = false;
      bool locked = false;
      Room& connectedRoom;

      explicit Connection(Room& toConnect) : connectedRoom(toConnect){};
      ~Connection() override = default;

      [[nodiscard]] inline auto describe() const -> std::string override
      {
        return connectedRoom.getName();
      }
    };

    auto addConnection(const std::string& direction, Room& toConnect, bool hidden = false, bool locked = false)
        -> Connection&;

    auto addOneWayConnection(const std::string& direction, Room& toConnect, bool hidden = false, bool locked = false)
        -> Connection&;

    [[nodiscard]] auto describeExits() const -> std::string;

    [[nodiscard]] inline auto describe() const -> std::string override
    {
      return fmt::format("{}\n{}", Describable::describe(), describeExits());
    }

  private:
    std::unordered_map<std::string, Connection> exits;
  };

  explicit Dungeon(Room start) : rootRoom(std::move(start)){};
  ~Dungeon() override = default;

  [[nodiscard]] inline auto describe() const -> std::string override
  {
    return rootRoom.describe();
  }

  [[nodiscard]] inline auto getRoot() -> Room&
  {
    return rootRoom;
  };

  [[nodiscard]] inline auto getRooms() const -> std::vector<Room>
  {
    return rooms;
  };

private:
  Room rootRoom;
  std::vector<Room> rooms;
};
