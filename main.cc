#include "overload-set.h"

#include <cassert>
#include <cstddef>

struct A{};
struct B{};
struct C{};
struct D{};
struct E{};

int main()
{
	auto a = size_t{};
	auto c = size_t{};
	auto x = size_t{};

	auto fn = overload(
		[&a](A const&) { a++; },
		[]  (B const&) {},
		[&c](C const&) { c++; },
		[&x](auto const&) { x++; }
	);

	fn(A{});
	fn(B{});
	fn(C{});
	fn(D{});
	fn(E{});

	assert(a == 1);
	assert(c == 1);
	assert(x == 2);

	return 0;
}
