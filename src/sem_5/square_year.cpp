#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;


int main(){
    int testcases;
    cin >> testcases;
    for (int i=0; i<testcases; i++){
        string s;
        cin >> s;
        int snum=stoi(s);
        float srt=sqrt(snum);
        if (srt == int(srt) && srt>0){
            if (int(srt)%2 ==0) {
            cout<< int(srt/2) - 1 << " " <<int(srt/2)+1<<"\n";
            }else{
                cout<< int(srt/2) << " " <<int(srt/2)+1<<"\n";
            }
        }
        else if(srt==0){
            cout<<"0"<<" "<<"0"<<"\n";
        }
        else {
            cout<<"-1"<<"\n";
        }
    }
    return 0;
}