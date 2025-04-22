#include <stdio.h>
/*
Simple Dining Philosophers solution using semaphores:
1. Use N philosophers and N forks (chopsticks)
2. Each fork is a binary semaphore (initially 1)
3. Each philosopher:
   - Think for some time
   - Pick up left fork first (wait)
   - Pick up right fork (wait)
   - Eat for some time
   - Put down right fork (signal)
   - Put down left fork (signal)
4. Avoid deadlock by:
   - Making last philosopher pick right fork first
   - Or using a mutex for picking up both forks
5. Main creates threads and initializes semaphores
*/
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

sem_t mutex;
sem_t s[N];
int state[N];

void test(int i) {
    if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        sem_post(&s[i]);
    }
}

void take_forks(int i) {
    sem_wait(&mutex);
    state[i] = HUNGRY;
    test(i);
    sem_post(&mutex);
    sem_wait(&s[i]);
}

void put_forks(int i) {
    sem_wait(&mutex);
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void *philosopher(void *arg) {
    int i = *(int*)arg;
    while(1) {
        printf("Philosopher %d is thinking\n", i);
        sleep(1);
        
        printf("Philosopher %d is hungry\n", i);
        take_forks(i);
        
        printf("Philosopher %d is eating\n", i);
        sleep(1);
        
        put_forks(i);
    }
    return NULL;
}

int main() {
    pthread_t phil[N];
    int i, phil_id[N];
    
    sem_init(&mutex, 0, 1);
    for(i = 0; i < N; i++)
        sem_init(&s[i], 0, 0);
    
    for(i = 0; i < N; i++) {
        phil_id[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &phil_id[i]);
    }
    
    for(i = 0; i < N; i++)
        pthread_join(phil[i], NULL);
    
    sem_destroy(&mutex);
    for(i = 0; i < N; i++)
        sem_destroy(&s[i]);
    return 0;
} 