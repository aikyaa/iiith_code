#include <stdio.h>
int main(){
    int n;
    scanf("%d", &n);
    char str[n+1];
    scanf("%s", str);
    int count=0;
    for(int i=0; i<n; i++){
        if (str[i]=='"'){
            count+=1;
        }
        else if (str[i]==','){
            if(count%2==0){
                str[i]='*';
            }
        }
    }
    printf("%s", str);
    return 0;
}