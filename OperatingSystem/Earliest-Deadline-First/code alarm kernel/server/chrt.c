#include "pm.h"
#include "mproc.h"
#include <minix/callnr.h>
#include <stdio.h>


/*===========================================================================*
 *				do_chrt				     *
 *===========================================================================*/
int do_chrt(void)
{
    /* int sys_chrt(proc_ep, deadline) */
    //printf("Server level: do_char() who_p:%d \n", who_p);
    return sys_chrt(who_p, m_in.m2_l1);    //proc_ep: caller's proc number, in main.c there is a global variable who_e
                                           //deadline: the input message.m2_l1, in main.c there is a global variable message m_in
}

/* what is the difference between who_e and who_p?
   in server/pm/main.c, who_e = m_in.m_source;   who sent the message
   in Glo.h, define who_p  ((int) (fp - fproc))
             define who_e  (self!=NULL ? fp->fp.endpoint : m_in.m_source)
             fp: pointer to caller's fproc struct
    EXTERN int who_p, who_e;	 caller's proc number, endpoint 
 */