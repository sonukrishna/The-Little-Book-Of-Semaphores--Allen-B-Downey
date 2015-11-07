#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
sem_t aArrived, bArrived;

void *thread1(void *a)
{
    printf("statement a1\n");
    sem_post(&aArrived);
    sem_wait(&bArrived);
    printf("statement a2\n");
}

void *thread2(void *a)
{
    printf("statement b1\n");
    sem_post(&bArrived);
    sem_wait(&aArrived);
    printf("statement b2\n");
}


main()
{
    sem_init(&aArrived, 0, 0);
    sem_init(&bArrived, 0, 0);
    pthread_t tA, tB;
    pthread_create(&tA, NULL, thread1, NULL);
    pthread_create(&tB, NULL, thread2, NULL);
    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
}

