#include<iostream>

template<class T>
class Mere {
 protected:
  T a;
 public:
  Mere(T t):a(t) {}
  void f() { std::cout << a ; }
};
template<class T>
class Fille : public Mere<T> {
 public:
  Fille(T t): Mere<T>(t) {}
  void m() { 
       this->a = this->a*this->a; 
       this->f();
     }
};
