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

struct shop_t{
    int product;
    pthread_mutex_t door;
    pthread_mutexattr_t attr;
} typedef shop;

struct buyer_t{
    pthread_t ptbayer_id;
    int bayer_id;
    int requirement;
} typedef bayer;

shop SHOPS[NSHOP];

static void init_shops()
{
    puts("create store..");
    for (size_t i = 0; i < NSHOP; i++)
    {

        SHOPS[i].product = rand() % 200 + 900;
        pthread_mutexattr_init(&SHOPS[i].attr);
        pthread_mutex_init(&SHOPS[i].door, &SHOPS[i].attr);
        // printf("%d: %d\n", i+1, SHOPS[i].product);
    }
}

static void destroy_shop()
{
    puts("destroy store..");
    for (size_t i = 0; i < NSHOP; i++)
    {
        pthread_mutexattr_destroy(&SHOPS[i].attr);
        pthread_mutex_destroy(&SHOPS[i].door);
    }
}

static int go_to_shop(bayer* b, int shop_id)
{
    int err;
    printf("customer(%d) knocks on store (%d)", b->bayer_id, shop_id);
    if((err = pthread_mutex_trylock(&SHOPS[shop_id].door)) == 0)
    {
        printf("customer(%d) entered the store (%d)", b->bayer_id, shop_id);
        //do...
        pthread_mutex_unlock(&SHOPS[shop_id].door);
        return 0;
    }
    else{
        handle_error_en(err, "mutex_trylock error!");
    }
    return 1;
}

static void* bayer_work(void* arg)
{
    bayer* b = arg;
    while (b->requirement > 0)
    {
        printf("bayer(%d) remains(%d) go to shopping", b->bayer_id, b->requirement);
        //go_to_shop
        while(go_to_shop(b, (rand()%5))) {};
        printf("bayer(%d) remains(%d) go to sleep...", b->bayer_id, b->requirement);
        sleep(10);
    }

    return NULL;
}



int main(int argc, char* argv[])
{
    srand(time(NULL));
    init_shops();
    //create customer..
    //create loader..
    destroy_shop();
    exit(0);
}