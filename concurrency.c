
// include stdio.h for printf
//   see `man printf` for synopsis
#include <stdio.h>

// include pthread.h for pthread_create and pthread_join
//   see `man pthread` or `man pthread.h` for synopsis
#include <pthread.h>

// the number of times to increment / decrement the shared variable
//   play with this value for different effects
#define LIMIT 10000

// a static shared variable, accessed by multiple threads concurrencly
//   marked volatile to prevent the compiler to make assumptions and optimizations
volatile int i = 0;

// the thread function for thread 1
//   thread functions have a type of `void*(*)(void*)`, meaning a single paramater
//   of type `void*` and a return value of `void*`. `void*` is an untyped pointer,
//   meaning a pointer to a location in memory that can't be dereferenced (followed)
//   without typing it first through a cast, like `void *p; int i = *(int*)p`
void* func_a (void *arg)
{
  (void)arg;

  int x;
  for (x = 0; x < LIMIT; ++x)
    i++;

  return NULL;
}

// the thread function for thread 2
void* func_b (void *arg)
{
  (void)arg;

  int x;
  for (x = 0; x < LIMIT; ++x)
    i--;

  return NULL;
}

// the main function (program entry point)
int main(void)
{
  // prepare two variables holding the references to the worker threads
  pthread_t thread_a;
  pthread_t thread_b;

  // repeat forever
  while (1)
    {
      // reset the shared variable
      i = 0;

      // create the two threads
      pthread_create(&thread_a, NULL, &func_a, NULL);
      pthread_create(&thread_b, NULL, &func_b, NULL);

      // join the two threads
      //    this blocks until the threads have terminated.
      pthread_join(thread_a, NULL);
      pthread_join(thread_b, NULL);

      // print the result
      printf("%i\n", i);
    }

  return 0;
}
