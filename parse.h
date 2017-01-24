char ** parse(char * scan);

char * translate(char * input);
int check(char ** input, char ** board);

typedef struct piece{
  char* name;
  int x,y;
} piece;
