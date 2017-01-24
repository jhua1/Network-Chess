#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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

  int * c;
    
  c[0] = letter;
  c[1] = num;

  
  return c;
}

int * translatePiece(char * piece) {

  int piece;
  int color;
  


}

int checkMoves(char * piece, int * from, int * to){
  
  

}

int check(char * input) {
  
  int from[2];
  int to[2];

  from = translate(input[1]);
  to = translate(input[2]);

  return 0;

}
