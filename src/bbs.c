#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "bbs.h"

#define SIZE(n) ((int)(floor(log10(n)) + 1))
#define BEGIN_PRIME  32000
#define LIMIT_PRIME  10000000
#define LENGTH_PRIME 10000
#define LENGTH_COMP  10000


typedef struct M
{
    uint16_t p;
    uint16_t q;
}M;

static uint64_t N, x1;

static uint64_t gcd(uint64_t a, uint64_t b)
{
    while (a != 0 && b != 0) {
        if (a > b)
            a = a % b;
        else
            b = b % a;
    }
    return a + b;
}

static uint64_t lcm(uint64_t a, uint64_t b)
{
    return (a * b) / gcd(a, b);
}

/* Generate Prime Numbers */
static void prime_number(uint64_t limit, uint64_t prime[], uint64_t length)
{
    bool* arr;
    arr = (bool*)calloc(limit + 1, sizeof(bool));

    uint64_t j = 0, k = 0, i;

    for (i = 0; i <= limit; i++)
        arr[i] = true;

    for (i = 2; (i * i) <= limit; i++)
        if (arr[i])
            for (j = (i * i); j <= limit; j += i)
                arr[j] = false;

    i = BEGIN_PRIME;

    while (i++ <= limit) {
        if (arr[i])
            if (k < length) {
                prime[k] = i;
                k++;
            }
            else
                break;
    }
    free(arr);
}

/* Generate Comparable Numbers */
static void comparable_number(uint64_t prime[], uint64_t length_prime,
                              M comparable[], uint64_t length_comparable)
{
    for (uint64_t i = length_prime, m = 0; i > 0; i--) {
        for (uint64_t j = 0; j < i; j++) {
            if (prime[i] % 4 == 3 && prime[j] % 4 == 3
                && gcd(prime[i], prime[j]) == 1
                && SIZE(prime[i]) == SIZE(prime[j])) {
                comparable[m].p = prime[i];
                comparable[m].q = prime[j];
                m++;
            }
        }
        if (m >= length_comparable) {
            break;
        }
    }
}

/* Generate Seed */
static uint64_t generate_xzero(uint64_t M)
{
    uint64_t x0 = time(0) % M;

    while (true) {
        if (x0 == 0 || x0 == 1)
            continue;
        
        if (gcd(x0, M) == 1)
            return x0;
        else
            x0++;
    }
}

static void generate_variable(M comparable)
{
    N = comparable.p * comparable.q;
    uint64_t x0 = generate_xzero(N);
    uint64_t lambda_N = lcm(comparable.p-1, comparable.q-1);
    x1 = (uint64_t)pow(x0, 2 % lambda_N) % N;
}

void init()
{
    uint64_t prime[LENGTH_PRIME];
    M comparable[LENGTH_COMP];

    prime_number(LIMIT_PRIME, prime, LENGTH_PRIME);
    comparable_number(prime, LENGTH_PRIME, comparable, LENGTH_COMP);
    generate_variable(comparable[time(0) % LENGTH_COMP]);
}

uint64_t rnd(void)
{
    x1 = (x1 * x1) % N;
    return x1;
}
