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
    int pos1, pos2;
    scanf("%d %d", &n, &k);
    char word[n];
    scanf("%s", word);
    int shift[n];
    for(int z=0;z<n;z++){
        pos1=pos(word[z]);
        if(k<=pos1){
            shift[z]=k;
            k=0;
        } 
        else{
            shift[z]=pos1;
            k=k-pos1;
        }
    }
        for(int x=n-1; x>=0; x--){
            if (k==0){
                break;
            }
            pos2=pos(word[x]);
            k+=shift[x];
            if (k<=25-pos2){
                shift[x]=k;
                k=0;
            } else if(k>25-pos2 && 25-pos2>pos2){
                shift[x]=25-pos2;
                k-=25-pos2;
            } else {
                k-=shift[x];
            }
        }
    int pos3;
    for(int y=0;y<n;y++){
        pos3=pos(word[y]);
        if (shift[y]<=pos3){
        word[y]=lowercase[pos3-shift[y]];
        } else {
        word[y]=lowercase[pos3+shift[y]];       
        }
    }
    if(k==0){
    printf("%s", word);
    } else{
        printf("-1");
    }
    return 0;
}