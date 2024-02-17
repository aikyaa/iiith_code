#include<stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "platform.h"
#include "comment.h"
#include "post.h"
#include "reply.h"
Platform pt;

Platform createPlatform(){
    //works
    pt=(Platform)malloc(sizeof(struct stplatform));
    //pt->list_of_posts = (post)malloc(sizeof(struct stpost));
    pt->list_of_posts=NULL;
    pt->post_count=0;
    pt->last_viewed_post=NULL;
    return pt;  
}

void freeReply(reply clear){
    free(clear->username);
    free(clear->content);
    free(clear);
}

void freeComment(comment clear){
    //free(clear->username);
    //free(clear->content);
    //clearing replies
    reply reply_to_clear;
    reply_to_clear=(reply)malloc(sizeof(struct streply));
    reply_to_clear=clear->list_of_replies;
    if (reply_to_clear!=NULL){
        while(reply_to_clear->next_reply!=NULL){
            reply temp=reply_to_clear;
            reply_to_clear=reply_to_clear->next_reply;
            freeReply(temp);
        }
        freeReply(reply_to_clear);
    }
    free(clear);
}

bool addPost(char* username, char* caption){
    //works
    if(pt!=NULL){
        post new_post=createPost(username, caption);
        new_post->next_post=pt->list_of_posts;
        pt->post_count++;
        pt->list_of_posts=new_post;
        return (new_post!=NULL);
    } else{
        //failed to add post
        return 0;
    }
}

bool deletePost(int n){
    //works
    if(pt!=NULL){
        Platform dup;
        dup=pt;
        //preventing attempts to access inexistent posts
        if(n>pt->post_count){
            return NULL;
        }
        //finding post prev to the one we have to delete
        while(n>2){
            dup->list_of_posts=dup->list_of_posts->next_post;
            n--;
        }
        //storing ptr to the post we gotta delete
        post temp=dup->list_of_posts->next_post;
        //making prev post point to next post(ignoring post to be deleted)
        dup->list_of_posts->next_post=dup->list_of_posts->next_post->next_post;
        //clearing comments
        comment clear=temp->list_of_comments;
        if(clear!=NULL){
            while(clear->next_comment!=NULL){
                comment temp2=clear;
                clear=clear->next_comment;
                freeComment(temp2);
            }
            freeComment(clear);
        }
        //check if deleted post is last viewed and change it
        if(temp==pt->last_viewed_post){
            pt->last_viewed_post=pt->list_of_posts;
        }
        free(temp);
        pt->post_count--;
        return 1;
    } else{
        //failed to delete comment
        return 0;
    }
}

post viewPost(int n){
    //works
    //preventing trying to access inexistent posts
    if(n>pt->post_count){
        return NULL;
    } else{
        Platform dup=pt;
        //finding the nth recent post
        for(int i=0; i<n-1; i++){
            dup->list_of_posts=dup->list_of_posts->next_post;
        }
        pt->last_viewed_post=dup->list_of_posts;
        return pt->last_viewed_post;
    }
}

post currentPost(){
    //works
    if(pt->last_viewed_post==NULL){
        //updating last viewed post with the most recently added post
        pt->last_viewed_post=pt->list_of_posts;
    }
    return pt->last_viewed_post;
}

post nextPost(){
    //works
    Platform dup=pt;
    if(pt->last_viewed_post==NULL){
        pt->last_viewed_post=pt->list_of_posts;
        return pt->last_viewed_post;
    } else{
        while(dup->list_of_posts->next_post!=pt->last_viewed_post){
            dup->list_of_posts=dup->list_of_posts->next_post;
        }
        pt->last_viewed_post=dup->list_of_posts;
        return pt->last_viewed_post;
    }
}

post previousPost(){
    //works
    if(pt->last_viewed_post->next_post==NULL){
        return pt->last_viewed_post;
    } else if(pt->last_viewed_post==NULL){
        pt->last_viewed_post=pt->list_of_posts->next_post;
        return pt->last_viewed_post;
    } else{
        pt->last_viewed_post=pt->last_viewed_post->next_post;
        return pt->last_viewed_post;
    }
}

bool addComment(char* username, char* content){
    pt->last_viewed_post->comment_count++;
    comment new_comment=createComment(username, content);
    new_comment->next_comment=pt->last_viewed_post->list_of_comments;
    //updating prev pointer
    if(pt->last_viewed_post->list_of_comments!=NULL){
        pt->last_viewed_post->list_of_comments->prev_comment=new_comment;
    }
    pt->last_viewed_post->list_of_comments=new_comment;
    pt->last_viewed_post->comment_count++;
    return 1;
}

bool deleteComment(int n){
    comment dup;
    dup=pt->last_viewed_post->list_of_comments;
    if(dup==NULL){
        return 0;
    }
    else{
        if(n>pt->last_viewed_post->comment_count){
            return 0;
        } else{
            pt->last_viewed_post->comment_count--;
            while(n>2){
                dup=dup->next_comment;
                n--;
            }
            comment temp=dup->next_comment;
            dup->next_comment=dup->next_comment->next_comment;
            free(temp);
            //freeComment(temp);
            return 1;
        }
    }
}

comment viewComments(){
    //works
    comment dup=pt->last_viewed_post->list_of_comments;
    while(dup!=NULL&&dup->next_comment!=NULL){
        dup=dup->next_comment;
    }
    //return or print
    return dup;
}

bool addReply(char* username, char* content, int n){
    comment dup1;
    dup1=pt->last_viewed_post->list_of_comments;
    while(n>1){
        dup1=dup1->next_comment;
        n--;
    }
    reply new_reply=createReply(username, content);
    new_reply->next_reply=dup1->list_of_replies;
    dup1->list_of_replies=new_reply;
    return 1;
}

bool deleteReply(int n, int m){
    post dup=pt->last_viewed_post;
    while(n>1){
        dup->list_of_comments=dup->list_of_comments->next_comment;
        n--;
    }
    while(m>2){
        dup->list_of_comments->list_of_replies=dup->list_of_comments->list_of_replies->next_reply;
        m--;
    }
    if(dup->list_of_comments->list_of_replies!=NULL){
        reply temp=dup->list_of_comments->list_of_replies->next_reply;
        dup->list_of_comments->list_of_replies->next_reply=dup->list_of_comments->list_of_replies->next_reply->next_reply;
        freeReply(temp);
        return 1;
    } else{
        return 0;
    }
}
