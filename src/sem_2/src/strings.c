#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    char* inputs[n];
    int count[n];
    for(int h=0; h<n; h++){
        inputs[h]=(char *)malloc(100*sizeof(char));
    }
    for(int i=0; i<n; i++){
        //scanf("%[^\n]%*c", &inputs[i]);
        scanf("%s", inputs[i]);
        count[i]=1;
    }
    for(int j=0; j<n; j++){
        if(count[j]!=-1){   
            for(int k=j+1; k<n; k++){
                if(0==strcmp(inputs[j], inputs[k])){
                    count[k]=-1;
                    count[j]++;
                }
            }
        }
    }
    for(int l=0; l<n; l++){
        if(count[l]==2){
            printf("%s", inputs[l]);
        }
    }
}