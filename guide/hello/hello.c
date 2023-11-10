#include <linux/syscalls.h>

//  SYSCALL_DEFINEn(name, ...) -- n это кол-во принимаемых аргументов, name - имя
SYSCALL_DEFINE0(hello)
{
  printk("KERNEL SAYS: YO DUDE\n");
  return 0;
}
