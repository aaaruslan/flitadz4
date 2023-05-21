#include <stdio.h>
#include <time.h>

#define MAX_VERTICES 310000

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] < temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int main() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int arr[MAX_VERTICES];
    int i = 0;

    clock_t start = clock();

    while (fscanf(file, "%d", &arr[i]) != EOF) {
        i++;
    }

    int num_vertices = i;

    shellSort(arr, num_vertices);

    printf("Sorted vertex degrees in descending order:\n");
    for (int j = 0; j < num_vertices; j++) {
        printf("%d ", arr[j]);
    }

    clock_t end = clock();

    double time_taken = (double) (end - start) / CLOCKS_PER_SEC;
    printf("\n\nRunning time: %lf seconds\n", time_taken);

    fclose(file);

    return 0;
}
