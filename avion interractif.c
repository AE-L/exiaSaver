#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#define KEYBOARDU 8
#define KEYBOARDD 2
#define KEYBOARDR 6
#define KEYBOARDL 4

struct winsize w;
 
int taille()
{
  ioctl(0, TIOCGWINSZ, &w); /*give widht with w.ws_row and length with w.ws_col */
  return(0);
}

int planedisplay(char fill, int position, int w)
{
  printf("\033c"); /*clean the terminal*/
  char cursor = a;
  char picture
  switch(fill) /*open the right picture choose by the user*/
  {
    case 'u':
    FILE* uplane = NULL;
    uplane = fopen("upplane.pbm", "r");
    picture = uplane
    case 'd':
    FILE* dplane = NULL;
    dplane = fopen("downplane.pbm", "r");
    picture = dplane
    case 'r':
    FILE* rplane = NULL;
    rplane = fopen("rightplane.pbm", "r");
    picture = rplane
    case 'l':
    FILE* uplane = NULL;
    uplane = fopen("leftplane.pbm", "r");

  }

   if (picture != NULL) /*display the plane on the screen*/
    {
      int i = 0;
      int j = 0;
      fseek(picture, 7, SEEK_SET);
      for(j =0;j<6;j++)
        {
          for(i =0;i<12;i++)
        {
          cursor = fgetc(picture); /*take off the code character of the bpm file*/
          switch(cursor) /*write a special character in the console*/
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
 
        fclose(picture); /*close the bpm file*/
    }
    else
      {
    printf("\nErreur d'ouverture\n");
      }
    return 0;
}
 
int main(void)  
{
    taille();
    p.widht = rand_a_b(0, w.ws_row) /*choose a random position in the console*/
    p.length = rand_a_b(0, w.ws_col)
    char hotkey 
    char newhotkey
    
    while(newhotkey != x)
    {
    	planedisplay(newhotkey, p, w)
    	newhotkey = getchar();
    	if(newhotkey!=8 && newhotkey!=6 && newhotkey!=2 && newhotkey!=4 && newhotkey!=x) /*if the character choose by the user is wrong we */
    	{
    		newhotkey=hotkey
    	}
    	else 
    	{
    		hotkey=newhotkey
    	}
    }
    return 0;
}