#include <stdio.h>
#include <string.h>
int main(){
    int len,sublen;
    char lowercase[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    scanf("%d %d", &len, &sublen);
    char word[len+1];
    char str[len+1];
    scanf("%s", word);
    int count;
    int max=0;
    int pass=1;
    for(int i=0; i<26; i++){
        count=0;
        strcpy(str,word);
        for(int j=0;j<len;j++){
            pass=1;
            if(lowercase[i]==str[j]){
                for(int k=1; k<sublen; k++){
                    if(str[j]!=str[j+k]){
                        pass=0;
                        break;
                    }
                }
                if(pass==1){
                  j+=sublen-1;
                  count+=1;  
                }
            }
        }
        if(max<count){
            max=count;
        }
    }
    printf("%d", max);
    return 0;
}