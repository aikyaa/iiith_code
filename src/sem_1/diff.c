#include <stdio.h>
char lowercase[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int pos(char x){
    for(int a=0; a<26; a++){
        char lowercase[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        if (x==lowercase[a]){
            return a;
        }
    }
}
int main(){
    int n,k;
    scanf("%d %d", &n, &k);
    char word[n];
    scanf("%s", word);
    int shift[n];
    for(int z=n-1;z>=0;z--){
        if(k<=25-pos(word[z])){
            shift[z]=k;
            k=0;
        } 
        else{
            shift[z]=25-pos(word[z]);
            k=k-25+pos(word[z]);
        }
    }
    char new[n];
    for(int y=0;y<n;y++){
        new[y]=lowercase[shift[y]+pos(word[y])];
    }
    if(k=0){
    printf("%s", new);
    } else{
        printf("-1");
    }
    return 0;
}