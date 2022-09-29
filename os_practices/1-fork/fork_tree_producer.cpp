#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <cstring>
#include <deque>
#include <fcntl.h>
#include <iostream>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <sys/mman.h>

#define NAME "fork_tree"
#define MAX_DEPTH 1024

/*
 * Creates a shared memory segment and returns a descriptor to it.
 */
int shm_create(const char *name) {
  int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  if (fd == -1) {
    perror("shm_open");
    exit(1);
  }
  return fd;
}

/*
 * Maps a shared memory segment into the address space of the calling process.
 * and fill it with a new queue.
 */
void *shm_map(int fd, size_t size) {
  std::deque<pid_t> queue(size, 0x00);
  if (ftruncate(fd, sizeof(queue)) == -1) {
    perror("ftruncate");
    exit(1);
  }
  void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  if (ptr == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  /* Copy the contents of the queue to the memory region*/
  memcpy(ptr, &queue, sizeof(queue));

  return ptr;
}

/*
 * This programs makes a binary tree of processes.
 * The root process forks two children, which fork two children each, and so on.
 * The number of levels in the tree is given as a command-line argument.
 * This programs uses a pre-order traversal to print the process tree, with each
 * PID being saved in a queue in a shared memory segment.
 * */
int main(int argc, char *argv[]) {
  unsigned long long int depth;

  pid_t pid;

  // shm segment and pointer to the stack
  int shmd;
  std::deque<pid_t> *shm_ptr;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <depth>\n", argv[0]);
    exit(1);
  }

  depth = strtoull(argv[1], NULL, 10);

  // create a shared memory segment
  shmd = shm_create(NAME);
  shm_ptr = (std::deque<pid_t> *)shm_map(shmd, int(pow(2, depth)));

  // print queue size
  std::cout << "queue size: " << shm_ptr->size() << std::endl;

  // root node
  // shm_ptr->push_back(getpid());
  std::cout << "Root: " << getpid() << std::endl;

  // create the process tree
  for (int i = 1; i < depth; i++) {

    fflush(stdout);
    fflush(stderr);
    if ((pid = fork()) == -1) {
      perror("fork");
      exit(1);
    }

    if (pid == 0) {
      // child
      wait(NULL);
      std::cout << "Left " << i << " " << getpid() << std::endl;
      // shm_ptr->push_back(getpid());
      sleep(1);
    } else {
      // parent
      wait(NULL);
      std::cout << "Right " << i << " " << getpid() << std::endl;
      // shm_ptr->push_back(getpid());
      sleep(1);
    }
  }

  // sleep(1);

  // clean up
  // shm_unlink(NAME);

  return EXIT_SUCCESS;
}
