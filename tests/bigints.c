#include "BigInteger.h"
#include <stdio.h>
/* Testing BigInteger structure */

int main(void)
{
    BigInteger *a = bigint_init("123456789");
    BigInteger *b = bigint_init("987654321");
    bigint_multiply(a, b);
    printf("%s\n", bigint_to_string(a));
}