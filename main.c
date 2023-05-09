#include <stdio.h> // include printf(), scanf()
#include <sys/socket.h> // подключаем ф-л сокетов. А как на винде будет?
#include <unistd.h> // подключаем ф-ции линукса для low-level работы
#include <stdlib.h> // general programming functions (memory, strings, random numbers)
#include <netinet/in.h>
#include <string.h>

int main() {
  // CREATE SOCKET FILE DESCRIPTOR
  int sockFD;
  if ((sockFD = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
    perror("cannot create socket");
    return -1;
  }

  // CREATE ADDRESS AND BIND SOCKET TO ADDRESS
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);
  memset(address.sin_zero, '\0', sizeof(address.sin_zero));
  if (bind(sockFD, (struct sockaddr*)&address, sizeof(address)) < 0) {
    perror("bind failed");
    return -1;
  }

  // LISTEN
  if (listen(sockFD, 10) < 0) {
    perror("In listen");
    return -1; 
  }

  int newSockFD;
  int addrlen = sizeof(address);
  while (1) {
    printf("\n+++++++ Waiting for new connection ++++++++\n\n");
    if ((newSockFD = accept(sockFD, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
      perror("In accept");
      return -1;
    }

    printf("past new socket\n");

    char buffer[30000] = {0};
    long valread = read(newSockFD, buffer, 30000);
    printf("%s\n", buffer);
    char* hello = "Hello from the server";
    write(newSockFD, hello, strlen(hello));
    printf("------------------Hello message sent-------------------\n");
    close(newSockFD);
  }

  printf("hello, working fine... \n");
  return 0;
}
