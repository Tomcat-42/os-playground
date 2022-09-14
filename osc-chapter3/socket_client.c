#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  int socket_fd = 0, n = 0;
  char recv_buffer[BUFFER_SIZE];
  unsigned int server_port;

  struct sockaddr_in serv_addr;

  if (argc != 3) {
    printf("usage: %s <IP address> <Port>\n", argv[0]);
    exit(1);
  }

  server_port = strtol(argv[2], NULL, 10);

  memset(recv_buffer, 0, sizeof(recv_buffer));

  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Error: Could not create socket \n");
    exit(1);
  }

  memset(&serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(server_port);

  if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
    printf("Error: inet_pton error\n");
    exit(1);
 }

  /* Tries to connect */
  if (connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <
      0) {
    close(socket_fd);
    printf("Error: Connection Failed\n");
    exit(1);
  }

  printf(":: Connected to server, readind data...\n\n");

  /* Reads the date from the server */
  while ((n = read(socket_fd, recv_buffer, BUFFER_SIZE)) > 0) {
    recv_buffer[n] = 0;
    if (fputs(recv_buffer, stdout) == EOF) {
      printf("Error: fputs error\n");
      exit(1);
    }
  }

  if (n < 0) {
    printf("\nError: Read error\n");
  }

  printf("\n:: Closing connection...\n");
  close(socket_fd);

  return 0;
}
