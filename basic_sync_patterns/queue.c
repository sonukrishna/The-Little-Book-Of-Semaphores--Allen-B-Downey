#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
sem_t leaderQ, followerQ;
void *leader(void *a)
{
    int i;
    for (i=0; i<50; ++i){
        sem_post(&leaderQ);
        sem_wait(&followerQ);
        printf("leader%d\n", i);
    }
}

void *follower(void *a)
{
    int i;
   // while(++i){
    for (i=0; i<50; ++i){
	sem_post(&followerQ);
	sem_wait(&leaderQ);
	printf("follower %d\n", i);
    }
}

main()
{
    sem_init(&leaderQ, 0, 0);
    sem_init(&followerQ, 0, 0);

    pthread_t t1, t2;
    pthread_create(&t1, 0, leader, 0);
    pthread_create(&t2, 0, follower, 0);
    pthread_join(t1, 0);
    pthread_join(t2, 0);
}
