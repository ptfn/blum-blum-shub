#include <stdio.h>
#include "bbs.h"

int main()
{
    init();

    for (int i = 0; i < 50; i++)
        printf("%ld ", rnd());
    putchar('\n');
}