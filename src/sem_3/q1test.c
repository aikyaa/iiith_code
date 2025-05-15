#include <stdio.h>
#include <stdlib.h>

// Struct to store rating and its index
typedef struct {
    int rating;
    int index;
} Problem;

// Comparator function to sort problems by rating
int compareByRating(const void *a, const void *b) {
    Problem *p1 = (Problem *)a;
    Problem *p2 = (Problem *)b;
    return p1->rating - p2->rating;
}

int main() {
    int n;
    printf("Enter the number of problems: ");
    scanf("%d", &n);

    Problem problems[n];

    // Reading the problem ratings
    printf("Enter the ratings of the problems: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &problems[i].rating);
        problems[i].index = i;
    }

    // Sort the problems by rating
    qsort(problems, n, sizeof(Problem), compareByRating);

    // Total time taken by Abhi
    int totalTime = 0;
    int currentIndex = problems[0].index; // Start with the first problem (lowest rating)

    // Solving the first problem
    totalTime += problems[0].rating;

    // Iterate through the sorted problems
    for (int i = 1; i < n; i++) {
        int nextIndex = problems[i].index;
        
        // Add time to move from current problem to the next problem
        totalTime += abs(currentIndex - nextIndex);
        
        // Add the time to solve the next problem
        totalTime += problems[i].rating;
        
        // Update current index
        currentIndex = nextIndex;
    }

    // Output the total time taken
    printf("Total time required: %d\n", totalTime);

    return 0;
}