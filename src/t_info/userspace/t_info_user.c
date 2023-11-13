#include <stdio.h>
#include <linux/sched.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>
#include "custom_thread_info.h"

#define     ERROR               -1
#define     OK                  0
#define     GIMME_THREAD_INFO   548

int main(int argc, char* arcgv[])
{

    if (argc != 2) {
        printf("Invalid usage\n");
        printf("try: ./prog <pid>\n");
        return ERROR;
    }

    int pid = atoi(arcgv[1]);

    struct custom_thread_info* data = malloc(sizeof(struct custom_thread_info));

    if (data == NULL) {
        printf("Cannot allocate memory.\n");
        return ERROR;
    }

    long int retval = syscall(GIMME_THREAD_INFO, pid, data);

    if (retval != 0) {
        free(data);
        printf("Error while syscalling, broo\n");
        printf("exec: sudo dmesg\n");
        return ERROR;
    }
  
    printf("thread_struct:\n");
    printf("--- flags = %lu\n", data->flags);
    printf("--- syscall_work = %lu\n", data->syscall_work);
    printf("--- status = %u\n",data->status);
    printf("--- cpu = %u\n",data->cpu);

    free(data);

    return OK;

}
