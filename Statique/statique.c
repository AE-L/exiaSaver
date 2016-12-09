#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

char getch()
{
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
}

char* CHEMIN_IMAGE = "IMAGE";

int my_rand()
{
    srand(time(NULL));
    int nbgen=rand()%3+1;
    return nbgen;
}

int position_X(char* tab_head)
{
    char tab_x[1];
    tab_x[0]=0;
    tab_x[1]=0;
  
    int i;
    int caractereActuel;
    int pos_x;
    FILE* image;
    image = fopen(CHEMIN_IMAGE,"r");

    for(i=0;i<8;i++)
            {
                caractereActuel = fgetc(image);
                tab_head[i] = caractereActuel;
            }
            fclose(image);

            //Detection de des dimension
            tab_x[0] = tab_head[4];
            tab_x[1] = tab_head[5];
            sscanf(tab_x, "%d", &pos_x);

    return pos_x;
}

int position_Y(char* tab_head)
{
    char tab_y[1];
    tab_y[0] = 0;
    tab_y[1] = 0;
    int i;
    int caractereActuel;
    int pos_y;
    FILE* image;
    image = fopen(CHEMIN_IMAGE,"r");

    for(i=0;i<15;i++)
            {
                caractereActuel = fgetc(image);
                tab_head[i] = caractereActuel;
            }
            fclose(image);

            //Detection de des dimension
            tab_y[0] = tab_head[7];
            tab_y[1] = tab_head[8];
            sscanf(tab_y, "%d", &pos_y);

    return pos_y;
}

char* load_screen(char* screen)
{
    FILE* image;
    int caractereActuel;
    int i = 0;

    image = fopen(CHEMIN_IMAGE,"r");
    for (i=0;i<8;i++)
    {
        caractereActuel = fgetc(image);
    }

    do
        {
            caractereActuel = fgetc(image);
            screen[i] = caractereActuel;
            i++;

        } while (caractereActuel != EOF);
        fclose(image);

    return screen;
}

void affichage(char* screen, int pos_x, int pos_y)
{
    int centrage_x;
    int centrage_y;
    int j = 0;
    int i;
    int x;
    int y;
    
    //Calcule la taille de la console.
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    //Calcul du centre
    centrage_x = ((w.ws_col - pos_x) / 2);
    centrage_y = ((w.ws_row - pos_y) / 2);

    
    
    //Affcihe et centre.
    
    
    if (centrage_y != 0)
      {
	for (y=0;y<centrage_y;y++)
	  {
	    printf("\n");
	  }
      }
    if (centrage_x != 0)
      {
	for (x=0;x<centrage_x;x++)
	  {
	    
	    printf(" ");
	  }
      }
    
    for (i=0;i<3850;i++)
                {
                    switch(screen[i])
                    {
                    case '0':
                        printf(" ");
                        break;
                    case '1':
                        printf("█");
                        break;
                    }
                    if (j == 160)
                    {
                        j=0;
                        printf("\n");
			if (centrage_x != 0)
			  {
			    for (x=0;x<centrage_x;x++)
			      {
				printf(" ");
			      }
			  }
                    }
                    else
                    {
                        j++;
                    }
                }
}

int main()
{
    //VARIABLE
    FILE* image;

    int x = 1;

    int pos_x;
    int pos_y;

    char *tab_head;
    char *screen;
    tab_head = malloc(12*(sizeof(char*)));
    screen = malloc(3850*(sizeof(char*)));
    char *tab_full;
    //FIN VARIABLE
    system("clear");
    x = my_rand();

    //CHOIX DE L'IMAGE
    switch (x)
    {
    //IMAGE 1
    case 1:
        CHEMIN_IMAGE = "stat_1.pbm";
        if (image != NULL)
        {
            //Detection de des dimension
            pos_x = position_X(tab_head);
            pos_y = position_Y(tab_head);
            //Chargement de l'image dans un tableau
            load_screen(screen);
            //Affichage de l'image par le biais du tableau
            affichage(screen,pos_x,pos_y);


        }
        break;
    //IMAGE 2
    case 2:
        CHEMIN_IMAGE = "stat_2.pbm";
        if (image != NULL)
        {
            //Detection de des dimension
            pos_x = position_X(tab_head);
            pos_y = position_Y(tab_head);
            //Chargement de l'image dans un tableau
            load_screen(screen);
            //Affichage de l'image par le biais du tableau
            affichage(screen,pos_x,pos_y);
        }
        break;
    //IMAGE 3
    case 3:
        CHEMIN_IMAGE = "stat_3.pbm";
        if (image != NULL)
        {
            //Detection de des dimension
            pos_x = position_X(tab_head);
            pos_y = position_Y(tab_head);
            //Chargement de l'image dans un tableau
            load_screen(screen);
            //Affichage de l'image par le biais du tableau
            affichage(screen,pos_x,pos_y);
        }
        break;
    }

   getch();
   system("clear");

free(tab_head);
free(screen);
}

