#include "A.hpp"
A::A(int k):
i(k)
{
}
void A::exec(int k)
{
	i+=k;
}