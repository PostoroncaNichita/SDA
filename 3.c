#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initializeArray(int *array, int length);
void displayArray(int *array, int length);
void freeArray(int *array);
int linearSearch(int *array, int length, int number);
int binarySearch(int *array, int left, int right, int number);

int main() {
    int length, option, number;
    printf("Enter the length of the array: ");
    scanf("%d", &length);

    // Allocate memory for the array
    int *array = (int *)malloc(length * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    do {
        printf("\nMenu:\n");
        printf("1. Initialize array with random numbers\n");
        printf("2. Display array\n");
        printf("3. Linear search\n");
        printf("4. Binary search\n");
        printf("5. Free array memory and exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                initializeArray(array, length);
                printf("Array initialized successfully.\n");
                break;
            case 2:
                displayArray(array, length);
                break;
            case 3:
                printf("Enter the number to search for: ");
                scanf("%d", &number);
                linearSearch(array, length, number);
                break;
            case 4:
                printf("Enter the number to search for: ");
                scanf("%d", &number);
                // Before binary search, array needs to be sorted
                printf("Binary search requires the array to be sorted first.\n");
                printf("Enter option 1 to sort the array and try again.\n");
                break;
            case 5:
                freeArray(array);
                printf("Array memory freed. Exiting program.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 5);

    return 0;
}

void initializeArray(int *array, int length) {
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        array[i] = rand() % 100;
    }
}

void displayArray(int *array, int length) {
    printf("Array: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void freeArray(int *array) {
    free(array);
}

int linearSearch(int *array, int length, int number) {
    clock_t start = clock();
    for (int i = 0; i < length; i++) {
        if (array[i] == number) {
            clock_t end = clock();
            double executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Number found at index %d. Search time: %f seconds.\n", i, executionTime);
            return i;
        }
    }
    printf("Number not found in the array.\n");
    return -1;
}

int binarySearch(int *array, int left, int right, int number) {
    clock_t start = clock();
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (array[mid] == number) {
            clock_t end = clock();
            double executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Number found at index %d. Search time: %f seconds.\n", mid, executionTime);
            return mid;
        }
        if (array[mid] < number) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    printf("Number not found in the array.\n");
    return -1;
}
