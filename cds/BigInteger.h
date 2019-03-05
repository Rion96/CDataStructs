#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct BigInteger
{
    bool sign;
    size_t max_size;
    size_t size;
    uint8_t *num;
} BigInteger;

/* Constructor for BigInteger.
 * Demands string representation of number.
 */
BigInteger *bigint_init(char *number);

/* Destructor for BigInteger. */
void bigint_destroy(BigInteger *bigint);

/* Create copy of bigint. */
BigInteger *bigint_copy(BigInteger *bigint);

/* Check if a is greater than b (absolute value). */
bool bigint_greater(BigInteger *a, BigInteger *b);

/* Check if a is less than b (absolute value). */
bool bigint_less(BigInteger *a, BigInteger *b);

/* Check if a is equal to b (absolute value). */
bool bigint_equals(BigInteger *a, BigInteger *b);

/* Adds b to a and stores result in a. */
void bigint_add(BigInteger *a, BigInteger *b);

/* Subtracts b from a and stores result in a. */
void bigint_subtract(BigInteger *a, BigInteger *b);

/* Multiplies a with b and stores result in a. */
void bigint_multiply(BigInteger *a, BigInteger *b);

/* Divides a with b and stores result in a. */
void bigint_divide(BigInteger *a, BigInteger *b);

/* Takes modulo of a and b and stores result in a. */
void bigint_modulo(BigInteger *a, BigInteger *b);

/* Get String representation of number. */
char *bigint_to_string(BigInteger *bigint);

#endif /* BIGINTEGER_H */