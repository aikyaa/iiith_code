#include <stdio.h>
#include <math.h>
float mod(float* arr, int n){
    float sum=0;
    for(int i=0; i<n; i++){
        sum+=arr[i]*arr[i];
    }
    return sqrt(sum);
}
float* add(float* arr1, float* arr2, int n){
    float new[n];
    for(int i=0; i<n; i++){
        new[i]=arr1[i]+arr2[i];
    }
    return new;
}
float* sub(float* arr1, float* arr2, int n){
    float new[n];
    for(int i=0; i<n; i++){
        new[i]=arr1[i]-arr2[i];
    }
    return new;
}
float dot(float* arr1, float* arr2, int n){
    float value=1.0;
    for(int i=0; i<n; i++){
        value*=arr1[i]*arr2[i];
    }
    return value;
}
float cosineSimilarity(float* arr1, float* arr2, int n){
    float value=1.0;
    value=dot(arr1,arr2,n)/(mod(arr1,n)*mod(arr2,n));
    return value;
}
int main(){
    int n;
    scanf("%d", &n);
    float arr1[n];
    float arr2[n];
    float result[n];
    for(int i=0; i<n; i++){
        scanf("%f", &arr1[i]);
    }
    for(int j=0; j<n; j++){
        scanf("%f", &arr2[j]);
    }
    int choice;
    scanf("%d", &choice);
    if (choice==1){
        add(arr1, arr2,n);
    }
    else if(choice==2){
        sub(arr1, arr2,n);
    }
    else if(choice==3){
        dot(arr1, arr2,n);
    }
    else if(choice==4){
        cosineSimilarity(arr1, arr2,n);
    }
    for(int k=0; k<n; k++){
        printf("%f", result[k]);
    }
    return 0;
}