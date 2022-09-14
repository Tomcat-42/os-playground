#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define LISTEN_MAX_CLIENTS 8

/* Signal traps and cleanup */
struct sigaction sigact;

static void signal_handler(int);
static void cleanup(void);
void init_signals(void);
void panic(const char *msg, ...);

/* Global descriptors */
int listen_fd = 0;
int conn_fd = 0;

char *progname;

int main(int argc, char *argv[]) {
  struct sockaddr_in serv_addr;
  int listen_port;

  char send_buffer[BUFFER_SIZE + 1];
  time_t ticks;

  atexit(cleanup);
  init_signals();

  if (argc != 2) {
    printf("usage: %s <Listen Port>\n", argv[0]);
    exit(1);
  }

  progname = argv[0];
  listen_port = strtol(argv[1], NULL, 10);

  /*
   * unnammed socker inside the kernel
   * socket() returns the descriptor of the socket
   * the first argument is the address family
   */
  listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serv_addr, 0, sizeof(serv_addr));
  memset(send_buffer, 0, sizeof(send_buffer));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(listen_port);

  /*
   * bind() binds the address to the socket
   */
  bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

  /*
   * listen() marks the socket as passive
   * the second argument is the backlog
   */
  listen(listen_fd, LISTEN_MAX_CLIENTS);

  printf(":: Server is listening on 127.0.0.1:%d\n\n", listen_port);

  for (;;) {
    /* accept() returns the descriptor of client request
     * after the 3-way handshake the first argument is
     * the descriptor of the socket.
     */
    conn_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);

    printf(":: Client connected\n");

    /* current epoch */
    ticks = time(NULL);
    snprintf(send_buffer, sizeof(send_buffer), "%.24s\r\n", ctime(&ticks));

    printf(":: Sending: %s\n\n", send_buffer);

    /* Write the date to the client */
    write(conn_fd, send_buffer, strlen(send_buffer));

    close(conn_fd);
    sleep(1);
  }

  printf(":: Server is shutting down\n");
  close(listen_fd);

  exit(0);
}

void init_signals(void) {
  sigact.sa_handler = signal_handler;
  sigemptyset(&sigact.sa_mask);
  sigact.sa_flags = 0;

  if (sigaction(SIGINT, &sigact, NULL) == -1) {
    panic("sigaction");
  }
}

static void signal_handler(int sig) {
  switch (sig) {
  case SIGINT:
    panic(":: SIGINT Received\n");
    break;
  default:
    panic(":: Unknown signal Received\n");
  }
}

void panic(const char *msg, ...) {
  va_list ap;

  va_start(ap, msg);
  vfprintf(stderr, msg, ap);
  va_end(ap);

  exit(-1);
}

void cleanup(void) {
  sigemptyset(&sigact.sa_mask);
  close(listen_fd);
  close(conn_fd);
}
