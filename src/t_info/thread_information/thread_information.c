#include <linux/syscalls.h>
#include <linux/pid.h> 
#include <linux/sched.h>
#include <linux/uaccess.h>

SYSCALL_DEFINE2(gimme_thread_info, int, pid, void*, data)
{
    struct task_struct *task;
    struct thread_info *info;

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        return -ESRCH; //  Процесс не найден
    }

    info = task_thread_info(task);
    if (info == NULL) {
        return -EINVAL; //  Аргумент передан неверно
    }

    if (copy_to_user(data, info, sizeof(struct thread_info)) != 0) {
        return -EFAULT; //  Неверный адрес
    }


    return 0;
}
