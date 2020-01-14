#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

template<typename T>
class List
{
public:
    // Constructors
    List();
    List(List<T> const & o);
    ~List();

    // List methods
    bool empty() const;
    unsigned int size() const;

    void push_back(T v);
    void push_front(T v);

    T const & front() const;
    T& front();
    T const & back() const;
    T& back();
    T pop_front();
    T pop_back();

    void display(std::ostream & out = std::cout) const;

private:
    struct Cell
    {
        Cell(T v, Cell* prev, Cell* next);
        T _value;
        Cell* _previous;
        Cell* _next;
    };

    Cell* _first;
    Cell* _last;

private:
    // Iterator class
    template<typename CellType>
    class Iterator
    {
        friend class List;
    public:
        Iterator(): _cell{nullptr} {}

        bool operator==(Iterator const&o) { return o._cell == _cell; }
        bool operator!=(Iterator const&o) { return o._cell != _cell; }

        Iterator& operator++() {
            _cell = _cell->_next;
            return *this;
        } // Prefixé

        Iterator operator++(int) {
            Iterator copy{*this};
            _cell = _cell->_next;
            return copy;
        } // Postfixé

        T & operator*() { return _cell->_value; }

        T const & operator*() const { return _cell->_value; }

    private:
        Iterator(CellType* cell): _cell{cell} {}
        CellType* _cell;
    };

public:
    using iterator = Iterator<Cell>;
    using const_iterator = Iterator<Cell const>;

    // Methods using iterators
    iterator begin() const;
    const_iterator cbegin() const;
    iterator end() const;
    const_iterator cend() const;

    iterator find(T const & elem);
    void remove(iterator const & it);
    void insert(iterator const & it, T val);
};


template<typename T>
std::ostream& operator<<(std::ostream & out, List<T> const & list);

#include "List.tpp"

#endif