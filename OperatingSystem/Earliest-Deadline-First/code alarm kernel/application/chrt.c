#include <sys/cdefs.h>
#include "namespace.h"
#include <lib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include<sys/time.h>


void sig_alarm()
{
  printf("process reached deadline. \n");
  exit(0);
}

int chrt(long deadline)
{
  if(deadline < 0)
    return 0;
    
  signal(SIGALRM, sig_alarm);
  /* if deadline == 0, alarm will be canceled */
  alarm((unsigned int)deadline);

  message m;
  memset(&m, 0, sizeof(m));

  // struct timeval tv;
  // gettimeofday(&tv, NULL);

  // m.m2_l1 = deadline + tv.tv_sec;
  m.m2_l1 = deadline;
  //printf("Application level: int chrt(long deadline:%ld) \n",deadline);
  return _syscall(PM_PROC_NR, PM_CHRT, &m);
}

/* int _syscall(endpoint_t _who, int _syscallnr, message *_msgptr);
   #define PM_PROC_NR   ((endpoint_t) 0)    which is the process manager*/

