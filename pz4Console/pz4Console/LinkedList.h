#include <iterator>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class LinkedList {
public:

	class Node {
	public:

		Node() {

			_value = T();
			_next = _prev = this;
		}

		Node(T value, Node* next, Node* prev)
		{
			_next = next;
			_prev = prev;
			_value = value;

		}
		~Node() = default;

		Node* _next;
		Node* _prev;
		T _value;
	};

	class iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		friend class LinkedList;

		iterator(Node* myitem)
		{
			this->_item = myitem;
		}

		iterator& operator++()
		{
			_item = _item->_next;
			return *this;
		}

		iterator operator++(int)
		{
			_item = _item->_next;
			return iterator(_item->_prev);
		}

		iterator& operator--()
		{
			_item = _item->_prev;
			return *this;
		}

		iterator operator--(int)
		{
			_item = _item->_prev;
			return iterator(_item->_next);
		}

		T& operator*()
		{
			return _item->_value;
		}

		T* operator->()
		{
			return &(_item->_value);
		}

		bool operator==(iterator other)
		{
			return other._item == _item;
		}

		bool operator!=(iterator other)
		{
			return other._item != _item;
		}

		Node* _item;
	};

	class const_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		friend class LinkedList;

		const_iterator(Node* myitem)
		{
			this->_item = myitem;
		}

		const_iterator& operator++()
		{
			_item = _item->_next;
			return *this;
		}

		const_iterator operator++(int)
		{
			_item = _item->_next;
			return const_iterator(_item->_prev);
		}

		const_iterator& operator--()
		{
			_item = _item->_prev;
			return this;
		}

		const_iterator operator--(int)
		{
			_item = _item->_prev;
			return const_iterator(_item->_next);
		}

		const T& operator*()
		{
			return _item->_value;
		}

		T* operator->()
		{
			return &(_item->_value);
		}

		bool operator==(const_iterator other)
		{
			return other._item == _item;
		}

		bool operator!=(const_iterator other)
		{
			return other._item != _item;
		}

		const Node* _item;
	};

	class reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		friend class LinkedList;

		reverse_iterator(Node* myitem)
		{
			this->_item = myitem;
		}

		reverse_iterator& operator--()
		{
			_item = _item->_next;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			_item = _item->_next;
			return reverse_iterator(_item->_prev);
		}

		reverse_iterator& operator++()
		{
			_item = _item->_prev;
			return this;
		}

		reverse_iterator operator++(int)
		{
			_item = _item->_prev;
			return reverse_iterator(_item->_next);
		}

		T& operator*()
		{
			return _item->_value;
		}

		T* operator->()
		{
			return &(_item->_value);
		}

		bool operator==(reverse_iterator other)
		{
			return other._item == _item;
		}

		bool operator!=(reverse_iterator other)
		{
			return other._item != _item;
		}

		Node* _item;
	};

	class const_reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		friend class LinkedList;

		const_reverse_iterator(Node* myitem)
		{
			this->_item = myitem;
		}

		const_reverse_iterator& operator--()
		{
			_item = _item->_next;
			return *this;
		}

		const_reverse_iterator operator--(int)
		{
			_item = _item->_next;
			return const_reverse_iterator(_item->_prev);
		}

		const_reverse_iterator& operator++()
		{
			_item = _item->_prev;
			return this;
		}

		const_reverse_iterator operator++(int)
		{
			_item = _item->_prev;
			return const_reverse_iterator(_item->_next);
		}

		const T& operator*()
		{
			return _item->_value;
		}

		T* operator->()
		{
			return &(_item->_value);
		}

		bool operator==(const_reverse_iterator other)
		{
			return other._item == _item;
		}

		bool operator!=(const_reverse_iterator other)
		{
			return other._item != _item;
		}

		const Node* _item;
	};

	const_iterator cbegin() const
	{
		return const_iterator(_head->_next);
	}

	const_iterator cend() const
	{
		return const_iterator(_head);
	}

	iterator begin() const
	{
		return iterator(_head->_next);
	}

	iterator end() const
	{
		return iterator(_head);
	}

	const_reverse_iterator crend() const
	{
		return const_reverse_iterator(_head->_next);
	}

	const_reverse_iterator crbegin() const
	{
		return const_reverse_iterator(_head);
	}

	reverse_iterator rend() const
	{
		return reverse_iterator(_head->_next);
	}

	reverse_iterator rbegin() const
	{
		return reverse_iterator(_head);
	}

	LinkedList();
	LinkedList(T* arr, size_t count);
	LinkedList(const LinkedList<T>& other);
	LinkedList(LinkedList<T>&& other);
	~LinkedList();

	LinkedList<T>& operator= (const LinkedList<T>& other);
	LinkedList<T>& operator= (LinkedList<T>&& other);

	void Empty() const;
	void PushBack(const T& value);
	void PushFront(const T& value);
	void Insert(const T& value, size_t number);
	void Insert(iterator Where, const T& value);
	void Swap(size_t, size_t);

	iterator Erase(iterator Where)
	{
		iterator buffer = iterator(Where._item->_next);
		Where._item->_prev->_next = Where._item->_next;
		Where._item->_next->_prev = Where._item->_prev;
		delete(Where._item);
		return buffer;
	}

	void Remove(const T& value);
	void Reverse();


private:
	Node* _head = nullptr;
};

template <typename T>
LinkedList<T>::LinkedList()
{
	_head = new Node(T(), nullptr, nullptr);
	_head->_next = _head->_prev = _head;
}

template <typename T>
LinkedList<T>::LinkedList(T* arr, size_t count)
{
	_head = new Node(T(), nullptr, nullptr);
	_head->_next = _head->_prev = _head;

	for (int i = 0; i < count; ++i) {
		this->PushBack(arr[i]);
	}
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	delete(this);

	this = LinkedList();

	for (auto i = other.begin(); i != other.end(); ++i) {
		this->PushBack(*i);
	}
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator= (const LinkedList<T>& other)
{
	if (this == &other)
		return *this;

	while (begin() != end()) {
		Erase(begin());
	}

	LinkedList<T>::iterator i = other.begin();
	for (i; i != other.end(); i++) {
		PushBack(*i);
	}

	return *this;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other)
{
	this->_head = other._head;
	other._head = nullptr;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator= (LinkedList<T>&& other)
{
	this->_head = other._head;
	other._head = nullptr;

	return *this;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	while (begin() != end()) {
		Erase(begin());
	}
	delete(_head);
	_head = nullptr;
}

template<typename T>
void LinkedList<T>::Empty() const
{
	return begin() == end();
}

template <typename T>
void LinkedList<T>::PushBack(const T& value) {
	Insert(end(), value);
}

template <typename T>
void LinkedList<T>::PushFront(const T& value) {
	Insert(begin(), value);
}

template <typename T>
void LinkedList<T>::Insert(const T& value, size_t number) {
	auto iter = this->begin();
	if (distance(this->begin(), this->end()) < number) return;
	advance(iter, number);
	Insert(iter, value);
}

template <typename T>
void LinkedList<T>::Insert(iterator Where, const T& value) {
	Node* temp = new Node(value, Where._item, Where._item->_prev);

	Where._item->_prev->_next = temp;
	Where._item->_prev = temp;
}

template<typename T>
void LinkedList<T>::Remove(const T& value)
{
	auto it = begin();
	while (it != end())
	{
		if (*it == value) {
			Erase(it);
			return;
		}
		it++;
	}
}

template<typename T>
void LinkedList<T>::Reverse()
{
	LinkedList<T> temp = LinkedList();
	for (auto it = end(); it != begin(); --it)
	{
		temp.PushBack(*it);
	}

	delete(this);
	this = temp;
}

template<typename T>
void LinkedList<T>::Swap(size_t first, size_t sec)
{
	auto iterF = this->begin();
	if (distance(this->begin(), this->end()) < first) return;
	advance(iterF, first);
	
	auto iterS = this->begin();
	if (distance(this->begin(), this->end()) < sec) return;
	advance(iterS, sec);

	T fi = *iterF;
	T se = *iterS;
	Erase(iterF);
	Insert(se, first);
	Erase(iterS);
	Insert(fi, sec);
}

template <typename T>
ostream& operator<<(ostream& out, LinkedList<T>& other)
{

	auto iter = other.begin();
	while (iter != other.end()) {
		out << *iter << " ";
		iter++;
	}

	return out;
}

template <typename T>
ofstream& operator<<(ofstream& fout, LinkedList<T>& other)
{
	fout << distance(other.begin(), other.end()) << " ";

	auto iter = other.begin();
	while (iter != other.end()) {
		fout << *iter << " ";
		iter++;
	}

	return fout;
}

template <typename T>
ifstream& operator>>(ifstream& in, LinkedList<T>& other)
{
	int n;
	in >> n;
	T tmp;
	while (other.begin() != other.end()) {
		other.Erase(other.begin());
	}
	for (int i = 0; i < n; ++i) {
		in >> tmp;
		other.PushBack(tmp);
	}
	return in;
}
