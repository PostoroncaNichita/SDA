#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize(int *array, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100; // Generate random numbers between 0 and 99
    }
}

void display(int *array, int size) {
    if (array == NULL) {
        printf("Array not initialized.\n");
        return;
    }
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void release(int *array) {
    free(array);
}

void selectionSort(int *array, int size) {
    if (array == NULL) {
        printf("Array not initialized.\n");
        return;
    }
    clock_t start = clock();
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        // Swap elements
        int temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
    }
    clock_t end = clock();
    printf("Selection sort executed in %.6f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    int choice, size;
    int *array = NULL;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    do {
        printf("\nMenu:\n");
        printf("1. Initialize array with random numbers\n");
        printf("2. Display array\n");
        printf("3. Release memory\n");
        printf("4. Sort using selection sort\n");
        printf("5. Sort using merge sort, quick sort, or heap sort\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initialize(array, size);
                printf("Array initialized.\n");
                break;
            case 2:
                display(array, size);
                break;
            case 3:
                release(array);
                array = NULL; // Reset array pointer after releasing memory
                printf("Memory released.\n");
                break;
            case 4:
                selectionSort(array, size);
                break;
            case 5:
                printf("Functionality not implemented.\n");
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
