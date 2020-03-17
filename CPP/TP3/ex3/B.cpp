#include "B.hpp"

B::B(int k):
j(k)
{
}

void B::exec(int k)
{
	j+=k;
}