#ifndef _UAPI_LINUX_CUSTOM_VM_AREA_INFO_H
#define _UAPI_LINUX_CUSTOM_VM_AREA_INFO_H

struct custom_vm_area_info
{
    unsigned long   vm_start;
	unsigned long   vm_end;
    unsigned long   vm_flags;
    unsigned long	vm_region_start;
	unsigned long	vm_region_end;
	unsigned long	vm_region_top;
    unsigned long   vm_region_pgoff;
};


#endif
