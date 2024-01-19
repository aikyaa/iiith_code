#include<stdio.h>
#include<string.h>
int factorial(int n){
    if(n==0){
        return 1;
    } else{
    return n*factorial(n-1);
    }
}
void swap(char *x, char *y) 
{ 
    char temp; 
    temp = *x; 
    *x = *y; 
    *y = temp;
} 
int permute(char *position, int l, int r, char strings[][8])
{
    int k=0;
    if (l == r) {
        for(int j=0;j<n;j++){
        strings[k][j]=position[j];
        k+=1;   
        }
        printf("%s\n", position); 
    } else {
        for (int i = l; i <= r; i++) {
                swap((position + l), (position + i)); 
                permute(position, l + 1, r,strings);
                swap((position + l), (position + i)); 
        } 
    } 
    return k;
} 
int pos(char x){
    for(int a=0; a<26; a++){
        char lowercase[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        if (x==lowercase[a]){
            return a;
        }
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
    char position[n];
    for(int d=0;d<n;d++){
        position[d]=pos(word[d]);
    }
    char strings[num][n];
    int val=permute(position, 0, n-1,n,strings); 
    int var=0;
    char printed[num][n];
    //if printed then don't
    int q=0;
    int pass=1;
    for(int e=0;e<q;e++){
        for(int f=0;f<n;f++){
            if(strings[e][f]!=printed[q][f]){
                var=1;
            }
        }
        if (var==0){
            pass=0;
            break;
        }
    }
    if(pass==1){
        printf("%s", strings[])
    }
    return 0; 
} 