// WAP to take 10 numbers from the user, store them in a 1-D array, and calculate the average.

#include <stdio.h>

int main() {
    int arr[10];
    int sum = 0;
    printf("Enter 10 numbers:\n");
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("Enter Number %d: ", i + 1);
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    float avg = sum / 10.0;

    printf("Average : %f", avg);

    return 0;
}