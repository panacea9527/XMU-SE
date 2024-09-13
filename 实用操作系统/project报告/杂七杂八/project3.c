#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];  // 缓冲区数组
int in = 0;               // 缓冲区的写索引
int out = 0;              // 缓冲区的读索引

pthread_mutex_t bufferMutex;    // 缓冲区的互斥锁
sem_t semEmpty;                 // 表示缓冲区空位的信号量
sem_t semFull;                  // 表示缓冲区数据项的信号量

void* ProducerTask(void* arg) {
    for (int i = 0; i < 10; i++) {
        int item = i;

        sem_wait(&semEmpty);

        pthread_mutex_lock(&bufferMutex);
        
        printf("Producer produces item %d at position %d.\n", item, in % BUFFER_SIZE);
        buffer[(in++) % BUFFER_SIZE] = item;
        
        pthread_mutex_unlock(&bufferMutex);

        sem_post(&semFull);

        // 模拟生产延迟
        sleep(1);
    }
    return NULL;
}

void* ConsumerTask(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&semFull);

        pthread_mutex_lock(&bufferMutex);
        
        int item = buffer[out % BUFFER_SIZE];
        printf("Consumer consumes item %d from position %d.\n", item, (out++) % BUFFER_SIZE);
        
        pthread_mutex_unlock(&bufferMutex);

        sem_post(&semEmpty);

        // 模拟消费延迟
        sleep(3);
    }
    return NULL;
}

int main() {
    pthread_mutex_init(&bufferMutex, NULL);
    sem_init(&semEmpty, 0, BUFFER_SIZE);
    sem_init(&semFull, 0, 0);

    pthread_t producerThread, consumerThread;

    pthread_create(&producerThread, NULL, ProducerTask, NULL);
    pthread_create(&consumerThread, NULL, ConsumerTask, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    pthread_mutex_destroy(&bufferMutex);
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);

    printf("Test is Finished!\n");
    return 0;
}
