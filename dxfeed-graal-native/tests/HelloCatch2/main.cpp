#include <catch.hpp>
#include <iostream>

TEST_CASE("Hello from Catch2", "[Catch2]") {
  std::cout << "Hello from Catch2" << std::endl;
  REQUIRE(true);
}
