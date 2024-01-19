#include<stdio.h>
#include<string.h>
void permute(char *word,int n, int d) {
    char comb[n];
    for(int e=0; e<n; e++){
        while (d<n){
        comb[d]=word[e];
        permute(word,n,d+1);
        }
    }
}

int factorial(int n){
    if(n==0){
        return 1;
    } else{
    return n*factorial(n-1);
    }
}
  
int main() 
{ 
    char word[8];
    char lowercase[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    scanf("%[^\n]%*c", word); 
    int n = strlen(word); 
    int count[25]={};
    for(int a=0; a<n; a++){
        for(int b=0;b<26; b++){
            if (lowercase[b]==word[a]){
                count[b]+=1;
                break;
            }
        }
    }
    int num=factorial(n);
    for(int c=0;c<26; c++){
        num=num/factorial(count[c]);
    }
    printf("%d\n", num);
    permute(word, 0, n-1); 
    return 0; 
} 