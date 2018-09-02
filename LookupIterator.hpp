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
template<class Src, class Lookup>
struct lookup_itr {
private:
	Src _src;
	Lookup _lookup;
	//using lookup_itr_t = contained_iterator_t<Lookup>;
	//using src_itr_t = contained_iterator_t<Src>;
	typedef decltype(begin(std::declval<Src>())) src_itr_t;
	typedef decltype(begin(std::declval<Lookup>())) lookup_itr_t;
	//using lookup_itr_t = Lookup::iterator;
	//using src_itr_t = typename Src::iterator;
	lookup_itr_t _lookup_itr;
	//typename contained_iterator_t<typename std::remove_const<Lookup>::type> _lookup_itr;
public:
	struct End {};
	explicit lookup_itr(Src&& src, Lookup&& lookup) : _src(src), _lookup(lookup) {
		using std::begin;
		_lookup_itr = begin(_lookup);
	}
	explicit lookup_itr(Src&& src, Lookup&& lookup, End end) : _src(src), _lookup(lookup) {
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
	decltype(_src[*_lookup_itr]) operator* () const { return _src[*_lookup_itr];/* _src[*_lookup_itr];*/ }
	bool      operator==(const lookup_itr& rhs) const { return _lookup_itr == rhs._lookup_itr; }
	bool      operator!=(const lookup_itr& rhs) const { return _lookup_itr != rhs._lookup_itr; }
};

template<class Src, class Lookup>
struct lookup_t {
	Src src;
	Lookup lookup;
	constexpr auto begin() const {
		return lookup_itr<Src, Lookup>{ std::forward<Src>(src), std::forward<Lookup>(lookup) };
	}
	constexpr auto end() const {
		return lookup_itr<Src, Lookup>{ std::forward<Src>(src), std::forward<Lookup>(lookup), lookup_itr<Src, Lookup>::End{} };
	}
};

template<class Src, class Lookup>
lookup_t<Src, Lookup> lookup(Src&& src, Lookup&& lookup) {
	return { std::forward<Src>(src), std::forward<Lookup>(lookup) };
}
#endif