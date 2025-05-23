
#include <array>
#include <cstdint>
#include <fmt/core.h>
#include <unordered_map>

// clang-format off
struct StatBlock {
  uint8_t strength;
  uint8_t dexterity;
  uint8_t constitution;
  uint8_t wisdom;
  uint8_t inteligence;
  uint8_t charisma;
  uint8_t luck;
  uint8_t other;
};

[[nodiscard]] inline auto describeStats(StatBlock stat) -> std::string {
  return fmt::format("Strength: {}, Dexterity: {}, Constitution: {}, Wisdom: {}, Intelligence: {}, Charisma: {}",
                     stat.strength, stat.dexterity, stat.constitution, stat.wisdom, stat.inteligence, stat.charisma);
}

constexpr const auto ModifiersMap = {
    -5, -5,
    -4, -4,
    -3, -3,
    -2, -2,
    -1, -1,
    0, 0,
    1, 1,
    2, 2,
    3, 3,
    4, 4,
    5, 5,
    6, 6,
    7, 7,
    8, 8,
    9, 9,
    10, 10
};
// clang-format on

constexpr const StatBlock commoner = {10, 10, 10, 10, 10, 10, 10, 10};
