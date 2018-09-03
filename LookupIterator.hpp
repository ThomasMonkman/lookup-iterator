// MIT License
// 
// Copyright(c) 2018 Thomas Monkman
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef LOOKUPITERATOR_HPP
#define LOOKUPITERATOR_HPP

#include <iterator>
#include <type_traits>

template<class Src, class Lookup>
struct lookup_itr {
private:
	typedef decltype(begin(std::declval<Src>())) src_itr_t;
	typedef decltype(*begin(std::declval<Src>())) src_itr_value;
	typedef decltype(begin(std::declval<Lookup>())) lookup_itr_t;

	Src _src;
	Lookup _lookup;
	lookup_itr_t _lookup_itr;
public:
	static_assert(std::is_same<typename src_itr_t::iterator_category, std::random_access_iterator_tag>::value, "Src must allow random access interation");

	using value_type = typename src_itr_t::value_type;
	using difference_type = typename lookup_itr_t::difference_type;
	using pointer = typename src_itr_t::pointer;
	using reference = typename src_itr_t::reference;
	using iterator_category = typename lookup_itr_t::iterator_category;

	struct End {};

	lookup_itr(Src&& src, Lookup&& lookup) : _src(src), _lookup(lookup) {
		using std::begin;
		_lookup_itr = begin(_lookup);
	}
	lookup_itr(Src&& src, Lookup&& lookup, End) : _src(src), _lookup(lookup) {
		using std::end;
		_lookup_itr = end(_lookup);
	}
	lookup_itr operator++(int) /* postfix */ {
		auto temp(*this);
		++_lookup_itr;
		return temp;
	}
	lookup_itr& operator++()    /* prefix */ {
		++_lookup_itr;
		return *this;
	}
	decltype(_src[*_lookup_itr]) operator* () const { return _src[*_lookup_itr]; }
	bool      operator==(const lookup_itr& rhs) const { return _lookup_itr == rhs._lookup_itr; }
	bool      operator!=(const lookup_itr& rhs) const { return _lookup_itr != rhs._lookup_itr; }
};

template<class Src, class Lookup>
struct lookup_t {
	lookup_t(Src&& src, Lookup&& lookup) :
		src(std::forward<Src>(src)),
		lookup(std::forward<Lookup>(lookup)) {}
	Src src;
	Lookup lookup;

	constexpr lookup_itr<Src, Lookup> begin() const {
		return lookup_itr<Src, Lookup>(Src(src), Lookup(lookup));
	}
	constexpr lookup_itr<Src, Lookup> end() const {
		return lookup_itr<Src, Lookup>(Src(src), Lookup(lookup), (lookup_itr<Src, Lookup>::End()));
	}
};

template<class Src, class Lookup>
lookup_t<Src, Lookup> lookup(Src&& src, Lookup&& lookup) {
	return lookup_t<Src, Lookup>(std::forward<Src>(src), std::forward<Lookup>(lookup));
}
#endif
