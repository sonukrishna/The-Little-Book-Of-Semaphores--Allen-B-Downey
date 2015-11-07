#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#define n 10
sem_t mutex, barrier;
int count;

void *threadn(void *a)
{
    sem_wait(&mutex);
    count = count + 1;
    sem_post(&mutex);
    if (count == n){
	sem_post(&barrier);
    }
    sem_wait(&barrier);
    sem_post(&barrier);

    printf("thread %d to critical section\n",*(int *)a);
}

main()
{
    int i;
    sem_init(&mutex, 0, 1);
    sem_init(&barrier, 0, 1);
    pthread_t t[n];
    for(i=0; i<n; i++){
	pthread_create(&t[i], 0, threadn, &i);
    }
    for(i=0; i<n; i++){
	pthread_join(t[i], 0);
    }
    printf("the count %d\n",count);
}	
