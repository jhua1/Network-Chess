#include <stdio.h>
#include <stdlib.h>

typedef struct {

  char * name;
  char coord[2];
  int color; //0: white, 1: black
  
} Piece;

char * move(Piece piece, char dest[]) {
  
  char curCoord[2];
  curCoord = piece.coord;
  piece.coord = dest;
  return curCoord;

}

char * check(Piece piece, char dest[]) {
  
  char * name = piece.name;
  
  //  if (strcmp(name, "pn"))
    //    if (
}

void add(pieces) {

  

}
