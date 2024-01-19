#include <stdio.h>
#include <string.h>
int swap(char* x, char* y){
    char temp;
    temp=*x;
    *x=*y;
    *y=temp;
    return 0;
}
int perm(char* word, int x, int y){
    if (x==y){
        printf("%s\n", word);
    } else {
    for (int i=x;i<=y;i++){
            swap(word+x,word+i);
            perm(word, x+1, y);
            swap(word+x,word+i);
    }
    }
    return 0;
}
int main(){
    char word[8];
    scanf("%[^\n]%*c", word);
    int size=strlen(word);
    perm(word,0,size);
    return 0;
}