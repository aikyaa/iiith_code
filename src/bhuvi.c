#include <stdio.h>
int main()
{
	int n,i,j,k;
	int flag=1;
	scanf("%d",&n);
	int count=n;
	int arr[n];
	for (i=0; i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	for (i=0;i<n;i++)
	{
		for (j=i+1;j<n;j++)
		{
			flag=1;
			if (arr[i]==arr[j])
			{
				//printf("%d %d",i,j);
				for(k=1;k<=(j-i)/2;k++)
				{
					if (arr[i+k]!=arr[j-k])
					flag=0;
					break;
				}
			
				if (flag==1)
				{
					count++;
					//printf("%d %d\n",i,j);
				}
			}
			
		}
	}
	printf("%d",count);
	return 0;
}