#pragma once

#include <fmt/format.h>
#include <string>
#include <utility>

class Describable {
public:
  virtual ~Describable() = default;

  explicit Describable(std::string name) : name_(std::move(name)){};

  void setDescription(const std::string& description)
  {
    this->description_ = description;
  }

  [[nodiscard]] inline auto getName() const -> std::string
  {
    return this->name_;
  }

  [[nodiscard]] auto getDescription() const -> const std::string&
  {
    return description_;
  }

  [[nodiscard]] inline virtual auto describe() const -> std::string
  {
    return fmt::format("{}\n{}", this->name_, this->description_);
  }

private:
  std::string name_;
  std::string description_;
};