#include<stdio.h>
#include<stdlib.h>
#include "comment.h"

comment createComment(char* username, char* content){
    comment new_comment;
    new_comment=(comment)malloc(sizeof(struct stcomment));
    new_comment->username=(char *)malloc(sizeof(char)*100);
    new_comment->username=username;
    new_comment->content=(char *)malloc(sizeof(char)*100);
    new_comment->content=content;
    new_comment->next_comment=NULL;
    new_comment->list_of_replies=NULL;
    new_comment->reply_count=0;
    new_comment->prev_comment=NULL;
    return new_comment;
}