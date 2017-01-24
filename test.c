#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int * translateCoord(char * input)  {

  int letter;
  int num;
  
  letter = tolower(input[0]);
  num = input[1];
  

  
  letter -= 97;
  num -= 49;

  int * c;
    
  c[0] = letter;
  c[1] = num;

  
  return c;
}

int * translatePiece(char * piece) { 

  int color = 0;
  int type = 0;
  
  char defColor = 'b';

  if (tolower(piece[0]) == defColor)
    color = 0;
  else 
    color = 1;
  /*
  int i = 0;
  char * temp = (char *) malloc(strlen(&piece[1]));

  while(piece[i]) {
    temp[i-1] = tolower(piece[i]);
    i++;
    printf("%s",temp);
  }
   
  if (strcmp(temp, "pn") == 0)
    type = 0;
  if (strcmp(temp, "bs"))
    type = 1;
  if (strcmp(temp, "kn"))
    type = 2;
  if (strcmp(temp, "rk"))
    type = 3;
  if (strcmp(temp, "qn"))
    type = 4;
  if (strcmp(temp, "kg"))
    type = 5;
  */

  int p = 1;
  d[0] = 1;
  d[1] = 1;
  

  return d;


}


int main() {

  char * input = "H1";
  int * res;

  printf("%s\n", input);
  res = translateCoord(input);
  printf("%d,%d\n",res[0], res[1]);
  


  char  input2[5] = "Wpn";
  printf("input is set to White pawn\n");
  int * piece = (int *) malloc(sizeof(int));
  printf("malloc the piece\n");
  piece = translatePiece(input2);

  
  /*


  piece = translatePiece(input2);
  
  
  printf("%d,%d\n", piece[0], piece[1]);

  //printf("%d,%d\n", piece[0], piece[1]);

  //free(piece);
  return 0;
  */
}
