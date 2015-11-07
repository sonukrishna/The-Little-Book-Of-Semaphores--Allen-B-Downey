#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
sem_t mutex, room_empty;
int count;

void *reader(void *a)
{
    int i = 1;
    while(i < 4) {
	sem_wait(&mutex);
	count++;
	if (count == 1) {
	    sem_wait(&room_empty);
	}
	sem_post(&mutex);
	printf("the reader %d access the block : %d\n",*(int *)a, i);
	i++;
	sem_wait(&mutex);
	count--;
	if (count == 0) {
	    sem_post(&room_empty);
	}
	sem_post(&mutex);
    }
}

void *writer(void *a)
{
    int i = 1;
    while (i < 4) {
	sem_wait(&room_empty);
	printf("the writer %d acces the block : %d\n",*(int *)a, i);
	i++;
	sem_post(&room_empty);
    }
}

main()
{
    int i;
    pthread_t t1[4], t2[2];
    sem_init(&mutex, 0, 1);
    sem_init(&room_empty, 0, 1);

    for (i = 0; i < 4; i++) {
	pthread_create(&t1[i], 0, reader, &i);
    }
    for (i = 0; i < 2; i++) {
	pthread_create(&t2[i], 0, writer, &i);
    }
    for (i = 0; i < 4; i++){
	pthread_join(t1[i], 0);
    }
    for (i = 0; i < 2; i++){
	pthread_join(t2[i], 0);
    }
}
