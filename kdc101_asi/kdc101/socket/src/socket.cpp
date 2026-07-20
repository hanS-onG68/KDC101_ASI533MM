#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // 用于 sleep()
#include "socket.h"

// 线程函数1
void* task1(void* arg) {
    printf("[Info]Thread1 is running task1.\n");
    Server();
    return NULL;
}

// 线程函数2
void* task2(void* arg) {
    printf("[Info]Thread2 is running task2.\n"); 
    Client((double*)arg);
    return NULL;
}
 
int socket(double *intputNum)
{
    pthread_t thread1, thread2; // 声明两个线程标识符

    // 创建线程1，执行task1函数
    if (pthread_create(&thread1, NULL, task1, NULL) != 0) {
        perror("[Fail]Failed to create thread1");
        return 1;
    }

    /* 
        int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
            thread: 指向线程标识符的指针，用于存储新创建线程的 ID;
            attr: 线程属性，通常设为 NULL 表示使用默认属性;
            start_routine: 线程要执行的函数指针，该函数必须接受一个 void* 参数并返回 void*。
            arg: 传递给 start_routine 函数的参数。
    */

    // 创建线程2，执行task2函数
    if (pthread_create(&thread2, NULL, task2, (void*)intputNum) != 0) {
        perror("[Fail]Failed to create thread2");
        return 1;
    }

    // 等待两个线程都执行完毕
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}