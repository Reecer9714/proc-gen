#include <functional>
#include <utility>

const constexpr int DEFAULT_EXP_TO_NEXT_LEVEL = 100;
const constexpr int DEFAULT_MAX_LEVEL = 20;

class Level {
private:
  int level;
  int maxLevel = DEFAULT_MAX_LEVEL; // Maximum level
  int experience = 0;
  int experienceToNextLevel;
  std::function<void(int)> onLevelUp; // Callback for level-up notifications

  void levelUp()
  {
    level++;
    experienceToNextLevel = getExperienceForLevel();
    if (onLevelUp) { onLevelUp(level); } // Notify external listener
  }

public:
  explicit Level(int lvl = 1, std::function<void(int)> callback = nullptr)
      : level(lvl), experienceToNextLevel(getExperienceToNextLevel()), onLevelUp(std::move(callback))
  {
  }

  void gainExperience(int exp)
  {
    if (level >= maxLevel) { return; } // No more levels to gain
    if (exp <= 0) { return; }          // No negative experience

    experience += exp;
    while (experience >= experienceToNextLevel) { levelUp(); }
  }

  [[nodiscard]] auto getLevel() const -> int
  {
    return level;
  }
  [[nodiscard]] auto getExperience() const -> int
  {
    return experience;
  }
  [[nodiscard]] auto getExperienceToNextLevel() const -> int
  {
    return experienceToNextLevel;
  }
  [[nodiscard]] auto getExperienceForLevel() const -> int
  {
    return DEFAULT_EXP_TO_NEXT_LEVEL * level;
  }
};
;