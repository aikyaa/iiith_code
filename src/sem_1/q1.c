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

void display(AccountInfo *list, int n){
    printf("Account Number\tAccount Type\t\tName\t\tBalance\n");
    printf("---------------------------------------------------------\n");
    for(int i=0; i<n; i++){
        printf("%d           \t%s      \t\t%s\t\t%f\n", list[i].account_number, list[i].account_type, list[i].name, list[i].balance);
    }
}
void lowBalanceAccounts(AccountInfo *list, int n){
    for(int i=0; i<n; i++){
        if(list[i].balance<100){
            printf("Account Number: %d, Name: %s",list[i].account_number, list[i].name);
        }
    }
}
void transaction(int accountNumber, float amount, int code, float balance){
    if (code==0){
        if((balance-amount)<100){
            printf("The balance is insufficient for the specified withdrawal.");
            return;
        }
        balance-=amount;
    }
    else {
        balance+=amount;
    }
}