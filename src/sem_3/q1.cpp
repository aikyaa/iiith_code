
int cmp(const void* a, const void* b ){
    return *(int* a)-*(int* b);
}

int main(){
scanf("%d", &t);
int n=0;
int arr[n];
int dup[n];
for(int i=0; i<t;i++){
    scanf("%d", &n);
    for(int j=0; j<n; j++){
        scanf("%d ", &arr[j]);
        dup[j]
    }
    qsort(arr,n,sizeof(int),cmp);

}
return 0;
}

