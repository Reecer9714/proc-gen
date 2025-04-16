#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "RandomPickList.hpp"

class TemplateParser {
public:
  TemplateParser() = default;

  void addPlaceholder(const std::string& name, RandomPickList<std::string>&& values);

  template <typename RNG>
  auto format(const std::string& templateString, RNG rng) -> std::string
  {
    std::unordered_map<std::string, std::string> vars;

    auto result = templateString;
    static const std::regex placeholderMatcher("_([a-zA-Z0-9_-]+)_");
    std::smatch match;
    while (std::regex_search(result, match, placeholderMatcher)) {
      std::string replacement = match[1];
      auto values = placeholders_.find(replacement);
      if (values != placeholders_.end()) { replacement = values->second.PickRandom(rng); }
      result = std::regex_replace(result, std::regex(match.str()), replacement,
                                  std::regex_constants::format_first_only);
    }
    return result;
  }

private:
  std::unordered_map<std::string, RandomPickList<std::string>> placeholders_;
};
