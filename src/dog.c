#include <stdio.h>
#include <string.h>
int str_rev(int size, char* str){
    char temp[size];
    strcpy(temp,str);
    for(int i=0; i<size; i++){
        str[i]=temp[size-1-i];
    }
    return 0;
}
int main(){
    int len,num_actions;
    scanf("%d", &len);
    char str[len];
    char extra;
    char newstr[len+1];
    scanf("%s", str);
    scanf("%d", &num_actions);
    for(int i=0; i<num_actions; i++){
        int action;
        int pos;
        scanf("%d", &action);
        if (action==1){
            str_rev(len, str);
        }
        else if(action==2){
            scanf(" %d", &pos);
            scanf(" %c", &extra);
            if(pos==1){
                newstr[0]=extra;
                for(int j=1; j<=len; j++){
                    newstr[j]=str[j-1];
                }
                strcpy(str, newstr);
            }
            else if (pos==2){
                newstr[len]=extra;
                for(int k=0; k<len; k++){
                    newstr[k]=str[k];
                }
                strcpy(str, newstr);
            }
        }
    }
    printf("%s", str);
    return 0;
}