#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct streply{
    char* username;
    char* content;
    struct streply* next_reply;
};

typedef struct streply* reply;

struct stcomment{
    char* username;
    char* content;
    reply list_of_replies;
    struct stcomment* next_comment;
    int reply_count;
    struct stcomment* prev_comment;
};

typedef struct stcomment* comment;

struct stpost{
    char* username;
    char* caption;
    comment list_of_comments;
    int comment_count;
    struct stpost* next_post;
};

typedef struct stpost* post;

struct stplatform{
    post list_of_posts;
    post last_viewed_post;
    int post_count;
};

typedef struct stplatform* Platform;

/////////////
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
///////////////////
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
///////////////////
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
////////////////
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
/////////////////////
int main(){
        int num_commands;
        scanf("%d", &num_commands);
        for(int z=0; z<num_commands; z++){
            char command[30];
            char username[100];
            char caption[100];
            char content[100];
            scanf("%s", command);
            if (strcmp("create_platform",command)==0){
                createPlatform();
            }
            else if(strcmp("add_post",command)==0){
                scanf("%s %s", &username, &caption);
                addPost(username, caption);
            }
            else if(strcmp("delete_post",command)==0){
                int n;
                scanf("%d", &n);
                if(!deletePost(n)){
                    printf("Post does not exist\n");
                }
            }
            else if(strcmp("view_post",command)==0){
                int n;
                scanf("%d", &n);
                post out=viewPost(n);
                if(out==NULL){
                    printf("Post does not exist\n");
                } else{
                    printf("%s %s\n", out->username, out->caption);
                }
            }
            else if(strcmp("current_post",command)==0){
                post out=currentPost();
                if(out==NULL){
                    printf("Post does not exist\n");
                } else{
                    printf("%s %s\n", out->username, out->caption);
                }
            }
            else if(strcmp("previous_post",command)==0){
                post out=previousPost();
                if(out==NULL){
                    printf("Post does not exist\n");
                } else{
                    printf("%s %s\n", out->username, out->caption);
                }
            }
            else if(strcmp("next_post",command)==0){
                post out=nextPost();
                if(out==NULL){
                    printf("Post does not exist\n");
                } else{
                    printf("%s %s\n", out->username, out->caption);
                }
            }
            else if(strcmp("view_comments",command)==0){
                comment dup=viewComments();
                while(dup!=NULL){
                printf("%s %s\n", dup->username, dup->content);
                while(dup->list_of_replies!=NULL){
                    printf("%s %s\n", dup->list_of_replies->username, dup->list_of_replies->content);
                    dup->list_of_replies=dup->list_of_replies->next_reply;
                }
                dup=dup->prev_comment;
                }
            }
            else if(strcmp("add_comment",command)==0){
                scanf("%s %s", &username, &content);
                addComment(username, content);
            }
            else if(strcmp("delete_comment",command)==0){
                int n;
                scanf("%d", &n);
                if(!deleteComment(n)){
                    printf("comment does not exist\n");
                }
            }
            else if(strcmp("add_reply",command)==0){
                int n;
                scanf("%s %s %d", &username, &content, &n);
                addReply(username, content,n);
            }
            else if(strcmp("delete_reply",command)==0){
                int n,m;
                scanf("%d %d", &n, &m);
                if(!deleteReply(n,m)){
                    printf("reply doesn't exist\n");
                }
            }   
        }
    return 0;
}