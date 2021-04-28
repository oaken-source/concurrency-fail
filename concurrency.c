
#include <stdio.h>

// this custom header provides portable functions for Windows and POSIX threads
#include "thread_helper.h"

// define the number of times to increment / decrement the shared variable
#define INCREMENTS 100000

// this is a static shared variable, accessed by multiple threads concurrently
volatile int i = 0;

// this is the thread function for thread 1
//
//   POSIX thread functions have a type of `void*(*)(void*)`, meaning a single
//   parameter of type `void*` and a return value of `void*`. `void*` is an
//   untyped pointer, meaning a pointer to a location in memory that can't be
//   dereferenced (followed) without typing it first through a cast, like
//   `void *p; int i = *(int*)p`
//
//   Windows threads are very similar, with only a different return value of
//   DWORD, an integer type instead of a pointer type. The
//   thread_helper_return_t type is defined correctly depending on the
//   operating system at build time.
thread_helper_return_t
func_a (void *arg)
{
  // this is the empty statement. It suppresses warnings about unused variables
  (void)arg;

  // increment the shared variable in a loop
  int x;
  for (x = 0; x < INCREMENTS; ++x)
    {
      // BEGIN CRITICAL SECTION
      i++;
      // END CRITICAL SECTION
    }

  // return an empty result
  return 0;
}

// this is the thread function for thread 2
thread_helper_return_t
func_b (void *arg)
{
  // this is the empty statement. It suppresses warnings about unused variables
  (void)arg;

  // increment the shared variable in a loop
  int x;
  for (x = 0; x < INCREMENTS; ++x)
    {
      // BEGIN CRITICAL SECTION
      i--;
      // END CRITICAL SECTION
    }

  // return an empty result
  return 0;
}

// this is the main function. Program execution begins here.
int main(void)
{
  // prepare two variables holding the references to the worker threads
  thread_helper_t thread_a;
  thread_helper_t thread_b;

  // create the two threads. The threads will start executing immediately.
  thread_helper_create(&thread_a, &func_a, NULL);
  thread_helper_create(&thread_b, &func_b, NULL);

  // join the two threads. This blocks until the threads have terminated.
  thread_helper_join(thread_a);
  thread_helper_join(thread_b);

  // print the result.
  //
  //   Observe how the result of the computetaion will usually not add up to
  //   the expected value of zero for large enough values of ITERATIONS. The
  //   actual result is unpredictable and appears random, even though it is not
  //   truly random.
  printf("%i\n", i);

  return 0;
}
