#include "syslib.h"
#include <stdio.h>

int sys_chrt(proc_ep, deadline)
endpoint_t proc_ep;
long deadline;
{
    message m;
    m.m2_i1 = proc_ep;
    m.m2_l1 = deadline;
    //printf("Server level: sys_chrt(proc_ep, deadline) \n");
    return (_kernel_call(SYS_CHRT, &m));
}

