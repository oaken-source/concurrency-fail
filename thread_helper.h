
// this is an include guard. It ensures that, if this header is included more
// than once, duplicate declarations are prevented.
#ifndef THREAD_HELPER_H
#define THREAD_HELPER_H

// define and declare different types, depending on the operating system
#ifdef _WIN32
// Declarations compatible with Windows Threads
#include <windows.h>

typedef HANDLE thread_helper_t;
typedef DWORD thread_helper_return_t;
#else
// Declarations compatible with POSIX Threads
#include <pthread.h>

typedef pthread_t thread_helper_t;
typedef void* thread_helper_return_t;
#endif

// based on the definitions and declarations above, declare portable functions
// for thread creation and thread join

// thread_helper_create
//
//   this function creates a new thread that starts executing the given
//   function immediately.
//
// parameters:
//
//   thread - this is a pointer to a thread_helper_t, it holds the reference to
//   the thread object in the used implementation.
//
//   thread_func - this is a pointer to a function that will be executed by the
//   created thread. The function takes a single argument of type void* and
//   returns a value of type void* when POSIX threads are used, and a value of
//   type DWORD, ant integer type, when Windows threads are used.
//
//   arg - this is the argument passed to the created threads, that is
//   accessible as the first argument to the thread_func function.
//
// return value:
//
//   the function returns 0 on success, and 1 otherwise.
int thread_helper_create(thread_helper_t *thread, thread_helper_return_t(*thread_func)(void*), void *arg);

// thread_helper_join
//
//   this function joins a previously created thread. This means that it waits
//   for the passed thread to terminate on its own, and then collects its
//   return value and frees all operating system resources related to the
//   thread object. This is important in long running programs because the
//   number of threads that the operating system can support is limited, and
//   terminated, but not joined threads continue to count towards this limit.
//
// parameters:
//
//   thread - this is a thread_helper_t, it holds the reference to the thread
//   object in the used implementation.
//
// return value:
//
//   the function returns 0 on success, and 1 otherwise.
int thread_helper_join(thread_helper_t thread);

#endif
