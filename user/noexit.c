/* no exit call in thread, should trap at bogus address */
#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;
int global = 1;

#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

void worker(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();

   int arg = 42;
   void *arg_ptr = &arg;
   int thread_pid = thread_create(worker, arg_ptr);
   printf(1, "in nnoexit%d\n", thread_pid);
   assert(thread_pid > 0);
   printf(1, "1111\n");
   int join_pid = thread_join();
   printf(1, "%d\n", join_pid);
   assert(join_pid == thread_pid);
   assert(global == 2);

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   int arg = *(int*)arg_ptr;
   printf(1, "in function\n");
   assert(arg == 42);
   assert(global == 1);
   global++;
   // no exit() in thread
}

