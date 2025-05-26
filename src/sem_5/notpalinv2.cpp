#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;


int main(){
    int testcases;
    cin >> testcases;
    for (int i=0; i<testcases; i++){
        int n, k;
        cin>>n>>k;
        string s;
        cin >> s;
        int k_curr=0; 
        int count1=0; 
        int count0 =0;
        int countav1=0;
        int countav0=0;
        //cout<<n;
        for(int j=0; j<(n/2); j++){
            if(s[j]==s[n-j-1]){
                k_curr++;
                if(s[j]==1) count1++;
                else count0++;
            } else{
                countav0++;
                countav1++;
            }
        }
        int c1=(2*count1)+countav1;
        int c0=(2*count0)+countav0;
        //cout<< k_curr<<" "<<count1<<" "<<count0;

        int diff=abs(k- k_curr);

        if((abs(c1-c0))/2 >= k && max(c1,c0) - abs(c1-c0) >= ((n/2) - k) && min(c1, c0)) cout<<"YES"<<"\n";

        else{
            cout<<"NO"<<"\n";
        }
        }
    
    return 0;
}