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

#define NSTORE 5
#define NCUST 3

struct store_t{
    int products;
    int customer_id;
    pthread_mutex_t door;
    pthread_mutexattr_t attr;
} typedef store;

struct customer_t{
    pthread_t ptcustomer_id;
    int customer_id;
    int requirement;
} typedef customer;

store STORES[NSTORE];
customer CUSTOMERS[NCUST];


static void init_stores()
{
    puts("create store..");
    for (size_t i = 0; i < NSTORE; i++)
    {

        STORES[i].products = rand() % 200 + 900;
        pthread_mutexattr_init(&STORES[i].attr);
        pthread_mutex_init(&STORES[i].door, &STORES[i].attr);
        // printf("%d: %d\n", i+1, STORES[i].product);
    }
}

static void destroy_store()
{
    puts("destroy store..");
    for (size_t i = 0; i < NSTORE; i++)
    {
        pthread_mutexattr_destroy(&STORES[i].attr);
        pthread_mutex_destroy(&STORES[i].door);
    }
}

static int go_to_store(customer* b, int store_id)
{
    int err, cnt = 0, ret = 1;
    printf("customer(%d) knocks on store(%d)\n", b->customer_id, store_id);
    if((err = pthread_mutex_trylock(&STORES[store_id].door)) == 0)
    {
        printf("customer(%d) entered the store(%d). Exists (%d)products\n", b->customer_id, store_id, STORES[store_id].products);
        
        STORES[store_id].customer_id = b->customer_id;
        if(STORES[store_id].products == 0){
            ret = 1;
        }
        else if(b->requirement > STORES[store_id].products){
            cnt = STORES[store_id].products;
            b->requirement-=cnt;
            STORES[store_id].products = 0;
            ret = 0;
        }
        else{
            cnt = b->requirement;
            STORES[store_id].products -= cnt;
            b->requirement = 0;
            ret = 0;
        }
        sleep(2);
        err = pthread_mutex_unlock(&STORES[store_id].door);
        if(err != 0)
            handle_error_en(err, "pthread_mutex_unlock");
        
        printf("customer(%d) buy (%d)product and left the store(%d)\n", b->customer_id, cnt, store_id);
        return ret;
    }
    else
    {
        printf("customer(%d) did not enter the store(%d)." 
                "There is already a buyer(%d)\n", b->customer_id, store_id, STORES[store_id].customer_id);
    }
    return ret;
}

static void* customer_work(void* arg)
{
    customer* b = arg;
    printf("customer(%d) with tid(%ld) created...\n", b->customer_id, b->ptcustomer_id);
    while (b->requirement > 0)
    {
        printf("customer(%d) needs to buy(%d). Go to shopping\n", b->customer_id, b->requirement);
        while(go_to_store(b, (rand()%NSTORE))) {sleep(2);};
        printf("customer(%d) remains(%d) go to sleep..Zzz\n", b->customer_id, b->requirement);
        sleep(5);
    }

    return NULL;
}

static void init_customer()
{
    int err;
    puts("create customers..");
    for (size_t i = 0; i < NCUST; i++)
    {
        CUSTOMERS[i].customer_id = i+1;
        CUSTOMERS[i].requirement = rand() % 2000 + 9000;

        err = pthread_create(&CUSTOMERS[i].ptcustomer_id, NULL, customer_work, &CUSTOMERS[i]);
        if (err != 0)
            handle_error_en(err, "pthread_create");
    }
    
}

static void* loader_work()
{
    puts("loader start work...");
    int err, cnt;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    while(1)
    {
        int store_id = rand() % NSTORE;
        printf("loader go to store(%d)..\n", store_id);
        
        err = pthread_mutex_lock(&STORES[store_id].door);
        if(err != 0) 
            handle_error_en(err, "loader pthread_mutex_lock");

        cnt = rand()%500+500;
        STORES[store_id].products += cnt;
        STORES[store_id].customer_id = -1;
        
        printf("loader added(%d) products and in the store(%d) became(%d) products\n"
                "\tloader go to reload...\n", cnt, store_id, STORES[store_id].products);
        pthread_mutex_unlock(&STORES[store_id].door);

        sleep(2);
    }
}

static void init_loader(pthread_t* pth_id)
{
    int err;
    err = pthread_create(pth_id, NULL, loader_work, NULL);
    if (err != 0)
        handle_error_en(err, "pthread_create");
}

static void wait_in_the_car(pthread_t pth_loader)
{
    int err;
    for (size_t i = 0; i < NCUST; i++)
    {
        err = pthread_join(CUSTOMERS[i].ptcustomer_id, NULL);
        if (err != 0)
            handle_error_en(err, "pthread_join");
        printf("the customer(%d) bought everything\n", CUSTOMERS[i].customer_id);
    }

    puts("finishing deliveries...");
    err = pthread_cancel(pth_loader);
    if(err != 0)
        handle_error_en(err, "pthread_cancel");
}



int main(int argc, char* argv[])
{
    pthread_t pth_loader;
    srand(time(NULL));
    init_stores();
    //create customer..
    init_customer();
    //create loader..
    init_loader(&pth_loader);

    wait_in_the_car(pth_loader);
    destroy_store();
    exit(0);
}