template<typename T>
List<T>::List():
	_first(nullptr)
{
}

template<typename T>
List<T>::~List()
{
	Cell<T> * act = _first;
	while (act != nullptr)
	{
		Cell<T> * next = act->next();
		delete act;
		act = next;
	}
}

template<typename T>
bool List<T>::isEmpty() const
{
	return _first == nullptr;
}

template<typename T>
std::size_t List<T>::size() const
{
	return _size;
}

template<typename T>
T List<T>::front() const
{
	if (isEmpty()) throw std::out_of_range("Empty list");
	return _first->getValue();
}

template<typename T>
T List<T>::back() const
{	
	if (isEmpty()) throw std::out_of_range("Empty list");
	return _last->getValue();
}

template<typename T>
void List<T>::push_back(T val)
{
	_size++;
	Cell<T> * act = _first;
	if (_first == nullptr)
	{
		_first = new Cell<T>(val, nullptr, nullptr);
		_last = _first;
	} else
	{
		_last->setNext(new Cell<T>(val, _last, nullptr));
		_last = _last->next();
	}
}

template<typename T>
void List<T>::push_front(T val)
{
	_size++;
	Cell<T> * act = _first;
	if (_first == nullptr)
	{
		_first = new Cell<T>(val, nullptr, nullptr);
	} else
	{
		Cell<T> * n = new Cell<T>(val, nullptr, _first);
		_first = n;
	}
}

template <typename T>
T List<T>::pop_back()
{
	if (isEmpty()) throw std::out_of_range("Empty list");
	
	T v = back();
	Cell<T> * old = _last;
	_last = _last->prev();
	delete old;
	_last->setNext(nullptr);

	_size--;

	if (size() == 0)
	{
		_first = nullptr;
		_last = nullptr;
	}

	return v;
}


template <typename T>
T List<T>::pop_front()
{
	if (isEmpty()) throw std::out_of_range("Empty list");

	T v = front();
	Cell<T> * old = _first;
	_first = _first->next();
	delete old;
	_first->setPrev(nullptr);

	_size--;

	if (size() == 0)
	{
		_first = nullptr;
		_last = nullptr;
	}

	return v;
}

template<typename T>
void List<T>::display(std::ostream & os) const
{
	os << *this << std::endl;
}


template<typename T>
std::ostream & operator<<(std::ostream & out, List<T> & t)
{
	for(Cell<T> * act = t._first; act != nullptr; act = act->next())
		out << act << " ";
    return out;
}