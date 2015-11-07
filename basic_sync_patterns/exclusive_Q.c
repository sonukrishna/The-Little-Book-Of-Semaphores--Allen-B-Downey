#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
sem_t mutex, rendezvous, leaderQ, followerQ;
int leaders, followers;
void *leader(void *a)
{
    int i = 0;
    for (i=0; i<100; ++i){
//    while (++i){
        sem_wait(&mutex);
        if (followers > 0){
	    followers--;
	    sem_post(&followerQ);
	}
	else{
	    leaders++;
	    sem_post(&mutex);
	    sem_wait(&leaderQ);
	}
        printf("leader\t%d\n",i);
        
        sem_wait(&rendezvous);
        sem_post(&mutex);
    }
}

void *follower(void *a)
{
    int i = 0;
//    while(++i){
    for (i=0; i<100; ++i){
	sem_wait(&mutex);
	if(leaders > 0){
	    leaders--;
	    sem_post(&leaderQ);
        }
	else{
	    followers++;
	    sem_post(&mutex);
	    sem_wait(&followerQ);
	}
	printf("follower\t%d\n", i);
	
	sem_post(&rendezvous);
    }
}

main()
{
    pthread_t t1, t2;
    sem_init(&mutex, 0, 1);
    sem_init(&leaderQ, 0, 0);
    sem_init(&followerQ, 0, 0);
    sem_init(&rendezvous, 0, 0);

    pthread_create(&t1, 0, &leader, 0);
    pthread_create(&t2, 0, &follower, 0);
    pthread_join(t1, 0);
    pthread_join(t2, 0);

//    while(1);
}

