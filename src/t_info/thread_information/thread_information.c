#include <linux/syscalls.h>
#include <linux/pid.h> 
#include <linux/sched.h>
#include <linux/uaccess.h>
#include "custom_thread_info.h"

SYSCALL_DEFINE2(gimme_thread_info, int, pid, void*, data)
{
    struct task_struct *task;
    struct thread_info *info;

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        printk("ERR: ESRCH");
        return -ESRCH; //  Процесс не найден
    }

    info = task_thread_info(task);
    if (info == NULL) {
        printk("ERR: EINVAL");
        return -EINVAL; //  Аргумент передан неверно
    }

    struct custom_thread_info *c_t_i = kmalloc(sizeof(struct custom_thread_info), GFP_KERNEL);
    if (c_t_i == NULL) {
        printk("ERR: ENOMEM");
        return -ENOMEM; // Недостаточно памяти
    }
    
    c_t_i->flags = info->flags;
    c_t_i->syscall_work = info->syscall_work;
    c_t_i->status = info->status;
    c_t_i->cpu = info->cpu;

    if (copy_to_user(data, c_t_i, sizeof(struct custom_thread_info)) != 0) {
        kfree(c_t_i);
        printk("ERR: EFAULT");
        return -EFAULT; //  Неверный адрес
    }

    kfree(c_t_i);
    printk("INF: OK");
    return 0;
}
