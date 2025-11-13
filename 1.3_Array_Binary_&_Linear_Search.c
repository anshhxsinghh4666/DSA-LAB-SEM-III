// Write a program to implement Linear Search and Binary Search.

#include <stdio.h>

void linearSearch(int arr[], int n, int ele) {
    int f = 0;
    int pos = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == ele) {
            f = 1;
            pos = i;
            break;
        } else {
            pos++;
        }
    }
    if (f == 1) {
        printf("Element %d found at Index %d", ele, pos);
    } else {
        printf("Not found");
    }
}

void binarySearch(int arr[], int n, int ele) {
    int low = 0, high = n - 1, mid;
    int found = 0;

    // Bubble Sort :
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    while (low <= high) {
        mid = (low + high) / 2;

        if (arr[mid] == ele) {
            found = 1;
            printf("Found Element %d at Index %d", ele, mid);
            break;
        } else if (arr[mid] < ele) {
            low = mid + 1;
        } else if (arr[mid] > ele) {
            high = mid - 1;
        }
    }
    if (!found) {
        printf("Element %d not found", ele);
    }
}

int main() {
    int n, ele;
    printf("Enter Number of Elements : ");
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Element %d : ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("Enter Element to Search : ");
    scanf("%d", &ele);

    int choice;
    printf("\nChoose the search method:\n");
    printf("1. Linear Search\n");
    printf("2. Binary Search\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("Linear Search : ");
            linearSearch(arr, n, ele);
            break;
        case 2:
            printf("Binary Search : ");
            binarySearch(arr, n, ele);
            break;
        default:
            printf("Invalid Input\n");
            break;
    }

    return 0;
}