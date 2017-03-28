#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#define PGSIZE (4096)

int
thread_create(void(*start_routine)(void*), void *arg)
{
   void *stack = malloc(PGSIZE*2);
   if(stack==NULL) {
     printf(2, "Error in malloc\n");
   }
/* if((uint)stack % PGSIZE) {
     stack = stack + (4096 - (uint)stack % PGSIZE);
   }*/
  int ret_value = clone(start_routine, arg, stack);
  return ret_value;
}
 
int
thread_join()
{
  void *stack;
  int ret_value = join(&stack);
  free(stack);
  return ret_value;
}
 
 
void
lock_init(lock_t* lock) {
  lock->flag = 0;  
}
void
lock_acquire(lock_t* lock) {
  while(xchg((uint*)&lock->flag, 1) == 1);
}
 
void
lock_release(lock_t* lock) {
  lock->flag = 0;
}
 


