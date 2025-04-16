#include "TemplateParser.hpp"
#include <iostream>
#include <random>

void TemplateParser::addPlaceholder(const std::string& name, RandomPickList<std::string>&& values)
{
  placeholders_.try_emplace(name, values);
}
