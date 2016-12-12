#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <time.h>
 
#define KEYBOARDU 8 /*variable system for the keys*/
#define KEYBOARDD 2
#define KEYBOARDR 6
#define KEYBOARDL 4
#define KEYBOARDEXIT 120
 
 
struct winsize w; /*give the height of the console*/
 
int taille()
{
  ioctl(0, TIOCGWINSZ, &w); /*give width with w.ws_row and length with w.ws_col */
  return(0);
}
 
int rand_(int a)   /*give a random number between 0 and a*/
{
  time_t t;
  srand((unsigned)time(&t));
  return rand()%(a)+1;
}
 
int arrondi(float a)  /*round a number*/
{
  return a +0.5;
}

int mysleep(float temps)
{
	clock_t arrivee=clock()+(temps*CLOCKS_PER_SEC); // On calcule le moment où l'attente devra s'arrêter
    while(clock()<arrivee);
}

int planedisplay(int keys, int planewidth, int planelength) /*display the plane according of the position and direction*/
{
  printf("\033c"); /*clean the terminal*/
  FILE* fichier = NULL; /*initializes a poiteur*/
  switch(keys) /*open the picture according of the direction*/
  {
    case KEYBOARDU:
    fichier = fopen("upplane.pbm", "r");
    case KEYBOARDD:
    fichier = fopen("downplane.pbm", "r");
    case KEYBOARDR:
    fichier = fopen("rightplane.pbm", "r");
    case KEYBOARDL:
    fichier = fopen("leftplane.pbm", "r");
 
  }
 
   if (fichier != NULL) /*display the plane on the screen*/
    {
      int i = 0;
      int j = 0;
      int cursor;
      fseek(fichier, 7, SEEK_SET); /*moves the read curseur to don't read the first lines*/
      for(j =0;j<6;j++)  
        {
          for(i =0;i<12;i++)
        {
          cursor = fgetc(fichier); /*take off the code character of the bpm file*/
          switch(cursor) /*write a special character in the console according of the bpm file*/
            {
            case '0':
              printf(" ");
              break;
            case '1':
              printf("█");
              break;
        case '\n':
        printf("\n");
            }
         }
         }
 
        fclose(fichier); /*close the bpm file*/
    }
    else /*if we can't open the file*/
      {
    printf("\nOpening Error\n");
      }
    return 0;
}
 
 
 
int main(int argc, char *argv[])  
{
  int planewidth;
  int planelength;
  int initdirection;
  int hotkey;
  int newhotkey;
  int oldplanewidth;
  int oldplanelength;
  int oldconsolewidth;
  int oldconsolelength;
    taille(); /*give the height of the console*/
    oldconsolewidth = w.ws_row; /*save the console */
    oldconsolelength =w.ws_col;
    planewidth = rand_(w.ws_row); /*choose a random position in the console*/
    oldplanewidth = planewidth; /*save the old value*/
    planelength = rand_(w.ws_col);
    oldplanelength =planelength;
    initdirection = rand_(4); /*choose a number between 1,2,3,4*/
    switch(initdirection) /*choose the plane direction according of initdirection*/
      {
      case 1:
    newhotkey = KEYBOARDU;
      case 2:
    newhotkey = KEYBOARDR;
      case 3:
    newhotkey = KEYBOARDD;
      case 4:
    newhotkey = KEYBOARDL;
      }
 
    /*begin while*/
    while(newhotkey != KEYBOARDEXIT) /*run while the user don't tape the x keys*/
    {
      taille(); /*give the height of the console*/
      planewidth=(w.ws_row/(oldconsolewidth/oldplanewidth)); /*if the height of the console change the plane position change proportionally*/
      planewidth=arrondi(planewidth);
      planelength=(w.ws_col/(oldconsolelength/oldplanelength));
      planelength=arrondi(planelength);
      oldconsolewidth = w.ws_row; /*save the old value of the console height*/
      oldconsolelength = w.ws_col;       
      planedisplay(newhotkey, planewidth, planelength); /*call the fonction to display the plane on the console with the different parameter*/
 
     
        newhotkey = getchar(); /*take the user choice*/
        if(newhotkey!=KEYBOARDU && newhotkey!=KEYBOARDD && newhotkey!=KEYBOARDR && newhotkey!=KEYBOARDL && newhotkey!=KEYBOARDEXIT) /*if the character choose by the user is wrong we don't change the position*/
        {
      newhotkey=hotkey;
        }
        else
        {
      hotkey=newhotkey;
  		}
       switch(hotkey) /*use a switch to change the plane position according of user choice and the console borders*/
            {
            case KEYBOARDU:
              planewidth=planewidth-1;
              if (planewidth<0)
              {
              	planewidth = w.ws_row;
              }	
            case KEYBOARDD:
              planewidth=planewidth+1;
              if (planewidth>w.ws_row)
              {
              	planewidth = 0;
              }
            case KEYBOARDR:
              planelength=planelength+1;
              if (planelength>w.ws_col)
              {
              	planelength = 0;
              }
            case KEYBOARDL:
              planelength=planelength-1;
              if (planelength<0)
              {
              	planelength = w.ws_col;
              }
            }
       
    }
    return 0;
}