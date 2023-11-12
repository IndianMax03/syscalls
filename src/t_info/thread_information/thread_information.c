#include <linux/syscalls.h>
#include <linux/pid.h> 
#include <linux/sched.h>
#include <linux/uaccess.h>
#include "custom_thread_info.h"

SYSCALL_DEFINE2(gimme_thread_info, int, pid, void*, data)
{
    struct task_struct *task;
    struct thread_info *info;

    if (c_t_i == NULL) {
        return -ENOMEM; // Недостаточно памяти
    }

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        return -ESRCH; //  Процесс не найден
    }

    info = task_thread_info(task);
    if (info == NULL) {
        return -EINVAL; //  Аргумент передан неверно
    }

    struct custom_thread_info *c_t_i = kmalloc(sizeof(struct custom_thread_info), GFP_KERNEL);

    с_t_i->palcode_ksp = info->pcb_struct->ksp;
    с_t_i->palcode_usp = info->pcb_struct->usp;
    с_t_i->palcode_ptbr = info->pcb_struct->ptbr;
    с_t_i->palcode_pcc = info->pcb_struct->pcc;
    с_t_i->palcode_asn = info->pcb_struct->asn;
    с_t_i->palcode_unique = info->pcb_struct->unique;
    с_t_i->palcode_flags = info->pcb_struct->flags;
    с_t_i->palcode_res1 = info->pcb_struct->res1;
    с_t_i->palcode_res2 = info->pcb_struct->res2;

    if (info->task != NULL) {
        c_t_i->task_state = info->task->__state;
        c_t_i->task_prio = info->task->prio;
    } else {
        c_t_i->task_state = -1;
        c_t_i->task_prio = -1;
    }
    
    c_t_i->flags = info->flags;
    c_t_i->ieee_state = info->ieee_state;
    c_t_i->cpu = info->cpu;
    c_t_i->preempt_count = info->preempt_count;
    c_t_i->status = info->status;
    c_t_i->bpt_nsaved = info->bpt_nsaved;
    c_t_i->bpt_addr[0] = info->bpt_addr[0];
    c_t_i->bpt_addr[1] = info->bpt_addr[1];
    c_t_i->bpt_insn[0] = info->bpt_insn[0];
    c_t_i->bpt_insn[1] = info->bpt_insn[1];

    
    if (copy_to_user(data, c_t_i, sizeof(struct custom_thread_info)) != 0) {
        kfree(c_t_i);
        return -EFAULT; //  Неверный адрес
    }

    kfree(c_t_i);
    return 0;
}
