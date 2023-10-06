#include <stdio.h>
#include <string.h>
int func(int place, int size, char word[]){
char comb[size];
for(int i=size-1;i>=0;i--){
    comb[place]=word[i];
    if (place+1<size){
        func(place+1, size, word);
    }
    printf("%s\n", comb);
    }    
    return 0;
}
int main(){
    char word[8];
    scanf("%[^\n]%*c", word);
    int size=strlen(word);
    func(0,size,word);
    return 0;
}