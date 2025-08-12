#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mtx;

void *increase_counter(void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mtx);
        counter++;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    pthread_mutex_init(&mtx, NULL);

    pthread_create(&t1, NULL, increase_counter, NULL);
    pthread_create(&t2, NULL, increase_counter, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mtx);

    printf("Counter: %d\n", counter);
}
