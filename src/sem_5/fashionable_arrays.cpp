#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int ans = 0;

int op(list<int> arr){
    int key= (arr.front() + arr.back())% 2;
    if (key ==0) return ans;
    else{
        
            if (arr.front() % 2 != 0){
                int temp=arr.front();
                arr.pop_front();
                ans++;
                if((arr.front() + arr.back())% 2 != 0){
                   arr.push_front(temp);
                   ans--;
                }
                else{
                    return op(arr);
                }
                
            }
            if (arr.back() % 2 != 0){
                int temp2= arr.back();
                arr.pop_back();
                ans++;
                if((arr.front() + arr.back())% 2 != 0){
                   arr.push_front(temp2);
                   ans--;
                }
                else{
                    return op(arr);
                }
            }
            arr.pop_front();
    }
    return op(arr);
}

int main(){
    int testcases;
    cin >> testcases;
    for (int i=0; i<testcases; i++){
        ans=0;
        int n;
        cin >> n;
        vector<int> arr;
        for(int j=0; j<n; j++){
            int temp;
            cin>>temp;
            arr.push_back(temp);
        }
        sort(arr.begin(), arr.end());
        for(int j=0; j<n; j++){
            cout<<arr[j];
        }
        list<int> arrl(arr.begin(), arr.end());
        cout<<op(arrl)<<"\n";
    }
    return 0;
}