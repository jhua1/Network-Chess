#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct piece{
  char* name;
  int x,y,color;
} piece;


char ** parse(char * scan) {
  
  *strchr(scan, '\n') = 0;
  
  char ** input = (char **) calloc(sizeof(char *), 10);
  
  int x = 0;
  while (input[x] = strsep(&scan, " ")) {
    if (strlen(input[x]))
      x++;
  }
  
  return input;

}

int * translateCoord(char * coord)  {

  int letter;
  int num;
  
  letter = tolower(coord[0]);
  num = coord[1];
  
  letter -= 97;
  num -= 49;

  int *c = (int *) malloc(sizeof(int) * 2);
    
  c[0] = letter;
  c[1] = num;

  
  return c;
}


int * translatePiece(char * piece) { 

  int color = -1;
  int type = -1;
  
  char defColor = 'b';

  if (tolower(piece[0]) == defColor)
    color = 0;
  else 
    color = 1;
  
  int i = 1;
  char * temp;
  temp = malloc(sizeof(char) * 3);

  temp[0] = piece[1];
  temp[1] = piece[2];


  if (strcmp(temp, "pn") == 0)
    type = 0;
  if (strcmp(temp, "bs") == 0)
    type = 1;
  if (strcmp(temp, "kn") == 0)
    type = 2;
  if (strcmp(temp, "rk") == 0)
    type = 3;
  if (strcmp(temp, "qn") == 0)
    type = 4;
  if (strcmp(temp, "kg") == 0)
    type = 5;

  int *d = (int *) malloc(sizeof(int) *2);
  
  d[0] = color;
  d[1] = type;
  
  free(temp);
  return d;

}

int checkMoves(char * piece, int * from, int * to){
  
  

}

int check(char ** input) {
  
  int *piece;
  int *from;
  int *to;

  piece = translatePiece(input[0]);
  from = translateCoord(input[1]);
  to = translateCoord(input[2]);
  
  printf("piece, %d, %d",piece[0], piece[1]);

  free(piece);
  free(from);
  free(to);

  return 0;

}

void printboard(piece same[8][8]){
  int j,k;
  for ( j=0 ; j < 8; j++){
    for ( k=0; k < 8; k++){
      printf(" %s ", same[j][k].name);
    }
    printf("\n");
  }
}
