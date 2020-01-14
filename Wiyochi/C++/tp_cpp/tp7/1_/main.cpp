#include <iostream>

template<typename T>
const T& maximum(const T& a,const T & b) {
    return ((a > b) ? a : b);
}

int main()
{
    std::cout << maximum(1, 3) << std::endl;
    std::cout << maximum(static_cast<float>(1), 3.2f) << std::endl;
    return 0;
}