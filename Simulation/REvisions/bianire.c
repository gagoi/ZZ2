#include <stdio.h>

void miroir(unsigned int * src, unsigned int * res)
{
	for (int j = 0; j < sizeof(*src) * 8; ++j)
	{
		*res |= ((*src >> j) & 1) << sizeof(*src) * 8 - j - 1; 
	}
}

void affichebin(unsigned n)
{
	unsigned bit = 0 ;
	unsigned mask = 1 ;
	for (int i = 0 ; i < 32 ; ++i)
	{
		bit = (n & mask) >> i ;
		printf("%d", bit) ;
		mask <<= 1 ;
	}
}

int main()
{
	unsigned int src = 1;
	unsigned int res;
	
	for (src = 1; src < 10; ++src)
	{
		res = 0;
		miroir(&src, &res);
		printf("sizeof(int) = %lu & i = %u ",sizeof(int), res);
		affichebin(src);
		printf(" - ");
		affichebin(res);
		printf("\n");
	}
	return 0;
}

