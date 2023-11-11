#include <linux/syscalls.h>
#include <linux/pid.h> 
#include <linux/sched.h>
#include <linux/uaccess.h>

SYSCALL_DEFINE2(gimme_thread_info, int, pid, void*, data)
{
    struct task_struct *task;
    struct thread_info *info;
    void *buffer;

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        return -ESRCH; //  Процесс не найден
    }

    info = task_thread_info(task);
    if (info == NULL) {
        return -EINVAL; //  Аргумент передан неверно
    }

    buffer = kmalloc(sizeof(struct thread_info), GFP_KERNEL);
    if (buffer == NULL) {
        return -ENOMEM; // Недостаточно памяти
    }

    memcpy(buffer, info, sizeof(struct thread_info));

    if (copy_to_user(data, buffer, sizeof(struct thread_info)) != 0) {
        kfree(buffer);
        return -EFAULT; //  Неверный адрес
    }

    kfree(buffer);
    return 0;
}