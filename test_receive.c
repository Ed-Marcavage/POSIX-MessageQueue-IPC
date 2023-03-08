/* pmsg_send.c

   Usage as shown in usageError().

   Send a message (specified as a command line argument) to a
   POSIX message queue.

   See also pmsg_receive.c.

   Linux supports POSIX message queues since kernel 2.6.6.
*/
#include <mqueue.h>
#include <fcntl.h>              /* For definition of O_NONBLOCK */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shm_channel.h"


#define MAX_MSG_SIZE 256
#define MAX_FILEPATH_LEN 256
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256

// typedef struct {
//     char file_path[MAX_FILEPATH_LEN];
//     char message[MAX_MSG_SIZE];
//     struct mq_attr Myattr;

// } mq_message_t;


int main(int argc, char *argv[])
{
    mq_message_t message_recv;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    //attr.mq_curmsgs = 0;
    attr.mq_msgsize = sizeof(message_recv);

    // const int BUF_SIZE = 1000;
    // char buf[BUF_SIZE];
    unsigned int prio = 0;

    mqd_t mqd;
    //mq_message_t message;

    //Sattr.mq_flags =0;
    //Sattr.mq_maxmsg = 10;
    //attr.mq_curmsgs = 0;
    //attr.mq_msgsize = 0;

    // attr.mq_maxmsg = 100;
    // attr.mq_msgsize = 1024;

    int flags;
    ssize_t nbytes;

    flags = O_RDONLY;
    // while ((opt = getopt(argc, argv, "n")) != -1) {
    //     switch (opt) {
    //     case 'n':   flags |= O_NONBLOCK;        break;
    //     default:    usageError(argv[0]);
    //     }
    // }

    // if (optind + 1 >= argc)
    //     usageError(argv[0]);

    mqd = mq_open("/mymq", flags, 0600, &attr);
    if (mqd == (mqd_t) -1)
        perror("mq_open failure from main");
        
    mq_getattr(mqd, &attr);
    // if (attr.mq_curmsgs > 0) {
    //     int nbytes = mq_receive(mqd, buf, sizeof(buf), &prio);
    //     printf("Received message: %s\n", buf);
    // } else {
    //     printf("No messages in queue\n");
    // }

    //printf("Num of Before recv messages: %ld\n", attr.mq_curmsgs);

    if(attr.mq_curmsgs == 0){
        printf("Empty MQ\n");
    }
    mq_getattr(mqd, &attr);
    while(attr.mq_curmsgs > 0){
    //mq_message_t message;
    printf("Num of before recv messages: %ld\n", attr.mq_curmsgs);
    nbytes = mq_receive(mqd, (char*) &message_recv, sizeof(message_recv), NULL);
    //buf[nbytes] = '\0';
    // printf("Read %s bytes from MQ\n", buf);
    // printf("Num of after recv messages: %ld\n", attr.mq_curmsgs);
    printf("Received message with file path: %s, message: %s\n", message_recv.file_path, message_recv.message);
    mq_getattr(mqd, &attr);
    printf("Num of after recv messages: %ld\n", attr.mq_curmsgs);
    //mq_getattr(mqd, &message.Myattr);
    }
    mq_close(mqd);

    exit(1);
}