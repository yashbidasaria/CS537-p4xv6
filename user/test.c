#include "types.h"
#include "user.h"

//int i = 1;
void
worker(void *arg)
{
//  i = 0;
  //*(int*)arg++;
  printf(1, "arg in worker %d\n", *(int*)arg);
  exit();
}
int
main(int argc, char *argv[])
{
  int arg = 5;
  int tid = thread_create(worker, &arg);
  printf(1, "thread id = %d\n", tid);
//  while(i);
  return 0;
}
