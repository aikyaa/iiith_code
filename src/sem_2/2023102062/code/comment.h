#ifndef _COMMENT_H_
#define _COMMENT_H_
#include "reply.h"

struct stcomment{
    char* username;
    char* content;
    reply list_of_replies;
    struct stcomment* next_comment;
    int reply_count;
    struct stcomment* prev_comment;
};

typedef struct stcomment* comment;

comment createComment(char* username, char* content);

#endif