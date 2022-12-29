#pragma once

#include "../Describable.hpp"

struct Room;

class Connection : public Describable {
public:
  explicit Connection(std::string name, Room& toConnect, bool locked = false, bool hidden = false)
      : Describable(std::move(name)), connectedRoom(&toConnect), hidden_(hidden), locked_(locked){};
  ~Connection() override = default;

  [[nodiscard]] auto describe() const -> std::string override;
  [[nodiscard]] auto isHidden() const -> bool;
  [[nodiscard]] auto isLocked() const -> bool;
  [[nodiscard]] auto getRoom() const -> const Room&;

  auto operator==(const Connection& rhs) const -> bool;

  struct ConnectionHash;

private:
  Room* connectedRoom;
  bool hidden_ = false;
  bool locked_ = false;
};

struct Connection::ConnectionHash {
  static constexpr auto HASH_OFFSET = 0x9e3779b9;
  auto operator()(const Connection& connection) const -> std::size_t
  {
    std::size_t seed = 0;
    seed ^= std::hash<Room*>()(connection.connectedRoom) + HASH_OFFSET + (seed << 6) + (seed >> 2);
    seed ^= std::hash<bool>()(connection.hidden_) + HASH_OFFSET + (seed << 6) + (seed >> 2);
    seed ^= std::hash<bool>()(connection.locked_) + HASH_OFFSET + (seed << 6) + (seed >> 2);
    return seed;
  }
};