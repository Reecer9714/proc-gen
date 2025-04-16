#pragma once

#include "../Describable.hpp"
#include "Class.hpp"
#include "Level.hpp"
#include "StatBlock.hpp"
#include <memory>
#include <sstream>
#include <string>
#include <utility>

class Character : public Describable {
private:
  Level level;
  StatBlock stats;
  const std::shared_ptr<Class> characterClass;

public:
  explicit Character(std::string name, Level lvl, StatBlock statBlock, std::shared_ptr<Class> cls)
      : Describable(std::move(name)), level(std::move(lvl)), stats(statBlock), characterClass(std::move(cls))
  {
  }

  [[nodiscard]] auto describe() const -> std::string override
  {
    return fmt::format("Character: {}\nLevel: {} ({}/{})\nClass: {}\nStats: \n{}\n", getName(), level.getLevel(),
                       level.getExperience(), level.getExperienceForLevel(), characterClass->name,
                       describeStats(stats));
  }
};

class CharacterBuilder {
private:
  std::string name;
  Level level;
  StatBlock stats;
  std::shared_ptr<Class> characterClass{};

public:
  explicit CharacterBuilder(std::string name, int lvl = 1) : name(std::move(name)), level(lvl), stats(commoner) {}
  auto setClass(const std::shared_ptr<Class>& className) -> CharacterBuilder&
  {
    characterClass = className;
    return *this;
  }
  auto setStatBlock(const StatBlock& _stats) -> CharacterBuilder&
  {
    this->stats = _stats;
    return *this;
  }
  auto build() -> Character
  {
    return Character(name, level, stats, characterClass);
  }
};