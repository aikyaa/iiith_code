#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
    char *str= (char*) malloc(300010*sizeof(char));
    scanf("%s", str);
    int num_actions,len, action, pos;
    len=strlen(str);
    scanf("%d", &num_actions);
    char extra, temp;
    int prev=0;
    for(int i=0; i<num_actions; i++){
        scanf("%d", &action);
        if (action==1){
                prev+=1;
        if (i==num_actions-1 && prev%2!=0){
            for(int o=0; o<len/2; o++){
                temp=str[o];
                str[o]=str[len-1-o];
                str[len-1-o]=temp;
            }
        }
        }
        else{
            if(prev%2!=0){
                for(int o=0; o<len/2; o++){
                temp=str[o];
                str[o]=str[len-1-o];
                str[len-1-o]=temp;
            }
            }
            prev=0;
            scanf(" %d %c", &pos, &extra);
            if(pos==1){
                for(int j=len-1; j>=0; j--){
                    str[j+1]=str[j];
                }
                str[0]=extra;
            }
            else{
                str[len]=extra;
            }
            len+=1;
        }
    }
    printf("%s", str);
    return 0;
}