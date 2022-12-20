#pragma once

#include <fmt/core.h>
#include <string>

class Describable {
public:
  virtual ~Describable() = default;

  void setName(const std::string& name)
  {
    this->name = name;
  }
  void setDescription(const std::string& description)
  {
    this->description = description;
  }

  inline virtual auto describe() const -> std::string
  {
    return fmt::format("{}\n{}", name, description);
  };

private:
  std::string name;
  std::string description;
};