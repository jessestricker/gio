#include <algorithm>
#include <array>
#include <gio/span.hpp>

#include "catch/catch.hpp"

TEST_CASE("span: construction and observers") {
  const auto data = std::array<int, 4>{1, 2, 3, 4};
  const auto span = gio::Span{data.begin(), data.end()};

  SECTION("constructor sets begin() and end()") {
    REQUIRE(span.begin() == data.begin());
    REQUIRE(span.end() == data.end());
  }

  SECTION("size() and empty() return correct values") {
    REQUIRE(span.size() == data.size());
    REQUIRE(span.empty() == data.empty());
  }

  SECTION("range-for compiles and works") {
    auto it = data.begin();
    for (const auto& item : span) {
      REQUIRE(item == *it);
      ++it;
    }
  }
}

TEST_CASE("span: empty storage yields empty span") {
  const auto data = std::array<int, 0>{};
  const auto span = gio::Span{data.begin(), data.end()};
  REQUIRE(span.size() == 0); // NOLINT(readability-container-size-empty)
  REQUIRE(span.empty());
}

TEST_CASE("span: items may be modified through non-const span") {
  auto data = std::array<int, 1>{1};
  const auto span = gio::Span{data.begin(), data.end()};
  const auto old = *span.begin();
  *span.begin() *= 2;
  REQUIRE(*span.begin() == 2 * old);
}

TEST_CASE("span: reverse() returns a new span with the order reversed") {
  const auto data = std::array<int, 4>{1, 2, 3, 4};
  const auto rev_data = std::array<int, 4>{4, 3, 2, 1};

  const auto span = gio::Span{data.begin(), data.end()};
  const auto rev_span = span.reverse();

  REQUIRE((std::equal(rev_span.begin(), rev_span.end(), rev_data.begin(), rev_data.end())));
}
