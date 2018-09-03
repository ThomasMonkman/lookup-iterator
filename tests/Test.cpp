#include "catch/catch.hpp"

#include "../LookupIterator.hpp"

#include "Util/TestHelper.hpp"

#include <vector>

TEST_CASE("vector", "[vector]") {

	SECTION("none const vectors") {
		std::vector<int> lookup_vector = { 0, 2 };
		std::vector<int> data = { 10, 20, 30 };
		auto a = lookup(data, lookup_vector).begin();
		REQUIRE(*a == 10);
		a++;
		REQUIRE(*a == 30);
	}
	SECTION("const lookup") {
		const std::vector<int> lookup_vector = { 0, 2 };
		std::vector<int> data = { 10, 20, 30 };
		auto a = lookup(data, lookup_vector).begin();
		REQUIRE(*a == 10);
		a++;
		REQUIRE(*a == 30);
	}
	SECTION("const vectors") {
		const std::vector<int> lookup_vector = { 0, 2 };
		const std::vector<int> data = { 10, 20, 30 };
		auto a = lookup(data, lookup_vector).begin();
		REQUIRE(*a == 10);
		a++;
		REQUIRE(*a == 30);
	}
	SECTION("range-for") {
		const std::vector<int> lookup_vector = { 0, 2 };
		const std::vector<int> data = { 10, 20, 30 };
		auto counter = 0;
		for (const auto& x : lookup(data, lookup_vector)) {
			REQUIRE(x == data[lookup_vector[counter]]);
			counter++;
		}
		REQUIRE(counter == 2);
	}
	SECTION("end") {
		const std::vector<int> lookup_vector = { 0, 2 };
		const std::vector<int> data = { 10, 20, 30 };
		auto a = lookup(data, lookup_vector).begin();
		a++;
		a++;
		REQUIRE(a == lookup(data, lookup_vector).end());
	}
	SECTION("r value") {
		//const std::vector<int> data = { 10, 20, 30 };
		const std::vector<char> data = { 'a', 'b', 'c' };
		auto a = lookup(data, std::vector<int>(0, 2)).begin();
		REQUIRE(*a == 10);
		a++;
		REQUIRE(*a == 30);
	}
	SECTION("static") {
		static const std::vector<int> lookup_vector = { 0, 2 };
		static const std::vector<int> data = { 10, 20, 30 };
		auto a = lookup(data, lookup_vector).begin();
		REQUIRE(*a == 10);
		a++;
		REQUIRE(*a == 30);
	}
	SECTION("mutate") {
		const std::vector<int> lookup_vector = { 0, 2 };
		std::vector<int> data = { 10, 20, 30 };
		auto a = lookup(data, lookup_vector).begin();
		REQUIRE(*a == 10);
		(*a) = 5;
		REQUIRE(*a == 5);
		REQUIRE(data[0] == 5);
		a++;
		REQUIRE(*a == 30);
		(*a) += 5;
		REQUIRE(*a == 35);
		REQUIRE(data[2] == 35);
	}

}
