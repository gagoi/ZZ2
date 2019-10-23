template<typename T>
Cell<T>::Cell(T value, Cell* prev, Cell* next):
	_value(value), _next(next), _prev(prev)
{
}

template<typename T>
Cell<T> * Cell<T>::next() const
{
	return _next;
}

template<typename T>
Cell<T> * Cell<T>::prev() const
{
	return _prev;
}

template<typename T>
void Cell<T>::setNext(Cell<T> * next)
{
	_next = next;
}

template<typename T>
void Cell<T>::setPrev(Cell<T> * prev)
{
	_prev = prev;
}

template<typename T>
T Cell<T>::getValue() const
{
	return _value;
}

template<typename T>
std::ostream & operator<<(std::ostream & out, Cell<T> & t)
{
	out << t.getValue();
	return out;
}

template<typename T>
std::ostream & operator<<(std::ostream & out, Cell<T> * t)
{
	out << t->getValue();
	return out;
}