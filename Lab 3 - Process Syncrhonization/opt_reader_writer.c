#include <stdio.h>
/*
Simple Reader-Writer solution using semaphores:
1. Use three semaphores:
   - mutex: Binary semaphore for reader count (initially 1)
   - wrt: Binary semaphore for writer access (initially 1)
   - readTry: Binary semaphore for reader entry (initially 1)
2. Use shared variables:
   - readcount: Number of readers (initially 0)
   - data: Shared data
3. Writer:
   - Wait for write access
   - Write data
   - Signal write access
4. Reader:
   - Wait for entry and reader count access
   - Increment reader count, if first reader wait for write access
   - Read data
   - Decrement reader count, if last reader signal write access
5. Main creates threads and initializes semaphores
*/
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt, readTry;
int readcount = 0, data = 0;

void *writer(void *arg) {
    int id = *(int*)arg;
    while(1) {
        sem_wait(&wrt);
        data++;
        printf("Writer %d writes data: %d\n", id, data);
        sem_post(&wrt);
        sleep(1);
    }
    return NULL;
}

void *reader(void *arg) {
    int id = *(int*)arg;
    while(1) {
        sem_wait(&readTry);
        sem_wait(&mutex);
        readcount++;
        if(readcount == 1)
            sem_wait(&wrt);
        sem_post(&mutex);
        sem_post(&readTry);
        
        printf("Reader %d reads data: %d\n", id, data);
        
        sem_wait(&mutex);
        readcount--;
        if(readcount == 0)
            sem_post(&wrt);
        sem_post(&mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t r[5], w[5];
    int i, r_id[5], w_id[5];
    
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    sem_init(&readTry, 0, 1);
    
    for(i = 0; i < 5; i++) {
        r_id[i] = w_id[i] = i;
        pthread_create(&r[i], NULL, reader, &r_id[i]);
        pthread_create(&w[i], NULL, writer, &w_id[i]);
    }
    
    for(i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }
    
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    sem_destroy(&readTry);
    return 0;
} 