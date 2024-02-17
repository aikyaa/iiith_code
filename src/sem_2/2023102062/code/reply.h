#ifndef _REPLY_H_
#define _REPLY_H_

struct streply{
    char* username;
    char* content;
    struct streply* next_reply;
};

typedef struct streply* reply;

reply createReply(char* username, char* content);

#endif