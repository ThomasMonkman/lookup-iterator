# lookup-iterator <a href="#"><img src="https://img.shields.io/badge/C++-11-blue.svg?style=flat-square"></a>

| Branch        | Status        |
| ------------- |:-------------:|
| **Master**    | [![Master](https://travis-ci.org/ThomasMonkman/lookup-iterator.svg?branch=master)](https://travis-ci.org/ThomasMonkman/lookup-iterator)|

A single header iterator that allows you to iterate one container with indexes from another.

### Install:
Drop [LookupIterator.hpp](https://github.com/ThomasMonkman/lookup-iterator/blob/master/LookupIterator.hpp) in to your include path and you should be good to go.
### Examples:

```c++
const std::vector<int> lookup_vector = { 0, 2 };
const std::vector<int> data = { 10, 20, 30 };
for (const auto& x : lookup(data, lookup_vector)) {
	std::cout << x << '\n';
}
```
will output
```
10
30
```

Data can be anything that specifies an `operator[]`, such as map
```c++
std::vector<char> lookup_vector = { 'b', 'c' };
std::map<char, int> data = { {'a', 10}, {'b', 20}, {'c', 30} };
for (const auto& x : lookup(data, lookup_vector)) {
	std::cout << x << '\n';
}
```
will output
```
20
30
```

`lookup` also defaults to a vector, such that initialisation lists can be used
```c++
const std::vector<int> data = { 10, 20, 30 };
for (const auto& x : lookup(data, { 0, 2 })) {
	std::cout << x << '\n';
}
```
will output
```
10
30
```

### Requirements
```c++
lookup(Src src, Lookup lookup)
```
* `Lookup` must be allow either `++` `--` operators
* `Src` must have an `operator[]`
