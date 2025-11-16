// Write a program to implement different operations on 2-D array.

#include <stdio.h>
#define MAX 10
int main() {
    int matrix1[MAX][MAX], matrix2[MAX][MAX], result[MAX][MAX];
    int rows, cols, choice;

    // Take matrix dimensions as input
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    // Input elements for the first matrix
    printf("\nEnter elements of the first matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix1[i][j]);
        }
    }

    // Input elements for the second matrix
    printf("\nEnter elements of the second matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix2[i][j]);
        }
    }

    do {  // repeat opeartions until user wants to exit
        // Choice of operation
        printf("\nChoose the operation:\n");
        printf("Press 1 for Addition\n");
        printf("Press 2 for Subtraction\n");
        printf("Press 3 for Multiplication\n");
        printf("Press 4 for Transpose of first matrix\n");
        printf("Press 5 for Terminating the program\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Addition of two matrices
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        result[i][j] = matrix1[i][j] + matrix2[i][j];
                    }
                }
                printf("\nResult of Addition:\n");
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        printf("%d\t", result[i][j]);
                    }
                    printf("\n");
                }
                break;

            case 2:
                // Subtraction of two matrices
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        result[i][j] = matrix1[i][j] - matrix2[i][j];
                    }
                }
                printf("\nResult of Subtraction:\n");
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        printf("%d\t", result[i][j]);
                    }
                    printf("\n");
                }
                break;

            case 3:
                // Multiplication of two matrices
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        result[i][j] = 0;
                        for (int k = 0; k < cols; k++) {
                            result[i][j] += matrix1[i][k] * matrix2[k][j];
                        }
                    }
                }
                printf("\nResult of Multiplication:\n");
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        printf("%d\t", result[i][j]);
                    }
                    printf("\n");
                }
                break;

            case 4:
                // Transpose of the first matrix
                for (int i = 0; i < cols; i++) {
                    for (int j = 0; j < rows; j++) {
                        result[j][i] = matrix1[i][j];
                    }
                }
                printf("\nTranspose of the first matrix:\n");
                for (int i = 0; i < cols; i++) {
                    for (int j = 0; j < rows; j++) {
                        printf("%d\t", result[i][j]);
                    }
                    printf("\n");
                }
                break;
            case 5:
                // Exit the program
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
