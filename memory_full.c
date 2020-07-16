#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

unsigned long maximum = 0;
int main(int argc, char *argv[])
{
    unsigned long alloc_size[] = {1024 * 1024 * 1024, 1024 * 1024, 1024};
    int i, count;
    for (i = 0; i < ARRAY_SIZE(alloc_size); i++)
    {
        for (count = 1;; count++)
        {
            void *block = malloc(maximum + alloc_size[i] * count);
            if (block != NULL)
            {
                maximum += alloc_size[i] * count;
                free(block);
            }
            else
            {
                break;
            }
        }
    }
    printf("maximum alloc size = %lu bytes \n", maximum);
    void *block = malloc(maximum);
    for (i = 0; i < 0xff; i++)
    {
        memset(block, i & 0xff, maximum);
    }
    free(block);
    return 0;
}