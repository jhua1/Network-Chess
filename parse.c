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

int * translate(char * input) {

  int x = 
  int c[2] = (int *) malloc(sizeof(char *), 2);
  
  c[0] = 

}
