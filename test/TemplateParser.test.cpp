#include <catch2/catch_test_macros.hpp>

#include <TemplateParser.hpp>
#include <random>

TEST_CASE("TemplateParser", "[TemplateParser]")
{
  TemplateParser parser;
  std::mt19937 rng(std::random_device{}());

  SECTION("No placeholders in the template")
  {
    auto output = parser.format("No placeholders in this text", rng);

    REQUIRE(output == "No placeholders in this text");
  }

  SECTION("No placeholder match in parser")
  {
    auto output = parser.format("This _placeholder_ is not added", rng);

    REQUIRE(output == "This placeholder is not added");
  }

  parser.addPlaceholder("placeholder", RandomPickList<std::string>{{{"holder"}}});
  SECTION("Placeholder match and replace")
  {
    auto output = parser.format("This _placeholder_ is added", rng);

    REQUIRE(output == "This holder is added");
  }

  SECTION("Placeholder match multiple and replace")
  {
    auto output = parser.format("This _placeholder_ is added multiple times _placeholder_", rng);

    REQUIRE(output == "This holder is added multiple times holder");
  }

  parser.addPlaceholder("otherholder", RandomPickList<std::string>{{{"other"}}});
  SECTION("Multiple placeholders match and replace")
  {
    auto output = parser.format("This _placeholder_ is added and this as well _otherholder_", rng);

    REQUIRE(output == "This holder is added and this as well other");
  }

  parser.addPlaceholder("nestedholder", RandomPickList<std::string>{{{"_otherholder_"}}});
  SECTION("Nested placeholder match and replace")
  {
    auto output = parser.format("This _nestedholder_ will give other", rng);

    REQUIRE(output == "This other will give other");
  }
}