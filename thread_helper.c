
#include "thread_helper.h"

int
thread_helper_create(thread_helper_t *thread, thread_helper_return_t(*thread_func)(void*), void *arg)
{
#ifdef _WIN32
  // Windows Implementation based on CreateThread
  //   see: https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread
  *thread = CreateThread(NULL, 0, thread_func, arg, 0, NULL);
  return *thread != NULL ? 0 : -1;
#else
  // POSIX Implementation based on pthread_create
  //   see: https://man7.org/linux/man-pages/man3/pthread_create.3.html
  return pthread_create(thread, NULL, thread_func, arg);
#endif
}

int
thread_helper_join(thread_helper_t thread)
{
#ifdef _WIN32
  // Windows Implementation based on WaitForSingleObject
  //   see: https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject
  DWORD res = WaitForSingleObject(thread, INFINITE);
  CloseHandle(thread);
  return res == WAIT_OBJECT_0 ? 0 : res;
#else
  // POSIX Implementation based on pthread_join
  //   see: https://man7.org/linux/man-pages/man3/pthread_join.3.html
  return pthread_join(thread, NULL);
#endif
}
