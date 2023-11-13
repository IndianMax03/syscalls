#include <stdio.h>
#include <linux/sched.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>
#include "custom_vm_area_info.h"

#define     ERROR               -1
#define     OK                  0
#define     GIMME_VM_AREA_INFO  549

int main(int argc, char* argv[])
{

    if (argc != 3) {
        printf("Invalid usage\n");
        printf("try: ./prog <pid> <addr>\n");
        return ERROR;
    }

    int pid = atoi(argv[1]);
    unsigned long addr = strtoul(argv[2], NULL, 0);

    struct custom_vm_area_info* data = malloc(sizeof(struct custom_vm_area_info));

    if (data == NULL) {
        printf("Cannot allocate memory.\n");
        return ERROR;
    }

    long int retval = syscall(GIMME_VM_AREA_INFO, pid, addr, data);

    if (retval != 0) {
        free(data);
        printf("Error while syscalling, broo\n");
        printf("exec: sudo dmesg\n");
        return ERROR;
    }
  
    printf("vm_area_struct:\n");
    printf("--- vm_start = %lu\n", data->vm_start);
    printf("--- vm_end = %lu\n",data->vm_end);
    printf("--- vm_flags = %lu\n",data->vm_flags);
    printf("--- vm_pgoff = %lu\n",data->vm_pgoff);

    free(data);

    return OK;
}
