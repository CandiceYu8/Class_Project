#include <sys/cdefs.h>
#include "namespace.h"
#include <lib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int chrt(long deadline)
{
  if(deadline < 0)
    return 0;
    
  message m;
  memset(&m, 0, sizeof(m));
  m.m2_l1 = deadline;
  //printf("Application level: int chrt(long deadline) \n");
  return _syscall(PM_PROC_NR, PM_CHRT, &m);
}

/* int _syscall(endpoint_t _who, int _syscallnr, message *_msgptr);
   #define PM_PROC_NR   ((endpoint_t) 0)    which is the process manager*/

