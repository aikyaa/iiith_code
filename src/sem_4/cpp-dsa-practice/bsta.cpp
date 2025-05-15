#include <bits/stdc++.h>
using namespace std;

int binary_search(int target, int arr[], int low, int high){
    int mid=(low+high)/2;
    while(low<=high){
        if(arr[mid]==target)
            return mid;
        if(arr[mid]<target)
            return binary_search(target, arr, mid+1, high);
        if(arr[mid]>target)
            return binary_search(target, arr, low, mid-1);
    }
    return -1;
}

int main(){
    int arr[] = {1, 3, 6, 8, 13};
    int n = sizeof(arr)/sizeof(arr[0]);
    int ans = binary_search(7, arr, 0, n-1);
    cout << ans;
    return 0;
}