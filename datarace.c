#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
    pthread_mutex_t mtx; // bu bizim gardiyanımız
    char *text;
}   t_list;

void    *print_message(void *arg)
{
    t_list *list = (t_list *)arg;
    int i = 0;

    pthread_mutex_lock(&list->mtx); // kilidi al
    while (i < 5)
    {
        printf("%s\n", list->text);
        i++;
        usleep(10);
    }
    pthread_mutex_unlock(&list->mtx); // kilidi bırak

    return NULL;
}

int main()
{
    pthread_t t1, t2;
    t_list list1, list2;

    // Mutexleri başlat
    pthread_mutex_init(&list1.mtx, NULL);
    pthread_mutex_init(&list2.mtx, NULL);

    // Mesajları ata
    list1.text = "Ayse";
    list2.text = "Zehra";

    // Threadleri başlat
    pthread_create(&t1, NULL, print_message, &list1);
    pthread_create(&t2, NULL, print_message, &list2);
    
    // Threadlerin bitmesini bekle
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Mutexleri yok et
    pthread_mutex_destroy(&list1.mtx);
    pthread_mutex_destroy(&list2.mtx);

    return 0;
}
