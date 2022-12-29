#include "Connection.hpp"
#include "Room.hpp"

[[nodiscard]] auto Connection::describe() const -> std::string
{
  return connectedRoom->getName();
}

[[nodiscard]] auto Connection::isHidden() const -> bool
{
  return hidden_;
}

[[nodiscard]] auto Connection::isLocked() const -> bool
{
  return locked_;
}

[[nodiscard]] auto Connection::getRoom() const -> const Room&
{
  return *connectedRoom;
}

auto Connection::operator==(const Connection& rhs) const -> bool
{
  return this->getName() == rhs.getName() && this->connectedRoom == rhs.connectedRoom && this->hidden_ == rhs.hidden_ &&
         this->locked_ == rhs.locked_;
}
