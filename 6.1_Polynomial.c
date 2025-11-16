// Write a program to implement polynomial addition, subtraction and sparse matrix.

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

// ----------- POLYNOMIAL STRUCTURE -----------
typedef struct {
    int coeff;
    int exp;
} term;

// Function to read polynomial
int readPolynomial(term poly[]) {
    int n;
    printf("Enter number of terms in polynomial: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d%d", &poly[i].coeff, &poly[i].exp);
    }
    return n;
}
 
// Function to display polynomial
void displayPolynomial(term poly[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d(x^%d)", poly[i].coeff, poly[i].exp);
        if (i < n - 1) printf(" + ");
    }
    printf("\n");
}
 
// Polynomial addition
int addPolynomial(term p1[], int n1, term p2[], int n2, term res[]) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (p1[i].exp > p2[j].exp) {
            res[k++] = p1[i++];
        } else if (p1[i].exp < p2[j].exp) {
            res[k++] = p2[j++];
        } else {
            res[k].exp = p1[i].exp;
            res[k].coeff = p1[i].coeff + p2[j].coeff;
            i++; j++; k++;
        }
    }
    while (i < n1) res[k++] = p1[i++];
    while (j < n2) res[k++] = p2[j++];
    return k;
}
 
// Polynomial subtraction
int subPolynomial(term p1[], int n1, term p2[], int n2, term res[]) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (p1[i].exp > p2[j].exp) {
            res[k++] = p1[i++];
        } else if (p1[i].exp < p2[j].exp) {
            res[k] = p2[j];
            res[k].coeff = -res[k].coeff;
            j++; k++;
        } else {
            res[k].exp = p1[i].exp;
            res[k].coeff = p1[i].coeff - p2[j].coeff;
            i++; j++; k++;
        }
    }
    while (i < n1) res[k++] = p1[i++];
    while (j < n2) {
        res[k] = p2[j];
        res[k].coeff = -res[k].coeff;
        j++; k++;
    }
    return k;
}
 
// ----------- SPARSE MATRIX -----------
typedef struct {
    int row, col, value;
} sparse;
 
// Function to read sparse matrix
int readSparse(sparse mat[]) {
    int rows, cols;
    printf("Enter number of rows and columns: ");
    scanf("%d%d", &rows, &cols);
 
    int nonZero;
    printf("Enter number of non-zero elements: ");
    scanf("%d", &nonZero);
 
    mat[0].row = rows;
    mat[0].col = cols;
    mat[0].value = nonZero;
 
    for (int i = 1; i <= nonZero; i++) {
        printf("Enter row, column, value for element %d: ", i);
        scanf("%d%d%d", &mat[i].row, &mat[i].col, &mat[i].value);
    }
    return nonZero + 1; // total size including header
}
 
// Function to display sparse matrix
void displaySparse(sparse mat[]) {
    int total = mat[0].value + 1;
    printf("\nRow\tCol\tValue\n");
    for (int i = 0; i < total; i++) {
        printf("%d\t%d\t%d\n", mat[i].row, mat[i].col, mat[i].value);
    }
}
 
// Sparse matrix addition
int addSparse(sparse a[], sparse b[], sparse c[]) {
    if (a[0].row != b[0].row || a[0].col != b[0].col) {
        printf("Matrix dimensions do not match!\n");
        return 0;
    }
 
    c[0].row = a[0].row;
    c[0].col = a[0].col;
 
    int i = 1, j = 1, k = 1;
    while (i <= a[0].value && j <= b[0].value) {
        if (a[i].row < b[j].row ||
           (a[i].row == b[j].row && a[i].col < b[j].col)) {
            c[k++] = a[i++];
        } else if (b[j].row < a[i].row ||
                  (b[j].row == a[i].row && b[j].col < a[i].col)) {
            c[k++] = b[j++];
        } else {
            c[k] = a[i];
            c[k].value = a[i].value + b[j].value;
            i++; j++; k++;
        }
    }
    while (i <= a[0].value) c[k++] = a[i++];
    while (j <= b[0].value) c[k++] = b[j++];
 
    c[0].value = k - 1;
    return k;
}
 
// ----------- MAIN FUNCTION -----------
int main() {
    int choice;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Polynomial Addition\n");
        printf("2. Polynomial Subtraction\n");
        printf("3. Sparse Matrix Addition\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
 
        if (choice == 1) {
            term p1[MAX], p2[MAX], res[MAX];
            int n1 = readPolynomial(p1);
            int n2 = readPolynomial(p2);
            printf("First polynomial: ");
            displayPolynomial(p1, n1);
            printf("Second polynomial: ");
            displayPolynomial(p2, n2);
            int n3 = addPolynomial(p1, n1, p2, n2, res);
            printf("Result (Addition): ");
            displayPolynomial(res, n3);
 
        } else if (choice == 2) {
            term p1[MAX], p2[MAX], res[MAX];
            int n1 = readPolynomial(p1);
            int n2 = readPolynomial(p2);
            printf("First polynomial: ");
            displayPolynomial(p1, n1);
            printf("Second polynomial: ");
            displayPolynomial(p2, n2);
            int n3 = subPolynomial(p1, n1, p2, n2, res);
            printf("Result (Subtraction): ");
            displayPolynomial(res, n3);
 
        } else if (choice == 3) {
            sparse a[MAX], b[MAX], c[MAX];
            printf("Enter first sparse matrix:\n");
            int sizeA = readSparse(a);
            printf("Enter second sparse matrix:\n");
            int sizeB = readSparse(b);
            printf("\nFirst Sparse Matrix:");
            displaySparse(a);
            printf("\nSecond Sparse Matrix:");
            displaySparse(b);
            int sizeC = addSparse(a, b, c);
            printf("\nResult (Sparse Addition):");
            displaySparse(c);
 
        } else if (choice != 4) {
            printf("Invalid choice!\n");
        }
 
    } while (choice != 4);
 
    return 0;
}
