#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


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

int * translateCoord(char * input)  {

  int letter;
  int num;
  
  letter = tolower(input[0]);
  //printf("%d\n",letter);
  num = input[1];
  
  letter -= 97;
  // printf("%d\n",letter);
  num -= 49;

  int * c = (int *) malloc(sizeof(int) * 2);
    
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

  int * d = (int *) malloc(sizeof(int) *2);
  
  d[0] = color;
  d[1] = type;
  
  free(temp);
  return d;

}

int check(char ** input) {

  int *piece;
  int *from;
  int *to;

  piece = translatePiece(input[0]);
  from = translateCoord(input[1]);
  to = translateCoord(input[2]);
  
  printf("color: %d; piece:%d; to:%d,%d; from:%d,%d;",piece[0], piece[1], from[0],from[1],to[0],to[1]);



  free(piece);
  free(from);
  free(to);

  return 0;

}

int main(int argc, char argv[]) {
  char buffer[1000];

  printf("type");
  fgets(buffer, sizeof(buffer), stdin);
  char ** inputs = parse(buffer);
  check(inputs);
  return 0;

  /*
  char * input = "f4";
  int * res;
  //  printf("%s\n", input);

  res = translateCoord(input);
  // printf("%d,%d\n",res[0], res[1]);
  
  char input2[5] = "Win\0";
  int * piece;
  //  printf("%s\n", input);

  piece = translatePiece(input2);
  //  printf("%d,%d\n", piece[0], piece[1]);
    
  free(res);
  free(piece);
  */


}
