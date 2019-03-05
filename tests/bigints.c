#include "BigInteger.h"
#include <stdio.h>
#include <stdlib.h>
/* Testing BigInteger structure */

void prints(char *c)
{
    if (c == NULL)
    {
        return;
    }
    printf("%s\n", c);
    free(c);
}

int main(void)
{
    BigInteger *a = bigint_init("123456789");
    BigInteger *b = bigint_init("987654321");
    bigint_multiply(a, b);
    prints(bigint_to_string(a));
    BigInteger *c = bigint_copy(a);
    bigint_subtract(a, c);
    prints(bigint_to_string(a));
}