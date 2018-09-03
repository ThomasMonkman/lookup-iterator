#include "catch/catch.hpp"

#include "../LookupIterator.hpp"

#include "Util/TestHelper.hpp"

#include <vector>
#include <map>
#include <list>

TEST_CASE("vector", "[vector]") {

	SECTION("none const vectors") {
		std::vector<int> lookup_vector = { 0, 2 };
		std::vector<int> data = { 10, 20, 30 };
		auto a = lookup(data, lookup_vector).begin();
		REQUIRE(*a == 10);
		a++;
		REQUIRE(*a == 30);
	}
	SECTION("bidirectional") {
		std::vector<int> lookup_vector = { 0, 2 };
		std::vector<int> data = { 10, 20, 30 };
		auto a = lookup(data, lookup_vector).begin();
		REQUIRE(*a == 10);
		a++;
		REQUIRE(*a == 30);
		a--;
		REQUIRE(*a == 10);
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
		const std::vector<int> data = { 10, 20, 30 };
		auto a = lookup(data, std::vector<int>{0, 2}).begin();
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
TEST_CASE("map", "[map]") {

	SECTION("none const vectors") {
		std::vector<char> lookup_vector = { 'b', 'c' };
		std::map<char, int> data = { {'a', 10}, {'b', 20}, {'c', 30} };
		auto a = lookup(data, lookup_vector).begin();
		REQUIRE(*a == 20);
		a++;
		REQUIRE(*a == 30);
	}
}

#include <forward_list>

TEST_CASE("lookup list", "[lookup]") {

	SECTION("none const vectors") {
		std::list<char> lookup_vector = { 'b', 'c' };
		std::map<char, int> data = { {'a', 10}, {'b', 20}, {'c', 30} };
		auto a = lookup(data, lookup_vector).begin();
		REQUIRE(*a == 20);
		a++;
		REQUIRE(*a == 30);
	}
}
