#include <stdio.h>
/*
Simple Producer-Consumer solution using semaphores:
1. Use a fixed-size buffer (N) shared between producer and consumer
2. Use three semaphores:
   - mutex: Binary semaphore for mutual exclusion (initially 1)
   - empty: Counting semaphore for empty slots (initially N)
   - full: Counting semaphore for filled slots (initially 0)
3. Producer:
   - Wait for empty slot and mutex
   - Add item to buffer
   - Signal mutex and full slot
4. Consumer:
   - Wait for full slot and mutex
   - Remove item from buffer
   - Signal mutex and empty slot
5. Main creates threads and initializes semaphores
*/
#include <pthread.h>
#include <semaphore.h>

#define N 5  // Buffer size
int buf[N], in = 0, out = 0;
sem_t mutex, empty, full;

void *producer(void *arg) {
    int item = 1;
    while(1) {
        sem_wait(&empty);
        sem_wait(&mutex);
        
        buf[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % N;
        item++;
        
        sem_post(&mutex);
        sem_post(&full);
        if(item > 10) break;  // Produce 10 items
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    while(1) {
        sem_wait(&full);
        sem_wait(&mutex);
        
        item = buf[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % N;
        
        sem_post(&mutex);
        sem_post(&empty);
        if(item >= 10) break;  // Consume all items
    }
    return NULL;
}

int main() {
    pthread_t p, c;
    
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
} 