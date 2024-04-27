#include<stdio.h>
#include<stdlib.h>

typedef long long int element;

void swap(element* a, element* b){
	element temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(element* array, element* array2, element n, element i){
    element child;
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

void heapsort(element* array, element* array2, element n){
    for(element i=n/2-1; i>=0; i--){
        heapify(array, array2, n, i);
    }
    for(element i=n-1; i>=0;i--){
        swap(&array[0], &array[i]);
		swap(&array2[0], &array2[i]);
        heapify(array,array2, i, 0);
    }
}

element* station_depths;
element* station_durations;
int main(){
    element station_count, initial_supply, final_depth, station_supply;
    scanf("%lld %lld %lld %lld", &station_count, &initial_supply, &final_depth, &station_supply);
    station_depths=(element*)malloc(station_count*sizeof(element));
    station_durations=(element*)malloc(station_count*sizeof(element));
    for(element t=0; t<station_count; t++){
        scanf("%lld", &station_depths[t]);
    }
    for(element u=0; u<station_count; u++){
        scanf("%lld", &station_durations[u]);
    }
	if(initial_supply>=final_depth){
		printf("0");
		return 0;
	}
    qsort(station_durations, station_count, sizeof(element), cmp())
    // element time=0;
    // element current_supply=initial_supply;
    // element current_depth=0;
	// heapsort(station_durations, station_depths, station_count);
	// for(element v=0; v<station_count; v++){
	// 	if(current_depth<station_depths[v] && station_depths[v]-current_depth<=current_supply){
    //         time+=station_durations[v];
    //         current_supply+=station_supply-(station_depths[v]-current_depth);
    //         current_depth=station_depths[v];
    //     }
    //     if(current_supply>=(final_depth-current_depth)){
    //         printf("%lld", time);
    //         return 0;
    //     }
    // }

    // time=0;
    // current_supply=initial_supply;
    // current_depth=0;
	// heapsort(station_depths, station_durations, station_count);
	// for(element v=0; v<station_count; v++){
	// 	if(station_depths[v]-current_depth<=current_supply){
    //         time+=station_durations[v];
    //         current_supply+=station_supply-(station_depths[v]-current_depth);
    //         current_depth=station_depths[v];
    //     }
    // }
    // current_depth+=current_supply;
    // printf("-1 %lld", current_depth);	
    return 0;
}