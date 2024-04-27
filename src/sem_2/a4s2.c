#include <stdio.h>
#include <stdlib.h>


int no_of_chambers;
int possible=0;

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(int* array, int* array2, int n, int i){
    int child;
    child=2*i+1;
    if(child+1<n && array[child+1]<array[child]){
    child++;
    }
    if(child<n && array[i]>array[child]){
        swap(&array[child], &array[i]);
		swap(&array2[child], &array2[i]);
        heapify(array,array2,n,child);
    }
    
}

void heapsort(int* array,int* array2, int n){
    for(int i=n/2-1; i>=0; i--){
        heapify(array, array2, n, i);
    }
    for(int i=n-1; i>=0;i--){
        swap(&array[0], &array[i]);
		swap(&array2[0], &array2[i]);
        heapify(array,array2, n, i);
    }
}


void feasible_paths(int current_supply, int* visited, int current_index, int visited_count, int* min_oxygen_req, int* change_in_supply){
    if(possible==1) return;
    visited_count++;
    visited[current_index]=1;
    if(current_supply<min_oxygen_req[current_index]){
        visited[current_index]=0;
        return;
    }
    current_supply+=change_in_supply[current_index];
    if(current_supply<0){
        visited[current_index]=0;
        return;
    }
    if(visited_count==no_of_chambers && current_supply>=0){
        possible=1;
        return;
    }
    for(int i=0; i<no_of_chambers; i++){
        if(possible==1) return;
        if(visited[i]==0){
            feasible_paths(current_supply, visited, i, visited_count, min_oxygen_req, change_in_supply);
        }
    }
    if (possible==0) visited[current_index]=0;
}

int main(){
    int initial_supply;
    scanf("%d %d", &no_of_chambers, &initial_supply);
    int min_oxygen_req[no_of_chambers];
    int change_in_supply[no_of_chambers];
    int supply_check=initial_supply;
    for(int t=0; t<no_of_chambers; t++){
        scanf("%d", &min_oxygen_req[t]);
    }
    
    int visited[no_of_chambers];
    for(int u=0; u<no_of_chambers; u++){
        scanf("%d", &change_in_supply[u]);
        supply_check+=change_in_supply[u];
        visited[u]=0;
    }
    if(supply_check<0){
        printf("NO");
        return 0;
    }
    heapsort(min_oxygen_req,change_in_supply, no_of_chambers);
    
    for(int i=0; i<no_of_chambers; i++){
        feasible_paths(initial_supply, visited, i, 0, min_oxygen_req, change_in_supply);
        if(possible==1) break;
        visited[i]=0;
    }

    if(possible==1) printf("YES");
    else printf("NO");
    return 0;
}