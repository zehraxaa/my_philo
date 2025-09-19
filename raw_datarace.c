#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *print_text(void *arg)
{
    char *text = (char *)arg;
    for (int i = 0; i < 5; i++)
    {
        printf("%s", text);
        usleep(10); // aynı anda çakışmayı kolaylaştırmak için
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, print_text, "Thread 1 says hello\n");
    pthread_create(&t2, NULL, print_text, "Thread 2 says hi\n");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}
