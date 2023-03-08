#ifndef SHM_CHANNEL_H
#define SHM_CHANNEL_H

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_MSG_SIZE 256
#define MAX_FILEPATH_LEN 256
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                                   } while (0)

#define BUF_SIZE 1024   /* Maximum size for exchanged string */

/* Define a structure that will be imposed on the shared
memory object */

           struct shmbuf {
               sem_t  sem1;            /* POSIX unnamed semaphore */
               sem_t  sem2;            /* POSIX unnamed semaphore */
               size_t cnt;             /* Number of bytes used in 'buf' */
               char   buf[BUF_SIZE];   /* Data being transferred */
           };

typedef struct {
    char file_path[MAX_FILEPATH_LEN];
    char message[MAX_MSG_SIZE];
    struct mq_attr Myattr;

} mq_message_t;


#endif /* SHM_CHANNEL_H */