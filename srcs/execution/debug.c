#include "execution.h"

void print_array(char **array, size_t arr_len)
{
        int i;
        i = -1;
        while (++i < (int)arr_len)
                printf("%s\n", array[i]);
}
