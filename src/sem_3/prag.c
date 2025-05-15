#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* rev(char* a, int j) {
    int len = strlen(a);
    int bound=j;
    char* b = (char*)malloc((len + 1) * sizeof(char)); 

    for (int i = 0; i < bound; i++) {
        b[bound - i - 1] = a[i];
    }
    for(int i=bound; i<len; i++){
        b[i]=a[i];
    }

    b[len] = '\0'; 
    return b;
}

int main() {
       
    int t;
    scanf("%d",&t);
    for (int m=0;m<t;m++)
    {
        int n;
        scanf("%d", &n);
        char str[100];   
       char strn[100] = "";  
       char* fin = NULL;     
       scanf("%s", str); 

    
       for (int j = 0; j < strlen(str); j++) {
        int len = strlen(strn);
        strn[len] = str[j];  
        strn[len + 1] = '\0'; 

        if (str[j] == '2' || str[j] == '3' || str[j] == '5' || str[j] == '7') {
            char* reversed = rev(strn, j);  
            strcpy(strn, reversed);      
            free(reversed);              
        }

        fin = strn;  
       }


         printf("%s\n", fin);  
    }
    return 0;
}