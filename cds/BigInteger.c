#include "BigInteger.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MINSIZE 16 /* Initial size of BigInteger array. Will not shrink beyond this point. */
#define FACTOR 2   /* Shrink/expand factor. */
#define RADIX 10   /* Radix of numbers. Might make this available to user at some point, but decimal for now. */

BigInteger *bigint_init(char *number)
{
    if (number == NULL)
    {
        return NULL;
    }
    size_t size;
    bool found = false;
    bool sign = false;
    for (size = 0; number[size] != '\0'; size++)
    {
        if (size == 0 && number[size] == '-')
        {
            sign = true;
        }
        else if (number[size] < '0' || number[size] > '9'
                    || (!found && number[size] == '0' && size != 0 && number[size + 1] != '\0'))
        {
            fprintf(stderr, "BigInteger Error: Passed string is not a valid number!\n");
            return NULL;
        }
        else
        {
            found = true;
        }
    }
    if (sign)
    {
        size--;
    }
    BigInteger *bigint = malloc(sizeof(BigInteger));
    if (bigint == NULL)
    {
        fprintf(stderr, "BigInteger Error: Could not allocate enough memory for BigInteger struct!\n");
        return NULL;
    }
    bigint->num = calloc(sizeof(uint8_t), size * FACTOR);
    if (bigint->num == NULL)
    {
        free(bigint);
        fprintf(stderr, "BigInteger Error: Could not allocate enough memory for BigInteger array!\n");
        return NULL;
    }
    bigint->sign = sign;
    bigint->size = size;
    bigint->max_size = size * FACTOR;
    for (size_t i = 0; i < size; i++)
    {
        bigint->num[size - i - 1] = number[i + (sign ? 1 : 0)] - '0';
    }
    return bigint;
}

void bigint_destroy(BigInteger *bigint)
{
    if (bigint == NULL)
    {
        return;
    }
    free(bigint->num);
    free(bigint);
}

static bool is_zero(BigInteger *bigint)
{
    if (bigint == NULL)
    {
        return false;
    }
    return bigint->size == 1 && bigint->num[0] == 0;
}

BigInteger *bigint_copy(BigInteger *bigint)
{
    if (bigint == NULL)
    {
        return NULL;
    }
    BigInteger *cpy = malloc(sizeof(BigInteger));
    if (cpy == NULL)
    {
        fprintf(stderr, "BigInteger Error: Could not allocate enough memory for BigInteger struct!\n");
        return NULL;
    }
    cpy->num = malloc(sizeof(uint8_t) * bigint->max_size);
    if (cpy->num == NULL)
    {
        free(cpy);
        fprintf(stderr, "BigInteger Error: Could not allocate enough memory for BigInteger array!\n");
        return NULL;
    }
    memcpy(cpy->num, bigint->num, bigint->max_size * sizeof(uint8_t));
    cpy->max_size = bigint->max_size;
    cpy->size = bigint->size;
    cpy->sign = bigint->sign;
    return cpy;
}

static void bigint_grow(BigInteger *bigint)
{
    if (bigint == NULL)
    {
        return;
    }
    uint8_t *larger = realloc(bigint->num, bigint->max_size * FACTOR);
    if (larger == NULL)
    {
        fprintf(stderr, "BigInteger Error: Could not expand BigInteger array!\n");
        return;
    }
    for (size_t i = bigint->max_size; i < bigint->max_size * FACTOR; i++)
    {
        larger[i] = 0;
    }
    bigint->num = larger;
    bigint->max_size *= FACTOR;
}

static void bigint_shrink(BigInteger *bigint)
{
    if (bigint == NULL)
    {
        return;
    }
    if (bigint->size * FACTOR > bigint->max_size || bigint->max_size <= MINSIZE)
    {
        return;
    }
    uint8_t *smaller = realloc(bigint->num, bigint->max_size / FACTOR);
    if (smaller == NULL)
    {
        fprintf(stderr, "BigInteger Error: Could not shrink BigInteger array!\n");
        return;
    }
    bigint->num = smaller;
    bigint->max_size /= FACTOR;
}

void bigint_add(BigInteger *a, BigInteger *b)
{
    if (a == NULL || b == NULL)
    {
        return;
    }
    if (a->sign != b->sign)
    {
        a->sign = !a->sign;
        bigint_subtract(a, b);
        if (is_zero(a))
        {
            a->sign = false;
        }
        else
        {
            a->sign = !a->sign;
        }
        return;
    }
    int carry = 0;
    int sum = 0;
    int total = 0;
    for (size_t i = 0; i < b->size || carry != 0; i++)
    {
        if (i >= a->max_size)
        {
            bigint_grow(a);
            if (i >= a->max_size)
            {
                return;
            }
        }
        if (i == a->size)
        {
            a->size++;
        }
        total = a->num[i] + (i < b->size ? b->num[i] : 0) + carry;
        sum = total % RADIX;
        carry = total / RADIX;
        a->num[i] = sum;
    }
    if (a->size * FACTOR < a->max_size && a->max_size > MINSIZE)
    {
        bigint_shrink(a);
    }
}

void bigint_subtract(BigInteger *a, BigInteger *b)
{
    if (a == NULL || b == NULL)
    {
        return;
    }
    if (a->sign != b->sign)
    {
        a->sign = !a->sign;
        bigint_add(a, b);
        a->sign = !a->sign;
        return;
    }
    if (bigint_less(a, b))
    {
        BigInteger *tmp = bigint_copy(b);
        bigint_subtract(tmp, a);
        a->sign = !a->sign;
        a->size = tmp->size;
        a->max_size = tmp->max_size;
        free(a->num);
        a->num = tmp->num;
        free(tmp);
        return;
    }
    int carry = 0;
    int sum = 0;
    int total = 0;
    for (size_t i = 0; i < b->size || carry != 0; i++)
    {
        if (i >= a->max_size)
        {
            bigint_grow(a);
            if (i >= a->max_size)
            {
                return;
            }
        }
        total = a->num[i] - (i < b->size ? b->num[i] : 0) + carry;
        sum = total % RADIX;
        carry = total / RADIX;
        if (sum < 0)
        {
            a->num[i] = RADIX + sum;
            carry--;
        }
        else
        {
            a->num[i] = sum;
        }
    }
    /* Stripping zeroes. */
    while (a->num[a->size - 1] == 0 && a->size > 1)
    {
        a->size--;
    }
    if (is_zero(a))
    {
        a->sign = false;
    }
    if (a->size * FACTOR < a->max_size && a->max_size > MINSIZE)
    {
        bigint_shrink(a);
    }
}

bool bigint_less(BigInteger *a, BigInteger *b)
{
    if (b == NULL || a == NULL)
    {
        return false;
    }
    if (b->size > a->size)
    {
        return true;
    }
    else if (b->size < a->size)
    {
        return false;
    }
    else
    {
        for (size_t i = 0; i < a->size; i++)
        {
            if (a->num[a->size - i - 1] < b->num[b->size - i - 1])
            {
                return true;
            }
            else if(a->num[a->size - i - 1] > b->num[b->size - i - 1])
            {
                return false;
            }
        }
    }
    return false;
}

bool bigint_greater(BigInteger *a, BigInteger *b)
{
    return bigint_less(b, a);
}

bool bigint_equals(BigInteger *a, BigInteger *b)
{
    if (a == NULL || b == NULL)
    {
        return false;
    }
    if (a->size != b->size)
    {
        return false;
    }
    else
    {
        for (size_t i = 0; i < a->size; i++)
        {
            if (a->num[a->size - i - 1] != b->num[b->size - i - 1])
            {
                return false;
            }
        }
    }
    return true;
}

/* Adds a to itself n times and stores result in tmp. */
static void naive_multiply(BigInteger *tmp, BigInteger *a, uint8_t n)
{
    for(; n > 0; n--)
    {
        bigint_add(tmp, a);
    }
}

/* Shifts tmp n steps over for multiply summing. Grows array if necessary. */
static void shift(BigInteger *tmp, size_t n)
{
    if (n == 0)
    {
        return;
    }
    while (n + tmp->size >= tmp->max_size)
    {
        bigint_grow(tmp);
    }
    memmove(tmp->num + n, tmp->num, tmp->size * sizeof(uint8_t));
    for (size_t i = 0; i < n; i++)
    {
        tmp->num[i] = 0;
    }
    tmp->size += n;
}

void bigint_multiply(BigInteger *a, BigInteger *b)
{
    if (a == NULL || b == NULL)
    {
        return;
    }
    /* Making a positive for the naive multiplications. */
    bool sign = a->sign;
    a->sign = false;
    BigInteger *sum = bigint_init("0");
    if (sum == NULL)
    {
        fprintf(stderr, "BigInteger Error: Could not allocate enough memory for BigInteger multiply!\n");
        return;
    }
    for (size_t i = 0; i < b->size; i++)
    {
        if (b->num[b->size - i - 1] > 0)
        {
            BigInteger *tmp = bigint_init("0");
            if (tmp == NULL)
            {
                fprintf(stderr, "BigInteger Error: Could not allocate enough memory for BigInteger multiply!\n");
                return;
            }
            naive_multiply(tmp, a, b->num[b->size - i - 1]);
            shift(tmp, b->size - i - 1);
            bigint_add(sum, tmp);
            bigint_destroy(tmp);
        }
    }
    a->sign = sign != b->sign;
    a->size = sum->size;
    a->max_size = sum->max_size;
    free(a->num);
    a->num = sum->num;
    free(sum);
    if (is_zero(a))
    {
        a->sign = false;
    }
}

/* Naive Division and Modulo operations for the time being.
 * Better than nothing. */
static void naive_division(BigInteger *a, BigInteger *b, bool modulo)
{
    BigInteger *counter, *one;
    /* Making a same sign as b for naive divisons. */
    bool sign = a->sign;
    a->sign = b->sign;
    if (!modulo)
    {
        counter = bigint_init("0");
        if (counter == NULL)
        {
            fprintf(stderr, "BigInteger (naive_division) Error: Could not allocate memory for counter!\n");
            return;
        }
        one = bigint_init("1");
        if (one == NULL)
        {
            fprintf(stderr, "BigInteger (naive_division) Error: Could not allocate memory for constant!\n");
            return;
        }
    }
    while (bigint_greater(a, b))
    {
        bigint_subtract(a, b);
        if (!modulo)
        {
            bigint_add(counter, one);
        }
    }
    if (bigint_equals(a, b))
    {
        bigint_subtract(a, b);
        if (!modulo)
        {
            bigint_add(counter, one);
        }
    }
    if (!modulo)
    {
        a->size = counter->size;
        a->max_size = counter->max_size;
        a->sign = sign != b->sign;
        free(a->num);
        a->num = counter->num;
        bigint_destroy(one);
    }
    if (is_zero(a))
    {
        a->sign = false;
    }
}

void bigint_divide(BigInteger *a, BigInteger *b)
{
    naive_division(a, b, false);
}

void bigint_modulo(BigInteger *a, BigInteger *b)
{
    naive_division(a, b, true);
}

char *bigint_to_string(BigInteger *bigint)
{
    if (bigint == NULL)
    {
        return NULL;
    }
    size_t size = sizeof(char) * (bigint->size + (bigint->sign ? 2 : 1));
    char *str = malloc(size); /* plus null terminating char (and sign if negative) */
    if (str == NULL)
    {
        fprintf(stderr, "BigInteger Error: Could not allocate enough memory for BigInteger string!\n");
        return NULL;
    }
    for (size_t i = 0; i < bigint->size; i++)
    {
        str[bigint->size - i - (bigint->sign ? 0 : 1)] = '0' + bigint->num[i];
    }
    if (bigint->sign)
    {
        str[0] = '-';
        str[bigint->size + 1] = '\0';
    }
    else
    {
        str[bigint->size] = '\0';
    }
    return str;
}