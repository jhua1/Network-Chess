#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "parse.h"

int server_setup() {
  
  int sd;
  int i;

  sd = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in sock;
  printf("socket created\n");
  sock.sin_family = AF_INET;
  sock.sin_addr.s_addr = INADDR_ANY;
  sock.sin_port = htons(7032);
  printf("stuff made\n");
  i = bind(sd, (struct sockaddr *)&sock, sizeof(sock));
  printf("binding to socket\n");
  return sd;
  

}


int server_connect(int sd) {

  int connection, i;
  printf("listening\n");
  i = listen(sd, 1);

  struct sockaddr_in sock1;
  unsigned int sock1_len = sizeof(sock1);
  connection = accept(sd, (struct sockaddr *)&sock1, &sock1_len);
  printf("connection accepted\n");
  printf("[??] connected to %s\n", inet_ntoa(sock1.sin_addr));
  printf("potato\n");
  return connection;
 

}

int main() {

  int sd, connection;

  sd = server_setup();
  printf("server is setup\n");
  char buffer[1000];
  connection = server_connect( sd );
  printf("connection is made\n");
  //creating board;
  piece board[8][8];

  
  
  while(1){

    //printboard();

    printf("waiting for opponent to make a move...\n");
    read(connection, buffer, sizeof(buffer));//reads the opponent's move
    //process(buffer); should take in the move which is in buffer and update the board accordingly
    //process should also put the board state into the buffer so that we can send it to the client
    //printboard();
    printf("%s\n" , buffer);
    write(connection, buffer, sizeof(buffer));//sends over the board state to client
    printf("make your move:");
    fgets(buffer, sizeof(buffer), stdin);
    char *p = strchr(buffer, '\n');
    *p = 0;
    //buffer now contains the server's move
    //process(buffer); //updates the board according to the server's move
    //printboard();
    write(connection, buffer, sizeof(buffer)); //writes the post-server-move board state to the cleint
    

  }
  
  close(connection);
 
  return 0;
}
