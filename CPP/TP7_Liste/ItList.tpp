template <typename T>
ItList<T>::ItList():
	_c(nullptr)
{
}

template <typename T>
ItList<T>::ItList(Cell<T> * el):
	_c(el)
{
}

template<typename T>
bool operator!=(const ItList<T> & i, const ItList<T> & i2)
{
	return i._c != i2._c;
}


template<typename T>
T& ItList<T>::operator*()
{
	if (_c == nullptr) throw std::exception();
	return _c->getValue();
}

template<typename T>
const T& ItList<T>::operator*() const
{
	if (_c == nullptr) throw std::exception();
	return _c->getValue();
}

template<typename T>
ItList<T>& ItList<T>::operator++()
{
	_c = _c->next();
	return *this;
}

template<typename T>
ItList<T> ItList<T>::operator++(int)
{
	auto tmp(*this);
	operator++();
	return tmp;
}

template<typename T>
ItList<T>& ItList<T>::operator--()
{
	_c = _c->prev();
	return *this;
}

template<typename T>
ItList<T> ItList<T>::operator--(int)
{
	auto tmp(*this);
	operator--();
	return tmp;
}

template<typename T>
void ItList<T>::remove()
{
	_c->prev()->setNext(_c->next());
	auto c = _c;
	operator++();
	delete c;
}
