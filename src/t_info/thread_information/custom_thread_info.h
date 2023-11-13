#ifndef _UAPI_LINUX_CUSTOM_THREAD_INFO_H
#define _UAPI_LINUX_CUSTOM_THREAD_INFO_H

struct custom_thread_info
{
    unsigned long   flags;
    unsigned long   syscall_work;
    unsigned int    status;
    unsigned int    cpu;
};

#endif
