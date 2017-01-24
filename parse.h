typedef struct piece{
  char* name;
  int x,y,color;
} piece;


char ** parse(char * scan);
int * translateCoord(char * coord);
int * translatePiece(char * piece);
int checkMoves(int * pieces, int * from, int * to, piece board[8][8]);
int move(char ** input, piece board[8][8]);
void printboard(piece same[8][8]);
