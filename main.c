#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

void error(char* msg) {
  printf("Error: %s\n", msg);
  exit(1);
}

int main(int argc, char* argv[]){
  if(argc < 3) error("Too few arguments!");

  int fd, s;
  struct addrinfo hints, *res, *rp;
  
  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_INET; // ipv4 only
  hints.ai_socktype = SOCK_STREAM; // tcp only yet
  hints.ai_protocol = 0; // any protocol
   
  s = getaddrinfo(argv[1], argv[2], &hints, &res);
  if(s != 0){
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    error("Erro: Nao foi possivel resolver o dominio!");
  }

  // try each item in list of getaddrinfo result 
  for (rp = res; rp != NULL; rp = rp->ai_next) {
     fd = socket(rp->ai_family, rp->ai_socktype,
                  rp->ai_protocol);
     if (fd == -1)
         continue;

     if (connect(fd, rp->ai_addr, rp->ai_addrlen) != -1)
         break;                  /* Success */

   }

  freeaddrinfo(res);

  if(rp == NULL){
    error("Could not connect!");
  }

  return 0;
}
