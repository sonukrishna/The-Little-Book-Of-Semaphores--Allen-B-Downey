#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#define n 10 //max no.of threads
int count;
sem_t mutex, turnstile, turnstile2;

void *threadn(void *a)
{
    sem_wait(&mutex);
    count += 1;
    if (count == n) {
	sem_wait(&turnstile2); //lock the second turnstile
	sem_post(&turnstile); //unlock the first
    }
    sem_post(&mutex);
    printf("threads %d\n", *(int *)a);
    sem_wait(&turnstile); //first turnstile
    sem_post(&turnstile);
//    printf("thread %d critical point\n", *(int *)a);

    sem_wait(&mutex);
    count -= 1;
    if (count == 0) {
	sem_wait(&turnstile); // lock the first turnstile
        sem_post(&turnstile2);
    }
    sem_post(&mutex);
//    printf("threads %d\n",*(int *)a);
    
    sem_wait(&turnstile2); // second turnstile
    sem_post(&turnstile2);
}

main()
{
    int i;
    sem_init(&mutex, 0, 1);
    sem_init(&turnstile, 0, 0);
    sem_init(&turnstile2, 0, 1);
    
    pthread_t t[n];

    for(i = 0; i < n; i++){
	pthread_create(&t[i], 0, threadn, &i);
    }
    for(i = 0; i < n; i++){
	pthread_join(t[i], 0);
    }
}
