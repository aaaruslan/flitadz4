#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int source, destination;
} Edge;

typedef struct {
    int number_of_vertices, number_of_edges;
    Edge* edges;
} Graph;

Graph* createGraph(int number_of_vertices, int number_of_edges) {
    Graph* graph = malloc(sizeof(Graph));
    graph->number_of_vertices = number_of_vertices;
    graph->number_of_edges = number_of_edges;
    graph->edges = (Edge*)malloc(number_of_edges * sizeof(Edge));
    return graph;
}

void freeGraph(Graph* graph) {
    free(graph->edges);
    free(graph);
}

void shellSort(int arr[], int n, int degree[]) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && degree[arr[j - gap]] < degree[temp]; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int main() {
    FILE* file = fopen("graph.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    int source, destination;
    int max_vertex = 0;
    int number_of_edges = 0;

    while (fscanf(file, "%d %d", &source, &destination) != EOF) {
        if (source > max_vertex)
            max_vertex = source;
        if (destination > max_vertex)
            max_vertex = destination;
        number_of_edges++;
    }

    int number_of_vertices = max_vertex + 1;

    Graph* graph = createGraph(number_of_vertices, number_of_edges);

    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < number_of_edges; i++) {
        fscanf(file, "%d %d", &(graph->edges[i].source), &(graph->edges[i].destination));
    }

    fclose(file);

    int* degrees = (int*)calloc(number_of_vertices, sizeof(int));
    for (int i = 0; i < number_of_edges; i++) {
        degrees[graph->edges[i].source]++;
        degrees[graph->edges[i].destination]++;
    }

    int* vertices = (int*)malloc(number_of_vertices * sizeof(int));
    for (int i = 0; i < number_of_vertices; i++) {
        vertices[i] = i;
    }

    clock_t start = clock();

    shellSort(vertices, number_of_vertices, degrees);

    printf("Vertices sorted in descending order of degree:\n");
    for (int i = 0; i < number_of_vertices; i++) {
        printf("%d ", vertices[i]);
    }
    printf("\n");

    clock_t end = clock();

    double time_taken = (double) (end - start) / CLOCKS_PER_SEC;
    printf("\n\nRunning time: %lf seconds\n", time_taken);

    freeGraph(graph);
    free(degrees);
    free(vertices);

    return 0;
}
