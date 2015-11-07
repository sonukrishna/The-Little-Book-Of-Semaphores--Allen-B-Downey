#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#define N 50 //max no.of threads
#define n 10 //max no.of concurrent threads
sem_t multiplex;
int count;

void *threadN(void *a)
{
    sem_wait(&multiplex);
    // critical section
    int sval;
    sem_getvalue(&multiplex, &sval);
    printf("the thread%d semVal: %d\n",*(int *)a, sval);
    count += 1;
    sem_post(&multiplex);
}
main()
{
    int i;
    pthread_t t[N];
    sem_init(&multiplex, 0, n);
    printf("count befor:%d\n",count);
    for (i=0; i<N; i++)
    pthread_create(&t[i],0,threadN,&i);
    for(i=0; i<N; i++)
    pthread_join(t[i], 0);
    printf("count after:%d\n", count);
}
