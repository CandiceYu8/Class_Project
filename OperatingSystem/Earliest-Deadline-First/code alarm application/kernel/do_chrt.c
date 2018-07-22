/* The kernel call implemented in this file:
 *   m_type:	SYS_CHRT
 *
 * The parameters for this kernel call are:
 *   m2_i1  (m_m2.m2i1  _who)
 *   m2_l1  (m_m2.m2l1  deadline)
 */

#include "kernel/system.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minix/timers.h"
#include "kernel/clock.h"

/*===========================================================================*
 *				do_chrt					     *
 *===========================================================================*/
int do_chrt(struct proc * caller, message * m_ptr)
{
  /* in sys_chrt: m.m2_i1 = proc_ep; m.m2_l1 = deadline; */
  struct proc *rp = proc_addr(m_ptr->m2_i1);
  long deadline = m_ptr->m2_l1;

  /* set flag and dequeue if the process was runnable */
	RTS_SET(rp, RTS_NO_QUANTUM);

  /* it is a dynamic deadline for it adds real_time in */
  if(deadline > 0)
    rp->ddl_est = deadline;
    // rp->ddl_est = (clock_t)deadline*60 + get_monotonic();

  /* if has been set before and now change to normal one */
  else if(deadline == 0){
    if(rp->ddl_est != 0){
      rp->ddl_est = 0;
    }
  }

  /* enqueue the process*/
	RTS_UNSET(rp, RTS_NO_QUANTUM);
  printf("process %d, deadline: %ld \n", rp->p_nr, deadline);
  return (OK);
}