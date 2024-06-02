#include <stdio.h>

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
    int n;
    printf("Introduceți poziția elementului în șirul lui Fibonacci: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Poziția trebuie să fie un număr pozitiv sau zero.\n");
    } else {
        unsigned long long result = fib(n);
        printf("Elementul de pe poziția %d în șirul lui Fibonacci este: %llu\n", n, result);
    }

    return 0;
}
