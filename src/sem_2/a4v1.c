#include<stdio.h>
#include<stdlib.h>

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(int* array, int* array2, int n, int i){
    int child;
    child=2*i+1;
    if(child+1<n && array[child+1]>array[child]){
    child++;
    }
    if(child<n && array[i]<array[child]){
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
        heapify(array,array2, i, 0);
    }
}

int main(){
    int station_count, initial_supply, final_depth, station_supply;
    scanf("%d %d %d %d", &station_count, &initial_supply, &final_depth, &station_supply);
    int station_depths[station_count],station_durations[station_count];
    for(int t=0; t<station_count; t++){
        scanf("%d", &station_depths[t]);
    }
    for(int u=0; u<station_count; u++){
        scanf("%d", &station_durations[u]);
    }
	if(initial_supply>=final_depth){
		printf("0");
		return 0;
	}
    int time=0;
    int current_supply=initial_supply;
    int current_depth=0;
	heapsort(station_durations, station_depths, station_count);
    // for(int w=0; w<station_count; w++){
    //     //printf("%d ", station_depths[w]);
    //     printf("%d ", station_durations[w]);
    // }
    // printf("\n");
	for(int v=0; v<station_count; v++){
		if(station_depths[v]-current_depth<=current_supply){
            time+=station_durations[v];
            current_supply+=station_supply-(station_depths[v]-current_depth);
            current_depth=station_depths[v];
        }
        if(current_supply>=(final_depth-current_depth)){
            printf("%d", time);
            return 0;
        }
    }
    
    time=0;
    current_supply=initial_supply;
    current_depth=0;
	heapsort(station_depths, station_durations, station_count);
	for(int v=0; v<station_count; v++){
		if(station_depths[v]-current_depth<=current_supply){
            time+=station_durations[v];
            current_supply+=station_supply-(station_depths[v]-current_depth);
            current_depth=station_depths[v];
        }
    }
    current_depth+=current_supply;
    printf("-1 %d", current_depth);	
    return 0;
}