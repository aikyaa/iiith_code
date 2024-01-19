#include <stdio.h>
check(char* sub1, char* sub2){
    if(sub1[2]==sub2[1] && sub1[1]!=sub2[2]){
        return 1;
    }
    else if(sub1[1]==sub1[1] && sub1[2]!=sub2[2]){
        return 1;
    }
    else if(sub1[1]!=sub1[1] && sub1[2]==sub2[2]){
        return 1;
    }
    else if(sub1[2]!=sub2[1] && sub1[1]==sub2[2]){
        return 1;
    }
    return 0;
}
int main(){
    int len, sub_len;
    scanf("%d %d", &len, &sub_len);
    char str[len+1];
    scanf("%s", str);
    int count;
    for(int i=0; i<len; i++){
        
    }
    count+=
}