#include <stdio.h>
#include <string.h>
int main(){
    int len,sublen;
    char lowercase[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    scanf("%d %d", &len, &sublen);
    char word[len+1];
    char str[len+1];
    scanf("%s", word);
    int h[26];
    int max=0;
    int pass=1;
        for(int l=0;l<len;l++){
            pass=1;
            int count=0;
            strcpy(str,word);
            for(int m=1; m<sublen;m++){
                if(str[l]!=str[l+m]){
                    pass=0;
                    break;
                }
            }
            if(pass==1){
                for(int n=1; n<sublen;n++){
                    str[l+n]='0';
                }
                for(int o=0;o<26;o++){
                    h[o]=0;
                    if (str[l]==lowercase[o]){
                        h[o]+=1; 
                    }
                }
            }
        }
        for(int o=0;o<26;o++){
            if (max<h[o]){
                max=h[o];
            }
        }
        printf("%d", max);
        return 0;
}