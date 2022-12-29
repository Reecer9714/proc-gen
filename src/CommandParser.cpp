#include "CommandParser.hpp"

#include <algorithm>
#include <fmt/core.h>
#include <sstream>
#include <stdexcept>

auto toLowerCase(std::string s) noexcept -> std::string
{
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
  return s;
}

void CommandParser::registerCommand(const std::vector<std::string>& keywords, const CommandHandler& handler) noexcept
{
  for (const auto& keyword : keywords) {
    auto lowerCaseKeyword = toLowerCase(keyword);
    commands[lowerCaseKeyword] = handler;
  }
}

auto getCommand(const std::string& input) -> std::string
{
  std::string command;
  std::istringstream iss(input);
  iss >> command;
  return toLowerCase(command);
}

auto getArgs(const std::string& input) -> std::vector<std::string>
{
  std::istringstream iss(input);
  std::string word;
  std::vector<std::string> words;
  while (iss >> word) { words.push_back(word); }
  return {words.begin() + 1, words.end()};
}

auto filterFillerWords(const std::vector<std::string>& words) -> std::vector<std::string>
{
  auto fillerWords = {"the", "a", "an", "to"};
  std::vector<std::string> filteredWords;
  for (const auto& w : words) {
    if (std::find(fillerWords.begin(), fillerWords.end(), toLowerCase(w)) == fillerWords.end()) {
      filteredWords.push_back(w);
    }
  }
  return filteredWords;
}

void CommandParser::parseAndExecute(const std::string& input)
{
  auto command = getCommand(input);
  auto args = getArgs(input);
  args = filterFillerWords(args);
  executeCommand(command, args);
}

void CommandParser::executeCommand(const std::string& command, const std::vector<std::string>& args) noexcept
{
  auto it = commands.find(command);
  if (it != commands.end()) {
    it->second(args);
  } else {
    fmt::print("Unknown Command: {}", command);
  }
}
