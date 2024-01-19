#include <stdio.h>
int main(){
    char s[];
    scanf("%s", &s);
    char uppercase[]={A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z};
    char lowercase[]={a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z}
    int upper=0;
    int lower=0;
    int size=sizeof(s);
    int value=1;
    int count=0;
    int pass=1;
    for (int i=0; i<size;i++){
        for(int j=0; j<26; j++){
            if (uppercase[j]==s[i]){
                upper=1;
                break;
            }
            if (lowercase[j]==s[i]){
                lower=1;
                break;
            }
        }
        for(int k=i+1; k<size; k++){
            if (s[i]==s[k]){
                value=0;
            }
        }
        if (upper==0||lower==0){
            pass=0;
            break;
        }
        if (value==0){
            count+=1;
        }
    }
    if(count==0&&pass!=0){
        printf("Yes");
    } else {
        printf("No")
    }
    return 0;
}