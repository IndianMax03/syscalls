#include <stdio.h>
#include <linux/sched.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>
#include "custom_thread_info.h"

#define     ERROR   -1
#define     OK      0

int main(int argc, char* arcgv[])
{

  if (argc != 2) {
    printf("Invalid usage\n");
    printf("try: ./t_info_user <pid>\n");
    return ERROR;
  }

  int pid = atoi(arcgv[1]);

  struct custom_thread_info* data = malloc(sizeof(struct custom_thread_info));

  long int retval = syscall(548, pid, data);

  if (retval != 0) {
    printf("try another pid!\n");
  }

  printf("scall reted %ld\n", retval);
  printf("%lu\n", data->flags);
  printf("%lu\n", data->syscall_work);
  printf("%u\n",data->status);
  printf("%u\n",data->cpu);

  return OK;
}
