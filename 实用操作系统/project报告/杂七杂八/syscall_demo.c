#include "los_printf.h"
#include "los_task_pri.h"
#include "los_base_pri.h"
#include "los_priqueue_pri.h"
#include "los_sem_pri.h"
#include "los_event_pri.h"
#include "los_mux_pri.h"
#include "los_hw_pri.h"
#include "los_exc.h"
#include "los_memstat_pri.h"
#include "los_mp.h"
#include "los_spinlock.h"
#include "los_percpu_pri.h"
#include "los_process_pri.h"
/* 新增系统调用内核处理函数的实现 */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "stdio.h"
#include "los_task_pri.h"

UINT32 g_PRIOR_MID_taskHiId;
UINT32 g_PRIOR_MID_taskLoId;
UINT32 g_PRIOR_MID_taskMidId;
UINT32 g_PRIOR_HI_taskId;
UINT32 g_PRIOR_LO_taskId;
#define TSK_PRIOR_HI 1
#define TSK_PRIOR_MID 2
#define TSK_PRIOR_LO 3

void Example_PRIOR_HI_Task(VOID)
{
    
    PRINTK("Enter PRIOR_HI_Task Handler.\r\n");
    PRINTK("PRIOR_HI_Task LOS_TaskDelete Success.\r\n");
    return;
}

void Example_PRIOR_LO_Task(VOID)
{
    
    PRINTK("Enter PRIOR_LO_Task Handler.\r\n");
    PRINTK("PRIOR_LO_Task LOS_TaskDelete Success.\r\n");
    return;
}

void Example_PRIOR_MID_TaskHi(VOID)
{
    
    PRINTK("Enter PRIOR_MID_TaskHi Handler.\r\n");
    PRINTK("PRIOR_MID_TaskLo LOS_TaskDelete Success.\r\n");
    return;
}

void Example_PRIOR_MID_TaskMid(VOID)
{
    
    PRINTK("Enter PRIOR_MID_TaskMid Handler.\r\n");
    PRINTK("PRIOR_MID_TaskMid LOS_TaskDelete Success.\r\n");
    return;
}

void Example_PRIOR_MID_TaskLo(VOID)
{
    PRINTK("Enter PRIOR_MID_TaskLo Handler.\r\n");
    PRINTK("PRIOR_MID_TaskLo LOS_TaskDelete Success.\r\n");
    return;
}


void SysNewSyscallSample(int num)
{
    UINT32 ret;
    TSK_INIT_PARAM_S initParam;

    /* 锁任务调度，防止新创建的任务比本任务高而发生调度 */
    LOS_TaskLock();

    PRINTK("LOS_TaskLock() Success!\r\n");


    initParam.pfnTaskEntry = (TSK_ENTRY_FUNC)Example_PRIOR_MID_TaskMid;
    initParam.usTaskPrio = TSK_PRIOR_MID;
    initParam.pcName = "PRIOR_MID_TaskMid";
    initParam.uwStackSize = OS_TASK_RESOURCE_STATCI_SIZE;
    initParam.uwResved   = LOS_TASK_STATUS_DETACHED;
    initParam.usEstimateRunTime   = 10;
    ret = LOS_TaskCreate(&g_PRIOR_MID_taskMidId, &initParam);
    if (ret != LOS_OK) {
        LOS_TaskUnlock();

        PRINTK("Example_PRIOR_MID_TaskMid create Failed!\r\n");
        return;
    }
    PRINTK("Example_PRIOR_MID_TaskMid create Success!\r\n");
    
    
    initParam.pfnTaskEntry = (TSK_ENTRY_FUNC)Example_PRIOR_HI_Task;
    initParam.usTaskPrio = TSK_PRIOR_HI;
    initParam.pcName = "PRIOR_HI_Task";
    initParam.uwStackSize = OS_TASK_RESOURCE_STATCI_SIZE;
    initParam.uwResved   = LOS_TASK_STATUS_DETACHED;
    initParam.usEstimateRunTime   = 10;
    ret = LOS_TaskCreate(&g_PRIOR_HI_taskId, &initParam);
    if (ret != LOS_OK) {
        LOS_TaskUnlock();

        PRINTK("Example__PRIOR_HI_Task create Failed!\r\n");
        return;
    }
    PRINTK("Example_PRIOR_HI_Task create Success!\r\n");
    
    
    initParam.pfnTaskEntry = (TSK_ENTRY_FUNC)Example_PRIOR_LO_Task;
    initParam.usTaskPrio = TSK_PRIOR_LO;
    initParam.pcName = "PRIOR_LO_Task";
    initParam.uwStackSize = OS_TASK_RESOURCE_STATCI_SIZE;
    initParam.uwResved   = LOS_TASK_STATUS_DETACHED;
    initParam.usEstimateRunTime   = 10;
    /* 创建高优先级任务，由于锁任务调度，任务创建成功后不会马上执行 */
    ret = LOS_TaskCreate(&g_PRIOR_LO_taskId, &initParam);
    if (ret != LOS_OK) {
        LOS_TaskUnlock();

        PRINTK("Example__PRIOR_LO_Task create Failed!\r\n");
        return;
    }
    PRINTK("Example_PRIOR_LO_Task create Success!\r\n");
    
    initParam.pfnTaskEntry = (TSK_ENTRY_FUNC)Example_PRIOR_MID_TaskHi;
    initParam.usTaskPrio = TSK_PRIOR_MID;
    initParam.pcName = "PRIOR_MID_TaskHi";
    initParam.uwStackSize = OS_TASK_RESOURCE_STATCI_SIZE;
    initParam.uwResved   = LOS_TASK_STATUS_DETACHED;
    initParam.usEstimateRunTime   = 5;
    /* 创建高优先级任务，由于锁任务调度，任务创建成功后不会马上执行 */
    ret = LOS_TaskCreate(&g_PRIOR_MID_taskHiId, &initParam);
    if (ret != LOS_OK) {
        LOS_TaskUnlock();

        PRINTK("Example_PRIOR_MID_TaskHi create Failed!\r\n");
        return;
    }
    PRINTK("Example_PRIOR_MID_TaskHi create Success!\r\n");
   
   
    initParam.pfnTaskEntry = (TSK_ENTRY_FUNC)Example_PRIOR_MID_TaskLo;
    initParam.usTaskPrio = TSK_PRIOR_MID;
    initParam.pcName = "PRIOR_MID_TaskLo";
    initParam.uwStackSize = OS_TASK_RESOURCE_STATCI_SIZE;
    initParam.uwResved   = LOS_TASK_STATUS_DETACHED;
    initParam.usEstimateRunTime   = 30;
    /* 创建低优先级任务，由于锁任务调度，任务创建成功后不会马上执行 */
    ret = LOS_TaskCreate(&g_PRIOR_MID_taskLoId, &initParam);
    if (ret != LOS_OK) {
        LOS_TaskUnlock();

        PRINTK("Example_PRIOR_MID_TaskLo create Failed!\r\n");
        return;
    }
    PRINTK("Example_PRIOR_MID_TaskLo create Success!\r\n");
    
    
    
    

    /* 解锁任务调度，此时会发生任务调度，执行就绪队列中最高优先级任务 */
    LOS_TaskUnlock();

    return;
}