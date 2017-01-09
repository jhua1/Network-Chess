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
/*
void main() {

  char read[256];
  char * s = read;
  fgets(read, sizeof(read), stdin);
  char ** inputs = parse(read);
  printf("%s\n %s\n", inputs[0], inputs[1]);

}
*/
