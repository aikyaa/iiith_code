#include<stdio.h>
#include<string.h>
int main()
{
    int n;int o;
    char v[300000];
    char temp;
    
    int k;
    char b;    
    scanf("%[^\n]%*c",v);
    scanf("%d",&n);
    int m=0;
     
    int p=strlen(v);
    
    for(int i=0;i<n;i++)
    {
        scanf("%d",&o);
        if(n==1 && o==1)
        {
            for(int i=0;i<(p/2);i++)
            {
            temp=v[p-i-1];
            v[p-i-1]=v[i];
            v[i]=temp;
            
            }
            break;
        }
        if(o==1)
        {   
            m=0;
            for(int j=i;j<n;j++)
            {
                scanf("%d",&o);
                if(o!=1)
                {
                    break;
                }
                m++;
            }
            i=i+m-1;
            
           // p=strlen(v);
           if(m%2!=0){
            for(int i=0;i<(p/2);i++)
            {
                temp=v[p-i-1];
                v[p-i-1]=v[i];
                v[i]=temp;
            }
            v[p]='\0';
           }
            //for(int i=0;i<p;i++)
            //{
             //   v[i]=r[i];
            //}
                           
        }
        if(o==2)
        {
            scanf("%d ",&k);
            scanf("%c",&b);           
            if(k==1)
            { 
               // p=strlen(v);
                v[p+1]='\0';
                memmove(v+1,v,p);
              //for(int i=p;i>0;i--)
              //{
                // v[i]=v[i-1];
              //}
              v[0]=b; 
              p=p+1;

            }
            else
            {
              //p=strlen(v);
              v[p]=b;
              v[p+1]='\0';
              p=p+1;
            }
        }
    }
    printf("%s",v);
    return 0;
}