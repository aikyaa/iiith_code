#include<stdlib.h>
#include "reply.h"

reply createReply(char* username, char* content){
    reply new_reply;
    new_reply=(reply)malloc(sizeof(struct streply));
    new_reply->username=(char *)malloc(sizeof(char)*100);
    new_reply->username=username;
    new_reply->content=(char *)malloc(sizeof(char)*100);
    new_reply->content=content;
    new_reply->next_reply=NULL;
    return new_reply;
}