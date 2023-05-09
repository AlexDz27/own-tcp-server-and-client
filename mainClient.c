#include <stdio.h> // include printf(), scanf()
#include <sys/socket.h> // подключаем ф-л сокетов
#include <unistd.h> // подключаем ф-ции линукса для low-level работы
#include <stdlib.h> // general programming functions (memory, strings, random numbers)
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
  // CREATE SOCKET FILE DESCRIPTOR
  int sockFD;
  if ((sockFD = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
    printf("Socket creation error \n");
    return -1;
  }

  // CREATE ADDRESS
  struct sockaddr_in address;
  memset(&address, '0', sizeof(address)); // TODO: ?
  address.sin_family = AF_INET;
  address.sin_port = htons(8080);
  if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  // CONNECT
  if (connect(sockFD, (struct sockaddr *)&address, sizeof(address)) < 0) {
    printf("\nConnection Failed \n");
    return -1;
  }

  // SEND MESSAGE
  char hello[] = "Hello from client";
  send(sockFD, hello, strlen(hello), 0);
  printf("Hello message sent\n");
  char buffer[1024] = {0};
  long valread = read(sockFD, buffer, 1024); // TODO: мы пишем long, хотя тип read ssize_t...
  printf("%s\n", buffer);

  return 0;
}
