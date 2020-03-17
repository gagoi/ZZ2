#ifndef NULL_POINTER_HPP_
#define NULL_POINTER_HPP_

#include <iostream>
#include <string>

class Null_pointer
{
private:
	std::string _msg;
public:
	Null_pointer(const std::string& str="Pas alloué");
	Null_pointer(const Null_pointer&);
	~Null_pointer();
};

#endif
