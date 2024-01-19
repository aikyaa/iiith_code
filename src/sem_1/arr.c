#include<stdio.h>
int main()
{
    int arr[] = {21, 16, 17, 4, 6, 3, 5, 2};

    int n = sizeof(arr)/sizeof(arr[0]);

    int max_from_right =  arr[n-1];
 
    printf("%d ", max_from_right);
     
    for (int i = n-2; i >= 0; i--)
    {
        if (max_from_right < arr[i])
        {          
            max_from_right = arr[i];
            printf("%d ",max_from_right);
        }
    }

    printf("\n");
 

    return 0;
} 