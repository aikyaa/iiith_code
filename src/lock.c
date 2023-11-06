#include <stdio.h>
#include <string.h>
int main(){
    char s[1001];
    scanf("%[^\n]%*c", s);
    int size=strlen(s);
    char str[size];
    char newstr[size];
    char temp[size];
    char maxstr[size];
    char minstr[size];
    strcpy(str, s);
    strcpy(maxstr, str);
    strcpy(minstr, str);
    strcpy(temp, str);
    for(int i=0; i<size; i++){
        newstr[size-1]=str[0];
            for(int j=1; j<size; j++){
                newstr[j-1]=str[j];
            }
        strcpy(str,newstr);
        if (strcmp(str, maxstr)>0){
            strcpy(maxstr, str);
            }
    }
    strcpy(str, temp);
    for(int k=0; k<size; k++){
        newstr[0]=str[size-1];
        for(int l=0; l<size-1; l++){
            newstr[l+1]=str[l];
        }
        strcpy(str,newstr);
        if (strcmp(newstr, minstr)<0){
            strcpy(minstr, str);
        }
    }
    for(int m=0; m<size; m++){
        printf("%c", minstr[m]);
    }
    printf("\n");
    for(int n=0; n<size; n++){
        printf("%c", maxstr[n]);
    }
}