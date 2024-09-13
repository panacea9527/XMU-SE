#include "los_printf.h"
#include "los_mux.h"
#include "los_task.h"
#include "los_sem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];  // 缓冲区数组
int in = 0;               // 缓冲区的写索引
int out = 0;              // 缓冲区的读索引
int count = 0;            // 缓冲区中的数据个数

UINT32 g_producerTaskId;
UINT32 g_consumerTaskId;

/* 生产者和消费者的互斥锁 */
LosMux bufferMux;
/* 表示缓冲区空位的信号量 */
UINT32 g_semEmpty;
/* 表示缓冲区数据项的信号量 */
UINT32 g_semFull;

/* 生产者任务 */
VOID ProducerTask(VOID)
{
    for(int i=0 ; i<10 ; i++)
    {
        // 生产数据
        int item = i; // 假设ProduceItem()函数已定义

        // 等待缓冲区有空位
        LOS_SemPend(g_semEmpty, LOS_WAIT_FOREVER);

        // 获取互斥锁
        LOS_MuxLock(&bufferMux, LOS_WAIT_FOREVER);
        
        //输出
        PRINTK("Producer produces item %d at position %d.\n",item,in % BUFFER_SIZE);

        // 将生产的数据放入缓冲区
        buffer[(in++) % BUFFER_SIZE] = item;

        // 释放互斥锁
        LOS_MuxUnlock(&bufferMux);

        // 增加缓冲区中的数据项信号量
        LOS_SemPost(g_semFull);

        // 生产一个产品需要1个tick
        LOS_TaskDelay(1);
    }
}

/* 消费者任务 */
VOID ConsumerTask(VOID)
{
    for(int i=0 ; i<10 ; i++)
    {
        // 等待缓冲区有数据
        LOS_SemPend(g_semFull, LOS_WAIT_FOREVER);

        // 获取互斥锁
        LOS_MuxLock(&bufferMux, LOS_WAIT_FOREVER);
        
        // 从缓冲区取出数据
        
        int item = buffer[out % BUFFER_SIZE];
        // 消费数据
        PRINTK("Consumer consumes item %d from position %d.\n",item,(out++) % BUFFER_SIZE);

        // 释放互斥锁
        LOS_MuxUnlock(&bufferMux);

        // 增加缓冲区空位信号量
        LOS_SemPost(g_semEmpty);



        // 消耗一个产品需要3个tick
        LOS_TaskDelay(3);
    }
}

// 初始化互斥锁、信号量、任务等
int SysNewSyscallSample(int num)
{
    UINT32 ret;

    // 创建互斥锁
    ret = LOS_MuxInit(&bufferMux, NULL);
    if (ret != LOS_OK) {
        return ret;
    }

    /* 锁任务调度 */
    LOS_TaskLock();

    // 创建信号量
    ret = LOS_SemCreate(BUFFER_SIZE, &g_semEmpty); // 缓冲区空位信号量
    if (ret != LOS_OK) {
        LOS_MuxDestroy(&bufferMux);
        return ret;
    }

    ret = LOS_SemCreate(0, &g_semFull); // 缓冲区数据项信号量
    if (ret != LOS_OK) {
        LOS_MuxDestroy(&bufferMux);
        LOS_SemDelete(g_semEmpty);
        return ret;
    }

    // 创建生产者任务
    TSK_INIT_PARAM_S stProducerTask;
    memset(&stProducerTask, 0, sizeof(TSK_INIT_PARAM_S));
    stProducerTask.pfnTaskEntry = (TSK_ENTRY_FUNC)ProducerTask;
    stProducerTask.usTaskPrio = 5; // 任务优先级
    stProducerTask.pcName = "ProducerTask";
    stProducerTask.uwStackSize = OS_TASK_RESOURCE_STATCI_SIZE; // 任务堆栈大小
    stProducerTask.uwResved = LOS_TASK_STATUS_DETACHED; // 任务状态
    ret = LOS_TaskCreate(&g_producerTaskId, &stProducerTask); // 创建任务并获取任务ID
    if (ret != LOS_OK) {
    PRINTK("Create ProducerTask failed.\n");
    return LOS_NOK;
    }

    // 创建消费者任务
    TSK_INIT_PARAM_S stConsumerTask;
    memset(&stConsumerTask, 0, sizeof(TSK_INIT_PARAM_S));
    stConsumerTask.pfnTaskEntry = (TSK_ENTRY_FUNC)ConsumerTask;
    stConsumerTask.usTaskPrio = 6; // 任务优先级，通常消费者优先级低于生产者
    stConsumerTask.pcName = "ConsumerTask";
    stConsumerTask.uwStackSize = OS_TASK_RESOURCE_STATCI_SIZE; // 任务堆栈大小
    stConsumerTask.uwResved = LOS_TASK_STATUS_DETACHED; // 任务状态
    ret = LOS_TaskCreate(&g_consumerTaskId, &stConsumerTask); // 创建任务并获取任务ID
    if (ret != LOS_OK) {
      PRINTK("Create ConsumerTask failed.\n");
      // 删除已创建的生产者任务
      LOS_TaskDelete(g_producerTaskId);
      return LOS_NOK;
    }

    /* 解锁任务调度 */
    LOS_TaskUnlock();
    
    /* 休眠100000Ticks */
    LOS_TaskDelay(100);


    LOS_MuxDestroy(&bufferMux);
    
    PRINTK("Test is Finished!");
    return LOS_OK;
}