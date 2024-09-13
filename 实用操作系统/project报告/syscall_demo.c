#include "los_printf.h"
/* 新增系统调用内核处理函数的实现 */
void SysNewSyscallSample(int num)
{
    PRINTK("kernel mode: num = %d\n", num);
    return;
}