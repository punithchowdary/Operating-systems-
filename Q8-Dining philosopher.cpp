#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t forks[N];

void *philosopher(void *arg)
{
    int id = *(int *) arg;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        pthread_mutex_lock(&forks[left]);
        int result = pthread_mutex_trylock(&forks[right]);

        if (result == 0) {
            printf("Philosopher %d is eating\n", id);
            usleep(1000000);

            pthread_mutex_unlock(&forks[right]);
        }
        pthread_mutex_unlock(&forks[left]);

        printf("Philosopher %d is thinking\n", id);
        usleep(1000000);
    }

    return NULL;
}

int main()
{
    pthread_t threads[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

