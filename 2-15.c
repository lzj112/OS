#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMMBER_OF_THREADS 10

void* print_hello_world(void* tid) 
{
    //本线程输出线程的标识符, 然后退出
    
    printf("hello word. Greeting from thread %d\n", (int)tid);
    // pthread_exit(NULL);
}

int main() 
{
    //主程序创建十个线程, 然后退出
    pthread_t threads[NUMMBER_OF_THREADS];
    int status, i, tmp;

    for (i = 0; i < NUMMBER_OF_THREADS; i++) 
    {
        tmp = i;
        // printf("%d %d---\n", i, tmp);
        printf("Main here. Creating thread %d\n", tmp);
        status = pthread_create(&threads[tmp], NULL, print_hello_world, (void*)tmp);
        if (status != 0) 
        {
            printf("Oops. pthread_create returned error code %d\n", status);
            exit(-1);
        }
    }

    return 0;
}