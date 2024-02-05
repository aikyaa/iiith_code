#ifndef _POST_H_
#define _POST_H_
#include "comment.h"

struct stpost{
    char* username;
    char* caption;
    comment list_of_comments;
    int comment_count;
    struct stpost* next_post;
};

typedef struct stpost* post;

post createPost(char* username, char* caption);

#endif
