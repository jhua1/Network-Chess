#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>


int server_setup() {

  int sd;
  int i;

  sd = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in sock;
  printf("socket created\n");
  sock.sin_family = AF_INET;
  sock.sin_addr.s_addr = INADDR_ANY;
  sock.sin_port = htons(7032);
  printf("stuff made");
  i = bind(sd, (struct sockaddr *)&sock, sizeof(sock));
  printf("binding to socket\n");
  return sd;
  

}


int server_connect(int sd) {

  int connection, i;

  i = listen(sd, 1);

  struct sockaddr_in sock1;
  unsigned int sock1_len = sizeof(sock1);
  connection = accept(sd, (struct sockaddr *)&sock1, &sock1_len);

  printf("[??] connected to %s\n", inet_ntoa(sock1.sin_addr));

  return connection;
 

}

int main() {
  printf("!\n");
  int sd, connection;

  printf("?\n");
  sd = server_setup();
  char buffer[100];    
  while (1) {
    
    connection = server_connect( sd );


    printf("%s\n", buffer);
    
    read( sd, &buffer, sizeof(buffer) ) ;
    
    printf("[SERVER %d] received: %s\n", getpid(), buffer );
        
  }
  return 0;
}
