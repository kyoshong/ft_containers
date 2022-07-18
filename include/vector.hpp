// -*- C++ -*-
//===----------------------------- vector ------------------------------------===//

#ifndef VECTOR_HPP
#define VECTOR_HPP
# include <memory>
# include "vector_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{

	template <class Typ, class Alloc = std::allocator<Typ> >
	class vector{
	public:
		typedef Alloc													allocator_type;
		typedef Typ														value_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef vector_iterator<random_access_iterator_tag, value_type> iterator;
		typedef vector_iterator<random_access_iterator_tag, 
				value_type, ptrdiff_t, const Typ*, const Typ&>			const_iterator;
		typedef reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef reverse_iterator<iterator>								reverse_iterator;
		typedef	size_t													size_type;
		typedef	typename iterator::difference_type						difference_type;
	private:
		allocator_type	_alloc;
		pointer			_ptr;
		size_type		_capacity;
		size_type		_size;

	public:
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
	// default : 빈 컨테이너 생성
	explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _ptr(NULL), _capacity(0), _size(0) 
	{
		this->_ptr = this->_alloc.allocate(0);
	}

	// fill : n 개 요소를 가진 컨테이너 생성 & val을 복사해 채운다
	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	: _alloc(alloc), _ptr(NULL), _capacity(n), _size(n) 
	{
		this->_ptr = this->_alloc.allocate(n);
		for (size_type i = 0; i < n; i++)
		{
			this->_alloc.construct(this->_ptr + i, val);
		}
	}

	// range : iterator first ~ last 범위의 요소 생성 밍 값 복사
	template <typename Input>
	vector(Input first, Input last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!is_integral<Input>::value>::type* = 0) :
		_alloc(alloc), _size(0) 
		{
			difference_type n = last - first;
			this->_ptr = this->_alloc.allocate(n);
			this->_capacity = n;
			while (first != last) {
				push_back(*first);
				first++;
			}
		}
	
	// copy : 매개로 들어온 vector 의 요소를 동일한 순으로 복사하여 생성
	vector(const vector& x) : _alloc(x._alloc), _capacity(x._capacity), _size(x._size)
	{
		this->_ptr = this->_alloc.allocate(this->_capacity);
		for (size_type i = 0; i < this->_size; i++)
		{
			this->_alloc.construct(&this->_ptr[i], x._ptr[i]);
		}
	}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/
	~vector()
	{
		this->clear();
		this->_alloc.deallocate(this->_ptr, this->_capacity);
	}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/
	vector&		operator=(const vector* vec)
	{
		if (this != &vec) {
			assign(vec->begin(), vec->end());
		}
		return (*this);
	}

/*
** --------------------------------- METHODS ----------------------------------
*/
	/*============================== Iterator ===============================*/
	iterator				begin() { return (iterator(this->_ptr)); }
	const_iterator			begin() const { return (const_iterator(this->_ptr)); }
	// 백터 마지막 요소의 뒤에있는 이론적 요소의 iterator를 반환
	iterator				end() { return (iterator(this->_ptr + this->_size)); }
	const_iterator			end() const { return (const_iterator(this->_ptr + this->_size)); }
	
	reverse_iterator		rbegin() { return (reverse_iterator(this->end())); }
	const_reverse_iterator	rbegin() const { return (const_reverse_iterator(this->end())); }
	
	reverse_iterator		rend() { return (reverse_iterator(this->begin())); }
	const_reverse_iterator	rend() const { return (const_reverse_iterator(this->begin())); }

	/*============================== capacity ===============================*/
	size_type	size() const { return (this->_size); }
	size_type	capacity() const { return (this->_capacity); }
	size_type	max_size() const { return (this->_alloc.max_size()); }
	bool		empty() const { return (this->_size == 0); }
	// capacity 재할당
	void		reserve(size_type n)
	{
		if (n > max_size()) {
			throw (std::length_error("ft::vector reserve() max_size length Eroor"));
		}
		
			if (n > this->_capacity) {
			pointer tem = this->_ptr;
			this->_ptr =  this->_alloc.allocate(n);
			for (size_type i = 0; i < this->_size; i++)
			{
				this->_alloc.construct(&this->_ptr[i], tem[i]);
				this->_alloc.destroy(&tem[i]);
			}
			// this->_alloc.deallocate(tem, this->_capacity);
			this->_capacity = n;
		}
	}
	//n개의 사이즈를 포함 가능하도록 size 재조정, n이 기존 사이즈보다 큰 element는 val로 초기화
	void		resize(size_type n, value_type val = value_type())
	{
		if (this->_capacity < n) { reserve(n);}
		if (this->_size < n) {
			for (size_type i = this->_size; i < n; i++){
				this->_alloc.construct(this->_ptr + i, val);
			}
		}
		else {
			for (size_type i = 0; i < this->_size; i++){
				this->_alloc.destroy(this->_ptr + i);
			}
			this->_capacity = n;
		}
		this->_size = n;
	}
	/*============================== element access ===============================*/
	reference		operator[](size_type n)			{ return (this->_ptr[n]); }
	const_reference	operator[](size_type n) const	{ return (this->_ptr[n]); }

	reference		at(size_type n) { if (n >= this->_size) throw (std::out_of_range("ft::vector at")); return (this->_ptr[n]); }
	const_reference	at(size_type n) const { if (n >= this->_size) throw (std::out_of_range("ft::vector at")); return (this->_ptr[n]); }

	// begin 은 iterator를 반환 front 는 직접 참조를 반환
	reference			front() { return (this->_ptr[0]); }
	const_reference		front() const { return (this->_ptr[0]); }
	
	reference			back() { return (*(end() - 1)); }
	const_reference		back() const { return (*(end() - 1)); }

	/*============================== modifiers ===============================*/

	//벡터에 새 컨텐츠를 할당해 데이터를 바꾸고, 그에 따라 size 를 수정한다.
	template <typename Input_iter>
	void	assign(Input_iter first, Input_iter last,
		typename ft::enable_if<!ft::is_integral<Input_iter>::value, Input_iter>::type* = NULL)
	{
		clear();
		size_type n = 0;
		for (iterator it = first; it != last; it++)
		{
			n++;
		}
		if (n > this->_capacity) {
			this->_alloc.deallocate(this->_ptr, this->_capacity);
			this->_ptr = this->_alloc.allocate(n);
			this->_capacity = n;
		}
		this->_size = n;
		size_type i = 0;
		for (Input_iter iter = first; iter != last; iter++, i++) {
			this->_alloc.construct(&this->_ptr[i], *iter);
		}
	}

	void	assign(size_type n, const  value_type& val)
	{
		clear();
		if (n > this->_capacity) {
			this->_alloc.deallocate(this->_ptr, this->_capacity);
			this->_ptr = this->_alloc.allocate(n);
			this->_capacity = n;
		}
		this->_size = n;
		for (size_type i = 0; i < n; i++) {
			this->_alloc.construct(&this->_ptr[i], val);
		}
	}
	
	// capacity를 재할당 시 현재 capacity의 1.5배 할당
	void	push_back(const value_type& val)
	{
		if (this->_size == this->_capacity) {
			empty() ? reserve(10) : reserve(this->_capacity + (this->_capacity >> 1));
		}
		this->_alloc.construct(&this->_ptr[this->_size], val);
		++this->_size;
	}

	void	pop_back()
	{
		if (this->_size > 0) {
			--this->_size;
			this->_alloc.destroy(this->_ptr + (this->_size));
		}
	}
	//지정된 위치에 단일 element 삽입
	iterator	insert(iterator pos, const value_type& val)
	{
		size_type num = pos - this->begin();
		insert(pos, 1, val);
		return (this->_ptr + num);
	}
	//지정된 위치의 num 만큼의 사이즈에 val 추가
	void	insert(iterator pos, size_type num, const value_type& val)
	{
		vector tem = *this;
		size_type state = pos - this->_ptr;
		size_type idx = 0;
		reserve(this->_size + num);
		for (idx = state; idx < (state + num); idx++)
		{
			this->_alloc.construct(&this->_ptr[idx], val);
		}
		for (; idx < this->_size + num; idx++, state++)
		{
			this->_alloc.construct(&this->_ptr[idx], tem[state]);
		}
		this->_size += num;
	}
	//지정된 위치에 first ~ last 까지 element 추가
	template <typename Iter>
	void	insert(iterator pos, Iter first, Iter last, 
			typename ft::enable_if<!ft::is_integral<Iter>::value, Iter>::type* = NULL)
	{
		vector tem = *this;
		size_type n = last - first;
		size_type idx = pos - this->_ptr;
		size_type mid = idx;
		reserve(this->_size + n);
		for (size_type i = 0; i < n; idx++, i++)
		{
			this->_alloc.construct(&this->_ptr[idx], *(first + i));
		}
		for (; idx < this->_size + n; idx++, mid++)
		{
			this->_alloc.construct(&this->_ptr[idx], tem[mid]);
		}
		this->_size += n;
	}
	//단일 element 삭제
	iterator	erase(iterator pos)
	{
		return (erase(pos, pos + 1));
	}
	// first ~ last 까지 element 삭제
	iterator	erase(iterator first, iterator last)
	{
		if (empty()) return (end());
		size_type	num = first - this->begin();
		size_type	len = last - first;
		for (size_type i = num; i < this->_size && i + len < this->_size; i++)
		{
			(*this)[i] = (*this)[i + len];
		}
		for (difference_type _idx = 0; _idx < last - first; _idx++)
			this->pop_back();
		return (this->_ptr + num);
	}

	void		swap(vector &vec)
	{
		allocator_type	__alloc = this->_alloc;
		pointer			__ptr = this->_ptr;
		size_type		__size = this->_size;
		size_type		__capacity = this->_capacity;

		this->_ptr			= vec._ptr;
		this->_alloc		= vec._alloc;
		this->_size			= vec._size;
		this->_capacity		= vec._capacity;

		vec._ptr			= __ptr;
		vec._alloc			= __alloc;
		vec._size			= __size;
		vec._capacity		= __capacity;
	}

	//vector의 모든 요소 삭제 및 사이즈 0 초기화
	void		clear()
	{
		if (this->_size > 0){
			for (iterator iter = begin(); iter != end(); iter++)
			{
				this->_alloc.destroy(&(*iter));
			}
			this->_size = 0;
		}
	}

	/*============================== allocator ===============================*/

	allocator_type get_allocator() const {
		return (Alloc(this->_alloc));
	}

	};
	template <class Typ, class Alloc>
	bool	operator==(const vector<Typ, Alloc>& v1, const vector<Typ, Alloc>& v2)
	{
		if (v1.size() != v2.size()) return false;
		for (size_t i = 0; i < v1.size(); i++)
		{
			if (v1[i] != v2[i])
				return (false);
		}
		return (true);
	}
	
	template <class Typ, class Alloc>
	bool	operator!=(const vector<Typ, Alloc>& v1, const vector<Typ, Alloc>& v2) {
		return (!(v1 == v2));
	}

	template <class Typ, class Alloc>
	bool	operator<(const vector<Typ, Alloc>& v1, const vector<Typ, Alloc>& v2) {
		return (ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
	}

	template <class Typ, class Alloc>
	bool	operator>(const vector<Typ, Alloc>& v1, const vector<Typ, Alloc>& v2) {
		return (v2 < v1);
	}

	template <class Typ, class Alloc>
	bool	operator<=(const vector<Typ, Alloc>& v1, const vector<Typ, Alloc>& v2) {
		return !(v2 < v1);
	}

	template <class Typ, class Alloc>
	bool	operator>=(const vector<Typ, Alloc>& v1, const vector<Typ, Alloc>& v2) {
		return !(v1 < v2);
	}
	
	template <typename Typ, typename Alloc>
	void swap(vector<Typ, Alloc>& x, vector<Typ, Alloc>& y)
	{
		x.swap(y);
	}
} // namespace ft


#endif
