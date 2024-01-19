#include <stdio.h>
#include <stdlib.h>
int max_sum_of_irritations(int* irritation_value, int no_of_friends, int sum){
    int current_location=0;
    int sum_of_irritation=0;
    int max_sum=0;
    for(int start_location=0; start_location<no_of_friends; start_location++){
        sum_of_irritation=0;
        current_location=start_location;
        while(current_location<no_of_friends){
            sum_of_irritation+=irritation_value[current_location];
            current_location+=irritation_value[current_location];
        }
        if (max_sum<sum_of_irritation){
            max_sum=sum_of_irritation;
        }
        if (max_sum==sum){
            break;
        }
    }
    return max_sum;
}
int main(){
    int testcases;
    scanf("%d", &testcases);
    int results[testcases];
    for(int a=0;a<testcases;a++){
       int no_of_friends=0;
       int sum=0;
       scanf("%d", &no_of_friends); 
       int irritation_value[no_of_friends];
       for(int b=0;b<no_of_friends; b++){
         scanf("%d", &irritation_value[b]);
         sum+=irritation_value[b];
       }
       results[a]=max_sum_of_irritations(irritation_value,no_of_friends, sum);
    }
    for(int c=0;c<testcases;c++){
        printf("%d\n", results[c]);
    }
    return 0;
}