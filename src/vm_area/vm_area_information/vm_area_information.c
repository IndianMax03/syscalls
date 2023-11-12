#include <linux/syscalls.h>
#include <linux/pid.h> 
#include <linux/sched.h>
#include <linux/uaccess.h>
#include "custom_vm_area_info.h"

SYSCALL_DEFINE3(gimme_vm_area_info, int, pid, unsigned long, addr, void*, data)
{
    struct task_struct *task;

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        printk("ERR: ESRCH");
        return -ESRCH; //  Процесс не найден
    }

    struct vm_area_struct *vm_info = find_vma(task->active_mm, addr);
    if (vm_info == NULL) {
        printk("ERR: EINVAL (while finding)");
        return -EINVAL; //  Неверный аргумент (адрес)
    }

    struct custom_vm_area_info *c_va_i = kmalloc(sizeof(struct custom_vm_area_info), GFP_KERNEL);
    if (c_va_i == NULL) {
        printk("ERR: EINVAL (while kmalloc)");
        return -EINVAL; //  Неверный аргумент (адрес)
    }

    c_va_i->vm_start = vm_info->vm_start;
    c_va_i->vm_end = vm_info->vm_end;
    c_va_i->vm_flags = vm_info->vm_flags;

    if (vm_info->vm_region != NULL) {
        c_va_i->vm_region_start = vm_info->vm_region->vm_start;
        c_va_i->vm_region_end = vm_info->vm_region->vm_end;
        c_va_i->vm_region_top = vm_info->vm_region->vm_top;
        c_va_i->vm_region_pgoff = vm_info->vm_region->vm_top;
    } else {
        printk("WARN: vm_info->vm_region is null");
        c_va_i->vm_region_start = 0;
        c_va_i->vm_region_end = 0;
        c_va_i->vm_region_top = 0;
        c_va_i->vm_region_pgoff = 0;
    }
    
    if (copy_to_user(data, c_va_i, sizeof(struct custom_vm_area_info)) != 0) {
        kfree(c_va_i);
        printk("ERR: EFAULT");
        return -EFAULT; //  Неверный адрес
    }

    kfree(c_va_i);
    printk("INF: OK");
    return 0;
}
