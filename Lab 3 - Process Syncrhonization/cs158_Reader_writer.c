#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,wrt;   //Semaphores
int readercount=0;
int count=5;
pthread_t reader1,reader2,writer1,writer2;   //Threads
void *reader(void *);
void *writer(void *);

int main()
{
    sem_init(&mutex,0,1);   // initializing semaphore (pointer,sharing_status-0: 
    //only by threads within the process 1: threads outside the process also, innitial value )
    sem_init(&wrt,0,1);
    while(count--)
    {
        pthread_create(&reader1,NULL,reader,"1"); // (pointer,default attr,routine,args)
        pthread_create(&reader2,NULL,reader,"2");
        pthread_create(&writer1,NULL,writer,"1");
        pthread_create(&writer2,NULL,writer,"2");
    }
}

void *reader(void *p)
{
    sem_wait(&mutex);
    readercount++;
    if(readercount==1) 
    sem_wait(&wrt);
    sem_post(&mutex);
    printf("Reader %s is Reading\n",(char*)p);
    sem_wait(&mutex);
    printf("Reader %s Completed Reading\n",(char*)p);
    readercount--;
    if(readercount==0) 
    sem_post(&wrt);
    sem_post(&mutex);
}

void *writer(void *p)
{
printf("Writer %s is Waiting\n",(char*)p);
sem_wait(&wrt);
printf("Writer %s is writing\n",(char*)p);
sem_post(&wrt);        //increments the value by one
printf("Writing %s Completed\n",(char*)p);
}

