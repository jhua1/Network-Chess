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

void printboard(piece same[8][8]){
  int j = 0;
  int k = 0;
  for ( j ; j < 8; j++){
    for ( k; k < 8; k++){
      printf("%s ", same[j][k].name);
    }
    printf("\n");
  }
}

int main() {

  //==================creating board==========================
  
  piece board[8][8];
  //left side/black side
  int r = 0;
  int c = 0;
  for( r; r < 8; r++){
    for ( c; c < 2; c++){
      board[r][c].x = r;
      board[r][c].y = c;
      board[r][c].color = 0;
      if ( c == 1){
	board[r][c].name = "pn";
      }
    }
  }
  //middle
  r = 0;
  c = 2;
  for( r; r < 8; r++){
    for( c; c < 6; c++){
      board[r][c].name = "--";
      board[r][c].x = r;
      board[r][c].y = c;
      board[r][c].color = 0;
    }
  }
  //right/white
  r = 0;
  c = 6;
  for( r; r < 8; r++){
    for( c; c < 8; c++){
      board[r][c].x = r;
      board[r][c].y = c;
      board[r][c].color = 1;
      if( c == 6)
	board[r][c].name = "pn";    
    }
  }
  
  //black nonpawn
  board[0][0].name = "rk";
  board[1][0].name = "kn";
  board[2][0].name = "bs";
  board[3][0].name = "qn";
  board[4][0].name = "kg";
  board[5][0].name = "bs";
  board[6][0].name = "kn";
  board[7][0].name = "rk";
  //white nonpawn
  board[0][7].name = "rk";
  board[1][7].name = "kn";
  board[2][7].name = "bs";
  board[3][7].name = "qn";
  board[4][7].name = "kg";
  board[5][7].name = "bs";
  board[6][7].name = "kn";
  board[7][7].name = "rk";
  //==========================end board===========================
  
  printboard(board);

  int sd, connection;

  sd = server_setup();
  printf("server is setup\n");
  char buffer[1000];
  connection = server_connect( sd );
  printf("connection is made\n");

  

  
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
