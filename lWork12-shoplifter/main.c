#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define NSHOP 5

static pthread_mutex_t foo_mutex = PTHREAD_MUTEX_INITIALIZER;

struct shop_t{
    int product;
    pthread_mutex_t door;
    pthread_mutexattr_t attr;
} typedef shop;

shop SHOPS[NSHOP];

int init_shops()
{
    for (size_t i = 0; i < NSHOP; i++)
    {
        SHOPS[i].product = rand() % 200 + 900;
        pthread_mutexattr_init(&SHOPS[i].attr);
        pthread_mutex_init(&SHOPS[i].door, &SHOPS[i].attr);
        printf("%d: %d\n", i+1, SHOPS[i].product);
    }
}

void destroy_shop()
{
    for (size_t i = 0; i < NSHOP; i++)
    {
        pthread_mutexattr_destroy(&SHOPS[i].attr);
        pthread_mutex_destroy(&SHOPS[i].door);
    }
}



int main(int argc, char* argv[])
{
    srand(time(NULL));
    init_shops();
    
    exit(0);
}