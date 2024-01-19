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
  
void permute(char **permutations,char *word, int l, int r,int n)
{
    int i;
    static int k=0;
    int value=1;
    if (l == r) {
        for(int e=0; e<n; e++){
            permutations[k][e]=word[e];
        }
        permutations[k][n]='\0';
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
    int count[26]={};
    for(int a=0; a<n; a++){
        for(int b=0;b<26; b++){
            if (lowercase[b]==word[a]){
                count[b]+=1;
                break;
            }
        }
    }
    int rows=factorial(n);
    int num=rows;
    for(int c=0;c<26; c++){
        num=num/factorial(count[c]);
    }
    printf("%d", num);
    char **permutations = (char**) malloc((rows)*sizeof(char*));
    for(int z=0; z< rows; z++){
        permutations[z] = (char*)malloc((n+1)*sizeof(char));
    }
    permute(permutations,word, 0, n-1, n); 
    int pass=0;
    int result;
    char temp;
    for(int g=0; g<rows; g++){
        for(int p=0; p<n; p++){
         if(permutations[g-1][p]>permutations[g][p]){
            if (result>0){
                for(int h=0; h<n; h++){
                    temp=permutations[g-1][h];
                    permutations[g-1][h]=permutations[g][h];
                    permutations[g][h]=temp;
                }
                break;
            }
         }
        }
    }
    for(int d=0; d<rows; d++){
        for(int e=0; e<n; e++){
            if(permutations[d-1][e]!=permutations[d][e]){
                pass=1;
                break;
            }
        }
        if (pass==1){
            for(int e=0; e<n; e++){
                printf("%c", permutations[d][e]);
            }
            printf("\n");
        }
    }
    return 0;
} 