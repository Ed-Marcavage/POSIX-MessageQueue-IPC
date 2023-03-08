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

//#include "shm_channel.h"


// typedef struct {
//     char file_path[MAX_FILEPATH_LEN];
//     char message[MAX_MSG_SIZE];
//     struct mq_attr Myattr;

// } mq_message_t;


int main(int argc, char *argv[])
{
    int flags, opt;
    mqd_t mqd;
    struct mq_attr attr;
    mq_message_t message;


    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_curmsgs = 0;
    attr.mq_msgsize = sizeof(message);

    unsigned int prio;

    flags = O_CREAT | O_WRONLY;

    mqd = mq_open("/mymq", flags, 0600, &attr);
    if (mqd == (mqd_t) -1)
        perror("mq_open failure from main");


    strncpy(message.file_path, "mypath/path/to/file", MAX_FILEPATH_LEN);
    strncpy(message.message, "Hey!", MAX_MSG_SIZE);
    message.Myattr = attr;


   for(int i = 0; i < 4; i++) {
        if (mq_send(mqd, (const char*)&message, sizeof(message), 0)== -1)
            perror("mq_send failure from main");
    }

    mq_unlink("/mymq");
    exit(1);
}