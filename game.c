#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
//#include "parse.h"
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
  sock.sin_port = htons(666);
  
  printf("[client?] connecting to %s\n" , host);
  i = connect(sd , (struct sockaddr *)&sock, sizeof(sock));
  
  error_check(i, "client connect");
  return sd;

}

int main(int argc, char argv[]){

  char * host;
  if (argc != 2 ) {
    printf("host not specified, conneting to 149.89.150.20\n");
    host = "149.89.150.20";
  }
  else
    host = argv[1];

  int sd;

  sd = client_connect( host );
  
  char buffer[100];
  
  while (1) {
    printf("enter message: ");
    fgets( buffer, sizeof(buffer), stdin );
    char *p = strchr(buffer, '\n');
    *p = 0;
    
    write( sd, buffer, sizeof(buffer) );
    read( sd, buffer, sizeof(buffer) );
    printf( "received: %s\n", buffer );
  }
  
  return 0;
}
