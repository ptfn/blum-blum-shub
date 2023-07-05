#include <stdio.h>
#include "bbs.h"

int main()
{
    FILE *file = fopen("file.txt", "w");
    init();

    for (long long i = 0; i < 2e8; i++)
        fprintf(file, "%ld\n", rnd()%1000);

    fclose(file);
    return 0; 
}