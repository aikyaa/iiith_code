#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include<string.h>

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