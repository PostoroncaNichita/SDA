#include <stdio.h>
#include <time.h>

unsigned long long fib(int n) {
    unsigned long long a = 0, b = 1, temp;
    if (n == 0)
        return a;
    else if (n == 1)
        return b;
    else {
        for (int i = 2; i <= n; i++) {
            temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    }
}

int main() {
    int positions[] = {50, 100, 1000, 10000, 100000, 1000000};
    int num_positions = sizeof(positions) / sizeof(positions[0]);

    printf("Analiza empirică a timpului necesar pentru calculul numărului Fibonacci:\n");
    for (int i = 0; i < num_positions; i++) {
        int n = positions[i];
        clock_t start = clock();
        unsigned long long result = fib(n);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("fib(%d) = %llu, timp de calcul: %f secunde\n", n, result, time_taken);
    }

    return 0;
}
