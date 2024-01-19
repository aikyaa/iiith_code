#include <stdio.h>
int pos(char x){
    char lowercase[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for(int a=0; a<26; a++){
        if (x==lowercase[a]){
            return a;
        }
    }
}
int f(int k,int n){
    static int sum=0;
    int i=0;
    while(sum<k){
    for(int b=0;b<n;b++){
      sum+=b;
      b=shift[i];
      i+=1;
      f(k-b,n-1);
    }
    }
    return 0;
}
int shift[n];
int main(){
    int n,k;
    scanf("%d %d", &n, &k);
    char word[n];
    scanf("%s", word);
    f(k,n);
    for(int c=0; c<n; c++){
        printf("%d", shift[c]);
    }
    return 0;
}