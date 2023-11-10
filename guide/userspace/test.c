#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{
         long int retval = syscall(548); //  вместо 548 номер вашего системного вызова
         printf("Syscall reted: %ld\n", retval);
         return 0;
}
