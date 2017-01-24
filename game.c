#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "parse.h"
//#include "piece.h"

void error_check(int i, char *s) {
  if (i < 0) {
    printf("%d\n", i);
    printf("[%s] error %d: %s\n", s, errno, strerror(errno));
    exit(1);

  }

}

int client_connect(char * host) {

  int sd, i;

  sd = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  inet_aton(host, &(sock.sin_addr));
  sock.sin_port = htons(7032);
  
  printf("[client] connecting to %s\n" , host);
  i = connect(sd , (struct sockaddr *)&sock, sizeof(sock));
  
  error_check(i, "client connect");
  return sd;

}

void printbuffer(char * buffer){
  char  s[2] = " ";
  char * token;
  int j,k;
  token = strtok(buffer, s);
  while(token != NULL){
    for(k = 0; k <8; k++){
      for(j = 0; j <8; j ++){
	printf("%s ", token);
	token = strtok(NULL , s);
      }
      printf("\n");
    }
  }
  
}

int main(int argc, char argv[]){
  char host[1000];
  printf("enter the ip of the server you wish to play against:");
  fgets(host, sizeof(host), stdin);
  char *s = strchr(host, '\n');
  *s = 0;
  int sd;

  sd = client_connect( host );
  char buffer[1000];
  while(1){
    //printboard();
    printf("make your move: ");
    fgets( buffer, sizeof(buffer), stdin );
    char *p = strchr(buffer, '\n');
    *p = 0;
    
    write( sd, buffer, sizeof(buffer) );//sends the move over to the server
    printbuffer(buffer);
    printf("waiting for opponent...\n");
    read( sd , buffer, sizeof(buffer));
    printf("move confirmed, this the current board state:\n");
    printbuffer(buffer); 
  }
  
  return 0;

}
