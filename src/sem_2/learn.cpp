#include <bits/stdc++.h>
using namespace std;
// or #include <iostream>
// g++ learn.c; ./a.out
int main(){
int a;
cin >> a;
cout<<"a= "<<a<<endl;

//vectors
vector<int> v1(5,0); //initial length, value
vector<int> v2={1,2,3,4,5};
v2.push_back(6); //insert at end
v2.push_back(7);
v2.pop_back(); //delete last element
for(int i=0; i<v2.size(); i++){
    cout<<v2[i]<<" ";
}
return 0;
}