// Write a C program to perform various operations on Doubly Linked List.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

int count , pos;
struct Node *head, *tail, *newNode, *temp;

void display() {
    tail = head;
    printf("Linked List : \n");
    if (tail == NULL) {
        printf("Linked List is Empty\n");
    }
    while (tail != NULL) {
        printf("%d <--> ", tail->data);
        tail = tail->next;
    }
    printf("NULL\n");
}

void length() {
    if (head == NULL) {
        printf("Empty List \n");
    }
    count = 0;
    temp = head;
    while (temp != 0) {
        count++;
        temp = temp->next;
    }
    printf("Lenght of Linked List : %d\n", count);
}

void insertBeg() {
    newNode = (struct Node *) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed\n");
        return;
    }
    printf("Enter Data : ");
    scanf("%d", &newNode->data);
    newNode->prev = NULL;
    newNode->next = NULL;

    if (head == NULL) {  // Empty list
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    printf("Linked List After Insertion at Beginning : ");
    display();
}

void insertEnd() {
    newNode = (struct Node *) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed \n");
        return;
    }
    printf("Enter Data : ");
    scanf("%d", &newNode->data);
    newNode->prev = NULL;
    newNode->next = NULL;

    if (head == NULL) {  // Empty list
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    printf("Linked List After Insertion at End : ");
    display();
}

void insertAtLoc() {
    length();
    printf("Enter Position : ");
    scanf("%d", &pos);

    if (pos < 1 || pos > count + 1) {
        printf("Invalid Position\n");
        return;
    }

    if (pos == 1) {  // First position
        insertBeg();
        return;
    }
    if (head == NULL) {  // List empty but pos != 1
        printf("Empty list. Cannot insert at position %d\n", pos);
        return;
    }

    newNode = (struct Node *) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed \n");
        return;
    }
    printf("Enter Data : ");
    scanf("%d", &newNode->data);

    temp = head;
    int i = 1;
    while (i < pos - 1 && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Invalid Position\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    } else {
        tail = newNode;
    }
    temp->next = newNode;

    display();
}

void deleteBeg() {
    if (head == NULL) {
        printf("Linked List is Empty\n");
        return;
    }
    temp = head;
    head = head->next;
    head->prev = NULL;
    free(temp);
}

void deleteEnd() {
    if (head == NULL) {
        printf("Linked List is Empty\n");
        return;
    } else {
        temp = tail;
        tail->prev->next = NULL;
        tail = tail->prev;
        free(temp);
    }
}

void deleteAtLoc() {
    if (head == NULL) {
        printf("List is empty, cannot delete.\n");
        return;
    }
    int pos, i = 1;
    printf("Enter Position : ");
    scanf("%d", &pos);

    length();  // Calculate current length
    if (pos < 1 || pos > count) {
        printf("Invalid Position\n");
        return;
    }

    if (pos == 1) {
        deleteBeg();
        return;
    }

    temp = head;
    // The logic here was incorrect. This correctly finds the node *before* the target.
    while (i < pos) {
        temp = temp->next;
        i++;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp);
}

void BubbleSort() {
    if (head == NULL)
        return;

    int swapped;
    struct Node *ptr;
    struct Node *last = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != last) {
            if (ptr->data > ptr->next->data) {
                // Swap the data
                int temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;  // Reduce the range for next pass
    } while (swapped);
}

int main() {
    int n;
    head = NULL;
    printf("Enter Number of Elements : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        newNode = (struct Node *) malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
        printf("Enter Data : ");
        scanf("%d", &newNode->data);
        newNode->next = NULL;
        newNode->prev = NULL;

        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    display();

    // --- MENU LOOP ---
    int ch;
    do {
        printf("\n1. Display list");
        printf("\n2. Display list in reverse order");
        printf("\n3. Insert a node at the beginning");
        printf("\n4. Insert a node at the end");
        printf("\n5. Insert a node at a specific position");
        printf("\n6. Delete a node from the beginning");
        printf("\n7. Delete a node from the end");
        printf("\n8. Delete a node from a specific position");
        printf("\n9. Count nodes");
        printf("\n10. Sort the list (Bubble Sort)");
        printf("\n11. Exit");
        printf("\n----------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                display();
                break;
            case 2:
                // displayReverse();  // uncomment if you have this function
                printf("Reverse display not implemented yet.\n");
                break;
            case 3:
                insertBeg();
                break;
            case 4:
                insertEnd();
                break;
            case 5:
                insertAtLoc();
                break;
            case 6:
                deleteBeg();
                display();
                break;
            case 7:
                deleteEnd();
                display();
                break;
            case 8:
                deleteAtLoc();
                display();
                break;
            case 9:
                length();
                break;
            case 10:
                BubbleSort();
                display();
                break;
            case 11:
                exit(0);
            default:
                printf("\nInvalid choice!\n");
        }
    } while (1);
    
    return 0;
}