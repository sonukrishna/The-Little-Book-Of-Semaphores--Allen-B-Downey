#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t aa, bb;
void *thread1(void *a)
{
	printf("statement 1\n");
        sem_post(&aa);
	sem_wait(&bb);
	printf("statement 2\n");
}
void *thread2(void *a)
{
	printf("statement 1.1\n");
	sem_post(&bb);
	sem_wait(&aa);
	printf("statemnt 2.1\n");
}

main()
{
	pthread_t t1,t2;
	sem_init(&aa, 0, 0);
	sem_init(&bb, 0, 0);
	pthread_create(&t1, 0, thread1, 0);
	pthread_create(&t2, 0, thread2, 0);
	pthread_join(t1, 0);
	pthread_join(t2, 0);
}
