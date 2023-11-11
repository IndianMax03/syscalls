#include <stdio.h>
#include <linux/sched.h>
#include <sys/syscall.h>
#include <unistd.h>

struct thread_info {
 unsigned int  flags;  /* low level flags */
 int   preempt_count; /* 0 => preemptable, <0 => BUG */
};

int main()
{
  struct thread_info data;
  long int retval = syscall(548, getpid(), &data);
  printf("scall reted %ld\n", retval);
  printf(data.flags);
  return 0;
}
