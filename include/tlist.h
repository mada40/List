//MAKHINYA DANIL 
//2023
//task_summer_school_2023
#ifndef __TDynamicList_H__
#define __TDynamicList_H__

#include<algorithm>
#include<stdexcept>

template<typename T>
class List
{
private:

	struct TNode
	{
		TNode* next = nullptr;
		T value;
		TNode(const T& _value) : next(nullptr), value(_value) {}
	};

	TNode* first = nullptr;
	TNode* last = nullptr;
	size_t sz = 0;

	void erase_after_node(TNode* node);
	void insert_after_node(TNode* node, const T& value);

public:

	struct iterator
	{
		TNode* node;
		iterator() = default;
		iterator(const iterator& other) = default;
		iterator(TNode* _node) noexcept { node = _node; }

		bool operator ==(const iterator& it) { return node == it.node; }
		bool operator !=(const iterator& it) { return node != it.node; }
		T& operator*() { return node->value; }
		iterator& operator ++();
	};

	List() : first(nullptr), last(nullptr), sz(0) {}
	List(const List& other);
	List(List&& other) noexcept : first(nullptr), last(nullptr), sz(0) {swap_lists(*this, other);}
	~List() noexcept { clear(); }
	List& operator= (const List& other);
	List& operator= (List&& other);

	bool empty() const noexcept { return sz == 0; }
	size_t size() const noexcept { return sz; }
	T& front() noexcept { if (!first) throw std::logic_error("list is empty"); return first->value; }
	void push_front(const T& v);
	void pop_front();
	void resize(size_t new_size);
	void clear() noexcept;
	void  remove(const T& value);
	void reverse();

	iterator begin() { return iterator(first); }
	iterator end() { return iterator(nullptr); }
	T& back() noexcept { if (!first) throw std::logic_error("list is empty"); return last->value; }

	void push_back(const T& v);
	void erase_after(const iterator& it) { erase_after_node(it.node); }
	void insert_after(const iterator& it, const T& value) { insert_after_node(it.node, value); }
	

	//function, which swaps the contents of two linked lists
	template<typename T2>
	friend void swap_lists(List<T2>& l1, List<T2>& l2) noexcept;
};

template<typename T>
inline typename List<T>::iterator& List<T>::iterator::operator++()
{
	if (!node)
		throw std::logic_error("out of range");
	node = node->next;
	return *this;
}

template<typename T>
inline void List<T>::clear() noexcept
{
	TNode* cur = first;
	while (cur)
	{
		TNode* temp = cur;
		cur = cur->next;
		delete temp;
	}
	sz = 0;
	last = nullptr;
	first = nullptr;
}

template<typename T>
inline void List<T>::remove(const T& value)
{
	if (first->value == value)
		pop_front();

	TNode* cur = first;
	while (cur)
	{
		if (cur->next && cur->next->value == value)
			erase_after_node(cur);

		cur = cur->next;
	}
}

template<typename T>
inline void List<T>::reverse()
{
	List<T> tmp;
	TNode* cur = first;
	while (cur)
	{
		T x = cur->value;
		tmp.push_front(x);
		cur = cur->next;
	}

	swap_lists(*this, tmp);
}

template<typename T>
inline void List<T>::push_back(const T& v)
{
	if (!first)
	{
		first = new TNode(v);
		last = first;
	}
	else
	{
		last->next = new TNode(v);
		last = last->next;
	}
	sz++;
}

template<typename T>
inline void List<T>::push_front(const T& v)
{
	TNode* tmp = first;
	first = new TNode(v);
	first->next = tmp;
	sz++;
}

template<typename T>
inline void List<T>::pop_front()
{
	if (!first)
		throw std::logic_error("list is empty");

	TNode* tmp = first->next;
	delete first;
	first = tmp;
	sz--;
}

template<typename T>
inline void List<T>::resize(size_t new_size)
{
	while (new_size > sz)
		push_front(T());

	while (new_size < sz)
		pop_front();
}

template<typename T>
inline List<T>& List<T>::operator=(const List& other)
{
	if (this == &other)
		return *this;

	List<int> tmp(other);
	swap_lists(*this, tmp);
	return *this;
}

template<typename T>
inline List<T>& List<T>::operator=(List&& other)
{
	if (this == &other)
		return *this;

	clear();
	swap_lists(*this, other);
	return *this;
}

template<typename T>
inline void List<T>::erase_after_node(TNode* node)
{
	if (!node || !node->next)
		throw std::logic_error("invalid node");

	TNode* er_el = node->next;
	node->next = er_el ? er_el->next : nullptr;
	delete er_el;
	sz--;
}

template<typename T>
inline void List<T>::insert_after_node(TNode* node, const T& value)
{
	if (!node)
		throw std::logic_error("invalid node");

	if (node == last)
	{
		push_back(value);
		return;
	}

	TNode* tmp = node->next;
	node->next = new TNode(value);
	node->next->next = tmp;
	sz++;
}

template<typename T>
inline List<T>::List(const List& other) : first(nullptr), last(nullptr), sz(0)
{
	TNode* tmp_first = other.first;
	while (tmp_first)
	{
		push_back(tmp_first->value);
		tmp_first = tmp_first->next;
	}
}

template<typename T2>
inline void swap_lists(List<T2>& l1, List<T2>& l2) noexcept
{
	std::swap(l1.first, l2.first);
	std::swap(l1.last, l2.last);
	std::swap(l1.sz, l2.sz);
}
#endif
