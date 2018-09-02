# lookup-iterator <a href="#"><img src="https://img.shields.io/badge/C++-11-blue.svg?style=flat-square"></a>

| Branch        | Status        |
| ------------- |:-------------:|
| **Master**    | [![Master](https://travis-ci.org/ThomasMonkman/lookup-iterator.svg?branch=master)](https://travis-ci.org/ThomasMonkman/lookup-iterator)|


# lookup-iterator
Iterate one container with indexes from another


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