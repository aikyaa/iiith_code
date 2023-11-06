#include<stdio.h>
#include<string.h>
#include <stdlib.h>

void swap(char *x, char *y) 
{ 
    char temp; 
    temp = *x; 
    *x = *y; 
    *y = temp;
} 
  
void permute(char permutations[][9],char *word, int l, int r, int n)
{
    int i;
    int k=0;
    if (l == r) {
        for(int e=0; e<n; e++){
            permutations[k][e]=*word;
        }
        k+=1;
    }
    else
    {
        for (i = l; i <= r; i++) 
        {
                swap((word + l), (word + i)); 
                permute(permutations,word, l + 1, r,n);
                swap((word + l), (word + i)); 
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
    char word[9];
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
    char permutations[factorial(n)][n];
    printf("%d\n", num);
    permute(permutations,word, 0, n-1, n); 
    //void qsort(permutations, factorial(n), n*sizeof(char), int (*compar)(const void *, const void*));
    for(int d=0; d<factorial(n); d++){
        for(int e=0; e<n; e++){
            printf("%c", permutations[d][e]);
        }
    }
    return 0; 
} 