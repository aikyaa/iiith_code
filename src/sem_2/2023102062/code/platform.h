#ifndef _PLATFORM_H_
#define _PLATFORM_H_
#include "post.h"
#include "comment.h"
#include<stdbool.h>

struct stplatform{
    post list_of_posts;
    post last_viewed_post;
    int post_count;
};

typedef struct stplatform* Platform;

extern Platform pt;

void freeComment(comment clear);
void freeReply(reply clear);
Platform createPlatform();
bool addPost(char* username, char* caption);
bool deletePost(int n);
post viewPost(int n);
post currentPost();
post nextPost();
post previousPost();
bool addComment(char* username, char* content);
bool deleteComment(int n);
comment viewComments();
bool addReply(char* username, char* content, int n);
bool deleteReply(int n, int m);

#endif
