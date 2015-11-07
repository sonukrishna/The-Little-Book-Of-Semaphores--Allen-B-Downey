#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
sem_t mutex, items, space;
int buffer;
void *producer(void *a)
{
    int i, event;
    for (i=0; i<10; i++){
	event = rand();
        sem_wait(&space);
	sem_wait(&mutex);
	printf("the producer produced: %d\n", event);
	buffer = event;
	sem_post(&mutex);
	sem_post(&items);
    }
    sleep(1);
}

void *consumer(void *a)
{
    int i, event;
    for (i=0; i<10; i++){
	sem_wait(&items);
	sem_wait(&mutex);
	event = buffer;
	printf("the consumer gets: %d\n", event);
	sem_post(&mutex);
	sem_post(&space);
    }
    printf("\n");
    sleep(1);
}

main()
{
    pthread_t t1, t2;
    
    sem_init(&space, 0, 1); 
    sem_init(&mutex, 0, 1);
    sem_init(&items, 0, 0);

    pthread_create(&t1, 0, producer, 0);
    pthread_create(&t2, 0, consumer, 0);
    pthread_join(t1, 0);
    pthread_join(t2, 0);
}
