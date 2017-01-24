char ** parse(char * scan);
int * translateCoord(char * coord);
int * translatePiece(char * piece);
int check(char ** input);

typedef struct piece{
  char* name;
  int x,y;
} piece;
