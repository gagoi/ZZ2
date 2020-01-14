#include <iostream>

class M {
 public:
  M() {
    std::cout << "M::M()" << std::endl;
  }
   ~M() {
    std::cout << "M::~M()" << std::endl;
  }
    M(const M&) {
    std::cout << "M::M(const M&)" << std::endl;
  }

    M& operator=(const M& m) {
        if(&m != this)
            std::cout << "M::operator=(const M& m)" << std::endl;
        return *this;
    }
};

class F : public M {
 public:
  F() {
    std::cout << "F::F()" << std::endl;
  }
~F() {
    std::cout << "F::~F()" << std::endl;
  }
  F(const F& f) : M(f) {
    std::cout << "F::F(const F&)" << std::endl;
  }

    F& operator=(const F& f) {
        if(&f != this) {
            M::operator=(f);
            std::cout << "F::operator=(const F& f)" << std::endl;
        }
        return *this;
    }
};

class A {
 public:
  A() {
    std::cout << "A::A()" << std::endl;
  }
   ~A() {
    std::cout << "A::~A()" << std::endl;
  }
    A(const A& a) : m(a.m) {
    std::cout << "A::A(const A&)" << std::endl;
  }

    A& operator=(const A& a) {
        if(&a != this)
            std::cout << "A::operator=(const A& a)" << std::endl;
        return *this;
    }
private:
    M m;
};

int main(int, char**) {
/*
  F f1;
  F f2 = f1;

  f1 = f2;
*/
  A a1;
  A a2(a1);

  return 0;
}