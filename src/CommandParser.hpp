#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

// A command handler function takes a vector of strings as arguments and returns void
using CommandHandler = std::function<void(std::vector<std::string>)>;
;

class CommandParser {
public:
  void registerCommand(const std::vector<std::string>& keywords, const CommandHandler& handler) noexcept;
  void parseAndExecute(const std::string& input);

private:
  void executeCommand(const std::string& command, const std::vector<std::string>& args) noexcept;
  std::unordered_map<std::string, CommandHandler> commands;
};