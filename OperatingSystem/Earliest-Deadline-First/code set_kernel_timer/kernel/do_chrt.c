#include "kernel/system.h"
#include <minix/timers.h>
#include "kernel/clock.h"
#include <minix/endpoint.h>
#include <signal.h>
#include <stdio.h>

void ddl_deal(minix_timer_t *tp)
{
	struct proc *rp;
	int proc_nr;
	rp = proc_addr(tp->tmr_arg.ta_int);
	printf("process %d reached deadline \n", rp->p_nr);
	/* void cause_sig(proc_nr_t proc_nr, int sig_nr) send signal to kill the process */
	/* check whether it has already finished, return nonzero if the process is alive */
	if (isokendpt(rp->p_endpoint, &proc_nr)) {
		rp = proc_addr(proc_nr);	
		cause_sig(rp->p_nr, SIGABRT);
	}
}

int do_chrt(struct proc *caller_ptr, message *m_ptr)
{
	struct proc *rp = proc_addr(m_ptr->m2_i1);
	minix_timer_t *tp = &rp->ddl_est;
	long deadline = m_ptr->m2_l1;

	/* if deadline < 0, failed to chrt */
	if (deadline < 0)
		return -1;	

	/* set flag and dequeue if the process was runnable */
	RTS_SET(rp, RTS_NO_QUANTUM);

	/* if deadline == 0 and called chrt before, then we need to change it to normal process */
    // if(tp->tmr_exp_time != 0 && deadline == 0){
    if(tp->tmr_exp_time != 0 ){
		reset_kernel_timer(tp);
        tp->tmr_exp_time = 0;
        printf("change to normal process. \n");
    }

	/* if deadline > 0, then to set_kernel_timer */
	tp->tmr_arg.ta_int = m_ptr->m2_i1;
	tp->tmr_exp_time = system_hz * deadline + get_monotonic();
	tp->tmr_func = (tmr_func_t)ddl_deal;
	set_kernel_timer(tp, tp->tmr_exp_time, tp->tmr_func); 

	/* enqueue the process*/
	RTS_UNSET(rp, RTS_NO_QUANTUM);
	return (OK);
}

/* 
in Timers.h
typedef struct minix_timer
{
  struct minix_timer	*tmr_next;	 next in a timer chain 
  clock_t 	tmr_exp_time;	 expiration time 
  tmr_func_t	tmr_func;	 function to call when expired 
  tmr_arg_t	tmr_arg;	 random argument, typedef union { int ta_int; long ta_long; void *ta_ptr; } tmr_arg_t;
} minix_timer_t;

in Proc.h
#define RTS_NO_QUANTUM	0x8000	 process ran out of its quantum and we should pick a new one. 
            Process was dequeued and should be enqueued at the end of some run queue again. 

in system.c
   void cause_sig(proc_nr_t proc_nr, int sig_nr) 
 ** A system process wants to send signal 'sig_nr' to process 'proc_nr'.
*/