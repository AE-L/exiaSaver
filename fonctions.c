#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "fonctions.h"

int my_rand(int x);
{
    srand(time(NULL));
    int randomValue;
    randomValue=rand()%x;

    return(randomValue);
}
