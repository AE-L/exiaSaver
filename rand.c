#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int my_rand(int x);
{
    srand(time(NULL));
    int randomValue;
    randomValue=rand()%x;

    return(randomValue);
}
