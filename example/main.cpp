#include <cassert>
#include <tl/expected.hpp>

int main() {
  tl::expected<int, int> e1 = 42;
  tl::expected<int, int> e2 = 17;
  tl::expected<int, int> e3 = 21;
  tl::expected<int, int> e4 = tl::make_unexpected(42);
  tl::expected<int, int> e5 = tl::make_unexpected(17);
  tl::expected<int, int> e6 = tl::make_unexpected(21);

  e1 = e2;
  assert(e1);
  assert(*e1 == 17);
  assert(e2);
  assert(*e2 == 17);

  e1 = std::move(e2);
  assert(e1);
  assert(*e1 == 17);
  assert(e2);
  assert(*e2 == 17);

  e1 = 42;
  assert(e1);
  assert(*e1 == 42);

  auto unex = tl::make_unexpected(12);
  e1 = unex;
  assert(!e1);
  assert(e1.error() == 12);

  e1 = tl::make_unexpected(42);
  assert(!e1);
  assert(e1.error() == 42);

  e1 = e3;
  assert(e1);
  assert(*e1 == 21);

  e4 = e5;
  assert(!e4);
  assert(e4.error() == 17);

  e4 = std::move(e6);
  assert(!e4);
  assert(e4.error() == 21);

  e4 = e1;
  assert(e4);
  assert(*e4 == 21);

  return 0;
}