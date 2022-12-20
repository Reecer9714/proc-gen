#pragma once

#include <fmt/format.h>
#include <string>

class Describable {
public:
  virtual ~Describable() = default;

  void setName(const std::string& new_name)
  {
    this->name = new_name;
  }
  void setDescription(const std::string& new_description)
  {
    this->description = new_description;
  }

  [[nodiscard]] inline virtual auto describe() const -> std::string
  {
    return fmt::format("{}\n{}", name, description);
  };

private:
  std::string name;
  std::string description;
};