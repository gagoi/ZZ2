#include <limits.h>
#include <stdio.h>

typedef unsigned int uint;

#define bit(x) (1 << x)

uint miroir_bin(uint n)
{
    uint miroir = 0;
    for(uint i = 0; i < sizeof(uint) * CHAR_BIT; i++)
    {
        miroir <<= 1;
        miroir |= n & 1;
        n <<= 1;
    }
    
    return miroir;
}

int main()
{
    uint n = 11;
    uint m = 0;

    printf("%u: %#x\n", n, n);

    m = miroir_bin(n);

    printf("%u: %#x\n", m, m);

    return 0;
}