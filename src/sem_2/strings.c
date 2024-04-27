#include<stdio.h>
#include<string.h>

int main(){
    int n;
    scanf("%d", &n);
    char inputs[n][100000];
    int count[n];
    for(int i=0; i<n; i++){
        scanf("%[^\n]%*c", inputs[i]);
    }
    for(int j=0; j<n; j++){
        if(count[j]==-1){
            break;
        }
        for(int k=j+1; k<n; k++){
            if(0==strcmp(inputs[j], inputs[k])){
                count[k]=-1;
                count[j]++;
            }
        }
    }
    for(int l=0; l<n; l++){
        if(count[l]==2){
            printf("%s", inputs[l]);
        }
    }
}