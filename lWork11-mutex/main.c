#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

static long A = 0;
long N = 100000000;
long NN=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutexattr_t xattr;

static void* do_async(void* arg)
{
    for (size_t i = 0; i < NN; i++)
    {
        long* tmp = &A;
        (*tmp)++;
        A = *tmp;
    }
}

static void* do_sync(void* arg)
{
    for (size_t i = 0; i < NN; i++)
    {
        pthread_mutex_lock(&mutex);
        long* tmp = &A;
        (*tmp)++;
        A = *tmp;
        pthread_mutex_unlock(&mutex);
    }
}

static void* do_atomic(void* arg)
{
    for (size_t i = 0; i < NN; i++)
    {
        atomic_fetch_add(&A, 1);
    }
}

void do_onethread()
{
    for (size_t i = 0; i < N; i++)
    {
        long* tmp = &A;
        (*tmp)++;
        A = *tmp;
    }

}

void main(int argc, char* argv[])
{
    int opt, err, npthread;
    pthread_t thread_id[100];

    while((opt = getopt(argc, argv, "lp:s:a:c:")) != -1)
    {
        switch (opt)
        {
            case 'l':
                printf("CPY COUNT: %ld  \n", sysconf(_SC_NPROCESSORS_CONF));
                exit(0);
                break;
            
            case 'p':
                npthread = atoi(optarg);
                NN = N/npthread;
                do_onethread();
                break;

            case 'a':
                puts("start async!!");
                npthread = atoi(optarg);
                NN = N/npthread;
                for (size_t i = 0; i < npthread; i++)
                {
                    err = pthread_create(&thread_id[i], NULL,
                            do_async, &npthread);
                    if (err != 0)
                        handle_error_en(err, "pthread_create");
                }
                for (size_t i = 0; i < npthread; i++)
                {
                    err = pthread_join(thread_id[i], NULL);
                    if (err != 0)
                        handle_error_en(err, "pthread_join");
                }
                break;

            case 's':
                puts("start sync!!");
                npthread = atoi(optarg);
                NN = N/npthread;
                for (size_t i = 0; i < npthread; i++)
                {
                    err = pthread_create(&thread_id[i], NULL,
                            do_sync, &npthread);
                    if (err != 0)
                        handle_error_en(err, "pthread_create");
                }
                for (size_t i = 0; i < npthread; i++)
                {
                    err = pthread_join(thread_id[i], NULL);
                    if (err != 0)
                        handle_error_en(err, "pthread_join");
                }
                break;

            case 'c':
                puts("start atomic!!");
                npthread = atoi(optarg);
                NN = N/npthread;
                for (size_t i = 0; i < npthread; i++)
                {
                    err = pthread_create(&thread_id[i], NULL,
                            do_atomic, &npthread);
                    if (err != 0)
                        handle_error_en(err, "pthread_create");
                }
                for (size_t i = 0; i < npthread; i++)
                {
                    err = pthread_join(thread_id[i], NULL);
                    if (err != 0)
                        handle_error_en(err, "pthread_join");
                }
                break;
            
            default:
                break;
        }
    }
    
    printf("A = %ld\n", A);
    
    exit(0);
}