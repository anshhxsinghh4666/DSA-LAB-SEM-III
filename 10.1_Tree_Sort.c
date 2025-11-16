// Write a program to implement quick sort, heap sort, merge sort, and radix sort.

#include <stdio.h>
#include <stdlib.h>

// -------- UTILITY FUNCTION --------
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

// ================= QUICK SORT =================
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ================= HEAP SORT =================
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// ================= MERGE SORT =================
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ================= RADIX SORT =================
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++) count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10) countSort(arr, n, exp);
}

// ================= MAIN MENU =================
int main() {
    int choice, n, arr[100], i;

    do {
        printf("\n--- Sorting Menu ---\n");
        printf("1. Quick Sort\n");
        printf("2. Heap Sort\n");
        printf("3. Merge Sort\n");
        printf("4. Radix Sort\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4) {
            printf("Enter number of elements: ");
            scanf("%d", &n);
            printf("Enter elements: ");
            for (i = 0; i < n; i++) scanf("%d", &arr[i]);

            printf("Original array: ");
            printArray(arr, n);

            switch (choice) {
                case 1:
                    quickSort(arr, 0, n - 1);
                    printf("Sorted array (Quick Sort): ");
                    break;
                case 2:
                    heapSort(arr, n);
                    printf("Sorted array (Heap Sort): ");
                    break;
                case 3:
                    mergeSort(arr, 0, n - 1);
                    printf("Sorted array (Merge Sort): ");
                    break;
                case 4:
                    radixSort(arr, n);
                    printf("Sorted array (Radix Sort): ");
                    break;
            }
            printArray(arr, n);
        } else if (choice != 5) {
            printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
