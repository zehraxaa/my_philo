#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t	mtx;

void *print_text(void *arg)
{
    char *text = (char *)arg;

	pthread_mutex_lock(&mtx);
    for (int i = 0; i < 5; i++)
    {
        printf("%s", text);
        usleep(10); // aynı anda çakışmayı kolaylaştırmak için
    }
	pthread_mutex_unlock(&mtx);

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

	pthread_mutex_init(&mtx, NULL);

    pthread_create(&t1, NULL, print_text, "Thread 1 says hello\n");
    pthread_create(&t2, NULL, print_text, "Thread 2 says hi\n");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

	pthread_mutex_destroy(&mtx);
}
