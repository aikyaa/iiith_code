#include <stdio.h>
#include <string.h>
int main(){
    char s[100];
    scanf("%[^\n]%*c", s);
    char uppercase[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char lowercase[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int upper=0;
    int lower=0;
    int size=strlen(s);
    int value=1;
    int pass=0;
    for (int i=0; i<size;i++){
        for(int j=0; j<26; j++){
            if (uppercase[j]==s[i]){
                upper=1;
                break;
            }
        }
        for(int j=0; j<26; j++){
            if (lowercase[j]==s[i]){
                lower=1;
                break;
            }
        }
        if (upper==1&&lower==1){
            pass=1;
            break;
        }
    }
    for (int b=0; b<size;b++){
        for(int c=b+1; c<size; c++){
            if (s[b]==s[c]){
                value=0;
                break;
            }
        }
        if (value==0){
            pass=0;
            break;
        }
    }
    if(pass!=0){
        printf("Yes");
    } else {
        printf("No");
    }
    return 0;
}