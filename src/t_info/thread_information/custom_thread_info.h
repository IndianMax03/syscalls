#ifndef _UAPI_LINUX_CUSTOM_THREAD_INFO_H
#define _UAPI_LINUX_CUSTOM_THREAD_INFO_H

struct custom_thread_info
{
    unsigned long   palcode_ksp;
	unsigned long   palcode_usp;
	unsigned long   palcode_ptbr;
	unsigned int    palcode_pcc;
	unsigned int    palcode_asn;
	unsigned long   palcode_unique;
	unsigned long   palcode_flags;
	unsigned long   palcode_res1, palcode_res2;
    unsigned int    task_state;
    int             task_prio;
    unsigned int    flags;
    unsigned int    ieee_state;
    unsigned        cpu;
    int             preempt_count;
    unsigned int    status;
    int             bpt_nsaved;
    unsigned long   bpt_addr[2];
    unsigned int    bpt_insn[2];
};


#endif
