#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
 
#define KEYBOARDUP 122 /*variable system for the keys*/
#define KEYBOARDDOWN 115
#define KEYBOARDRIGHT 100
#define KEYBOARDLEFT 113
#define KEYBOARDEXIT 120
 
 
struct winsize w; /*give the height of the console*/
 
int taille()
{
  ioctl(0, TIOCGWINSZ, &w); /*give width with w.ws_row and length with w.ws_col */
  w.ws_row=w.ws_row-1;
  return(0);
}
 
int rand_(int a)   /*give a random number between 0 and a*/
{
  time_t t;
  srand((unsigned)time(&t));
  return rand()%(a)+1;
}
 
 
int mysleep(float temps)
{
    clock_t arrivee=clock()+(temps*CLOCKS_PER_SEC); /*calculating the waiting time*/
    while(clock()<arrivee);
}
 
int planedisplay(int keys, int planewidth, int planelength) /*display the plane according of the position and direction*/
{
    printf("\033c"); /*clean the terminal*/
  int consoleboard[w.ws_row][w.ws_col];
  int planeboard[6][6];
  int l = 0;
  int k = 0;
  int i = 0;
  int j;
  int y;

  for (l=0; l<w.ws_row;l++) /*initializes the values in the board*/
  {
    for (k=0; k<w.ws_col; k++)
    {
        consoleboard[l][k]=0;
    }
  }
  FILE* fichier = NULL; /*initializes a poiteur*/
  switch(keys) /*open the picture according of the direction*/
  {
    case KEYBOARDUP:
    fichier = fopen("upplane.pbm", "r");
break;
    case KEYBOARDDOWN:
    fichier = fopen("downplane.pbm", "r");
break;
    case KEYBOARDRIGHT:
    fichier = fopen("rightplane.pbm", "r");
break;
 case KEYBOARDLEFT:
 fichier = fopen("leftplane.pbm", "r");
break;
  }
 
   if (fichier != NULL) /*get the .bpm in a board*/
    {
     
      int cursor;
   
      fseek(fichier, 7, SEEK_SET); /*moves the read curseur to don't read the first lines*/
      for(j =0;j<6;j++)  
        {
      y = 0;
          for(i =0;i<12;i++)
        {
          cursor = fgetc(fichier); /*take off the code character of the bpm file*/
          switch(cursor) /*write a special character in the console according of the bpm file*/
            {
            case '0':
              planeboard[j][y]=0;
          y++;
              break;
            case '1':
              planeboard[j][y]=1;
          y++;
              break;
       
            }
         }
         }
 
        fclose(fichier); /*close the bpm file*/
    }
    else /*if we can't open the file*/
      {
    printf("\nOpening Error\n");
      }
    /*fonction intégration dans la console*/
      for(j=0;j<6;j++)  
        {
          for(i=0;i<6;i++)
        {
            if (planewidth+j>=w.ws_row && planelength+i>=w.ws_col)
            {
                consoleboard[planewidth+j-w.ws_row][planelength+i-w.ws_col] = planeboard[j][i];
            }
            if(planewidth+j>=w.ws_row && planelength+i<=w.ws_col)/*!!!!*/
            {
                consoleboard[planewidth+j-w.ws_row][planelength+i] = planeboard[j][i];
            }
            if(planewidth+j<=w.ws_row && planelength+i>=w.ws_col)
            {
                consoleboard[planewidth+j][planelength+i-w.ws_col] = planeboard[j][i];
            }
            if(planewidth+j<=w.ws_row && planelength+i<=w.ws_col)
            {
              consoleboard[planewidth+j][planelength+i] = planeboard[j][i];
            }
         }
         }
    for (l=0; l<w.ws_row;l++) /*initializes the values in the board*/
  {
    for (k=0; k<w.ws_col; k++)
    {
        int character = consoleboard[l][k];
        if(character==1)
        {
            printf("█");
        }
        else
        {
      printf(" ");
        }
    }
  }  
    return 0;
}
 
 
 
int main(int argc, char *argv[])  
{
  int planewidth;
  int planelength;
  int initdirection;
  char hotkey;
  char newhotkey;
  int oldplanewidth;
  int oldplanelength;
  int oldconsolewidth;
  int oldconsolelength;
float floatplanew;
float floatplanel;
  taille();
  oldconsolewidth = w.ws_row;
  oldconsolelength = w.ws_col;
  planewidth = rand_(w.ws_row);
  planelength = rand_(w.ws_col);
  oldplanewidth=planewidth;
  oldplanelength=planelength;
  initdirection = rand_(4);
switch(initdirection)
{
 case 1:
newhotkey=KEYBOARDUP;
break;
 case 2:
newhotkey=KEYBOARDDOWN;
break;
 case 3:
newhotkey=KEYBOARDRIGHT;
break;
 case 4:
newhotkey=KEYBOARDLEFT;
break;
}
 
    /*begin while*/
  while(newhotkey != KEYBOARDEXIT) /*run while the user don't tape the x keys*/
       {
 
   taille(); /*give the height of the console*/
  floatplanew=(w.ws_row*planewidth/oldconsolewidth); /*if the height of the console change the plane position change proportionally*/
planewidth=(int) floatplanew;
 floatplanel=(planelength*w.ws_col/oldconsolelength);
planelength=(int) floatplanel;
       
      /*call the fonction to display the plane on the console with the different parameter*/
planedisplay(newhotkey, planewidth, planelength);
// mysleep(0.1);
oldconsolewidth = w.ws_row; /*save the old value of the console height*/
oldconsolelength = w.ws_col;
 
        newhotkey = getchar(); /*take the user choice*/
       while(getchar()!='\n');
 
    if(newhotkey!=KEYBOARDUP && newhotkey!=KEYBOARDDOWN && newhotkey!=KEYBOARDRIGHT && newhotkey!=KEYBOARDLEFT && newhotkey!=KEYBOARDEXIT) /*if the character choose by the user is wrong we don't change the position*/
       {
  newhotkey=hotkey;
     }
    else
     {
 hotkey=newhotkey;
      }
     switch(newhotkey) /*use a switch to change the plane position according of user choice and the console borders*/
               {
           case KEYBOARDUP:
            planewidth=planewidth-1;
    if (planewidth<=0)
             {
              planewidth = w.ws_row-1;
            }
           break;
           case KEYBOARDDOWN:
          planewidth=planewidth+1;
            if (planewidth>=w.ws_row)
            {
              planewidth = 0;
            }
break;
        case KEYBOARDRIGHT:
            planelength=planelength+1;
           if (planelength>=w.ws_col)
           {
             planelength = 1;
            }
break;
         case KEYBOARDLEFT:
          planelength=planelength-1;
            if (planelength<=0)
              {
                planelength = w.ws_col-1;
              }
break;
            }
       }
    return 0;
}