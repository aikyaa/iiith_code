#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char command[7];
    int n;
    char choices[4][7]={"ADD", "SUB", "DOT","COSINE"};
    scanf("%[^ ]%*c %d", command, &n);
    typedef struct number{
        float values[n];
    } num;
    float mod(num arr, int n){
        float sum=0;
        for(int t=0; t<n; t++){
            sum+=arr.values[t]*arr.values[t];
        }
        return sqrt(sum);
    }
    num add(num c1, num c2, int n){
        num ans;
        for(int t=0; t<n; t++){
            ans.values[t]= c1.values[t]+c2.values[t];
        }
        return ans;
    }
    num sub(num c1, num c2, int n){
        num ans;
        for(int t=0; t<n; t++){
            ans.values[t]= c1.values[t]-c2.values[t];
        }
        return ans;
    }
    float dot(num c1, num c2, int n){
        float value;
        for(int t=0; t<n; t++){
            value+=c1.values[t]*c2.values[t];
        }
        return value;
    }
    float cosineSimilarity(num c1, num c2, int n){
        float value;
        value=(dot(c1,c2,n)/(mod(c1,n)*mod(c2,n)));
        return value;
    }    
    num c1,c2;
    while(command!="-1"){
        for(int m=0;m<n;m++){
            scanf(" %f",&c1.values[m]);
        }
        for(int o=0;o<n;o++){
            scanf(" %f",&c2.values[o]);
        }
    if (strcmp(command, choices[0])==0){
        printf("Result: ");
        for(int i=0; i<n; i++){
            printf("%.2f ", add(c1, c2,n).values[i]);
        }
    }
    else if(strcmp(command, choices[1])==0){
        printf("Result: ");
        for(int k=0; k<n; k++){
            printf("%.2f ", sub(c1, c2,n).values[k]);
        }
    }
    else if(strcmp(command, choices[2])==0){
        printf("Result: %.2f", dot(c1, c2,n));
    }
    else if(strcmp(command, choices[3])==0){   
        printf("Result: %.2f", cosineSimilarity(c1, c2,n));
    }
    return 0;
    }
}