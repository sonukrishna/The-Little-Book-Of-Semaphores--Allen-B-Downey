#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

int leaders, followers;
sem_t mutex, rndezvous, leaderQ, followerQ;

