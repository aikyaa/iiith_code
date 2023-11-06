#define MAX_CHARACTERS 50
#include<stdio.h>
#include<stdlib.h>
typedef enum TAccountType {
    savings,
    current,
} AccountType;

typedef struct TAccountInfo {
    int account_number;
    AccountType account_type;
    char name[MAX_CHARACTERS];
    float balance;
} AccountInfo;

void display(){
    printf("Account Number\tAccount Type\t\tName\t\tBalance\n");
    printf("---------------------------------------------------------\n");

}

int main(){
    AccountInfo 101={}
}