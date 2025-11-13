// WAP program o take user-defined numbers in a 2-D array and calculates the average.

#include <stdio.h>

int main() {
    int rows, cols;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    int arr[rows][cols];
    int sum = 0;
    int totalElements = rows * cols;

    printf("Enter %d Numbers :  ", totalElements);
    for (int i = 0; i < rows; i++) {
        for (int i = 0; i < cols; i++) {
            printf("Enter Number [%d][%d]: ", i + 1, i + 1);
            scanf("%d", &arr[i][i]);
            sum += arr[i][i];
        }
    }

    float avg = sum / (float) totalElements;
    printf("Average : %f", avg);

    return 0;
}