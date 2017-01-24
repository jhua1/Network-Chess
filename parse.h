char ** parse(char * scan);

char * translate(char * input);
int check(char ** input, char ** board);

typedef struct {
  char* name;
  int x,y,color;
} piece;
