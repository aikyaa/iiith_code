#include<stdio.h>
#include<stdlib.h>
#include "post.h"

post createPost(char* username, char* caption){
    post new_post;
    new_post=(post)malloc(sizeof(struct stpost));
    new_post->username=(char *)malloc(sizeof(char)*100);
    new_post->username=username;
    new_post->caption=(char *)malloc(sizeof(char)*100);
    new_post->caption=caption;
    new_post->next_post=NULL;
    new_post->list_of_comments=NULL;
    new_post->comment_count=0;
    return new_post;
}