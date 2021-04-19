
// include stdio.h for printf
//   see `man 3 printf` for synopsis
#include <stdio.h>

// this header provides abstract helper functions for threads on
// windows (CreateThread) and POSIX threads (pthread_create)
#include "thread_helper.h"

// the number of times to increment / decrement the shared variable
//   play with this value for different effects
#define LIMIT 10000

// a static shared variable, accessed by multiple threads concurrently
//   marked volatile to prevent the compiler to make assumptions and optimizations
volatile int i = 0;

// the thread function for thread 1
//   POSIX thread functions have a type of `void*(*)(void*)`, meaning a single paramater
//   of type `void*` and a return value of `void*`. `void*` is an untyped pointer,
//   meaning a pointer to a location in memory that can't be dereferenced (followed)
//   without typing it first through a cast, like `void *p; int i = *(int*)p`
thread_helper_return_t func_a (void *arg)
{
  (void)arg;

  int x;
  for (x = 0; x < LIMIT; ++x)
    i++;
	
  return thread_helper_empty_result;
}

thread_helper_return_t func_b (void *arg)
{
  (void)arg;

  int x;
  for (x = 0; x < LIMIT; ++x)
    i--;

  return thread_helper_empty_result;
}

// the main function (program entry point)
int main(void)
{
  // prepare two variables holding the references to the worker threads
  thread_helper_t thread_a;
  thread_helper_t thread_b;
  
  // repeat forever
  while (1)
    {
      // reset the shared variable
      i = 0;

      // create the two threads
	  //    the threads will start executing immediately
	  thread_helper_create(&thread_a, &func_a);
	  thread_helper_create(&thread_b, &func_b);
	  
      // join the two threads
      //    this blocks until the threads have terminated.
	  thread_helper_join(thread_a);
	  thread_helper_join(thread_b);

      // print the result
      printf("%i\n", i);
    }

  return 0;
}
