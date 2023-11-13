#include <stdio.h>
#include <linux/sched.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>
#include "custom_vm_area_info.h"

#define     ERROR   -1
#define     OK      0

int main(int argc, char* arcgv[])
{

  struct custom_vm_area_info* data = malloc(sizeof(struct custom_vm_area_info));

  long int retval = syscall(549, getpid(), 12, data);

  printf("scall reted %ld\n", retval);
  
  printf("%lu\n", data->vm_start);
  printf("%lu\n",data->vm_end);
  printf("%lu\n",data->vm_flags);
  printf("%lu\n",data->vm_pgoff);

  return OK;
}
