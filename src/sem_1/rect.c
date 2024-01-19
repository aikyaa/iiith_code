#include <stdio.h>
void main(){
    int w,h;
    scanf("%d %d", &w,&h);
if (w>=2 && h>=2)
{
    printf("o");
    for(int i=0; i<(w-2); i++)
    {
        printf("-");
    }
    printf("o\n");
    for(int j=0; j<(h-2); j++)
    {
        printf("|");
        for(int k=0; k<(w-2); k++)
        {
            printf(" ");
        }
        printf("|\n");
    }
    printf("o");
    for(int l=0; l<(w-2); l++){
        printf("-");
    }
    printf("o\n");
}
else if (h==1&&w>=2){
    printf("o");
    for(int i=0; i<(w-2); i++)
    {
        printf("-");
    }
    printf("o\n");
}
else if (w==1&&h>=2){
    printf("o");
    for(int i=0; i<(w-2); i++)
    {
        printf("\n|");
    }
    printf("o\n");
}
else{
    printf("o");
    for(int j=0;j<h;j++){
        for(int i=0; i<w; i++)
        {
            printf("-");
        }
        printf("\n");
    }
}
}
//1 3