
#include <string>
#include <utility>
#include <vector>

struct Class {
  std::string name;
  std::vector<std::string> methods;
  std::vector<std::string> attributes;

  explicit Class(std::string className) : name(std::move(className)) {}

  void addMethod(const std::string& methodName)
  {
    methods.push_back(methodName);
  }

  void addAttribute(const std::string& attributeName)
  {
    attributes.push_back(attributeName);
  }
};