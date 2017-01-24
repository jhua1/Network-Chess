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
  int j,k;
  for ( j=0 ; j < 8; j++){
    for ( k=0; k < 8; k++){
      printf("%s ", same[j][k].name);
    }
    printf("\n");
  }
}

int main() {

  //==================creating board==========================
  
  piece board[8][8];
  //left side/black side
  int r,c;
  for( r = 0; r < 8; r++){
    for ( c = 0; c < 2; c++){
      board[r][c].x = r;
      board[r][c].y = c;      
      if ( c == 1){
	board[r][c].name = "bpn";
      }
    }
  }
  //middle
  
  for( r = 0; r < 8; r++){
    for( c = 2; c < 6; c++){
      board[r][c].name = "--";
      board[r][c].x = r;
      board[r][c].y = c;
    }
  }
  //right/white
  for( r = 0; r < 8; r++){
    for( c = 6; c < 8; c++){
      board[r][c].x = r;
      board[r][c].y = c;
      if( c == 6)
	board[r][c].name = "wpn";    
    }
  }
  
  //black nonpawn
  board[0][0].name = "brk";
  board[1][0].name = "bkn";
  board[2][0].name = "bbs";
  board[3][0].name = "bqn";
  board[4][0].name = "bkg";
  board[5][0].name = "bbs";
  board[6][0].name = "bkn";
  board[7][0].name = "brk";
  //white nonpawn
  board[0][7].name = "wrk";
  board[1][7].name = "wkn";
  board[2][7].name = "wbs";
  board[3][7].name = "wqn";
  board[4][7].name = "wkg";
  board[5][7].name = "wbs";
  board[6][7].name = "wkn";
  board[7][7].name = "wrk";
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
