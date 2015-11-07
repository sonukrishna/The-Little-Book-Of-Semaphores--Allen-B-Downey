#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
sem_t mutex;
int count;

void *thread1(void *a)
{
    sem_wait(&mutex);
    // critical section
    count = count + 1;
    sem_post(&mutex);
}
void *thread2(void *a)
{
    sem_wait(&mutex);
    // critical section
    sem_post(&mutex);
}
main()
{
    pthread_t t1, t2;
    sem_init(&mutex, 0, 1);
    printf("count before:%d\n",count);
    pthread_create(&t1, 0, thread1, 0);
    pthread_create(&t1, 0, thread2, 0);
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    printf("count after:%d\n",count);
}
