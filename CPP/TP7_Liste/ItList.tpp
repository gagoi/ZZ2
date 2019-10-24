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
T ItList<T>::operator*()
{
	return _c->getValue();
}