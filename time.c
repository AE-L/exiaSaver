#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[])
{
    int i = NULL;

    char format[128];

    time_t temps;

    struct tm date;

    FILE* fichier = NULL;




    // On récupère la date et l'heure actuelles.

    time(&temps);

    date=*localtime(&temps);


    // On remplit la chaîne avec le format choisi, puis on l'affiche.

    strftime(format, 128, "%X", &date);

    fichier = fopen ("time.txt", "w");

    if(fichier != NULL)
    {
        for(i=0;i<8;i++)
        {
            fprintf(fichier, "%c", format[i]);

        }
        fclose(fichier);
    }

    puts(format);


    return 0;

}
