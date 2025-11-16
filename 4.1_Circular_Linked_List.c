// Write a C program to perform various operations on Circular (Single) Linked list.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int pos, count = 0, i = 1;
struct Node *head, *newNode, *temp;

void length() {
    count = 0;
    if (head == NULL) {  // ✅ FIXED: handle empty list safely
        printf("List is Empty \n");
        return;
    }

    temp = head;
    do {  // ✅ FIXED: correct traversal in circular list
        count++;
        temp = temp->next;
    } while (temp != head);

    printf("Length of Linked List : %d\n", count);
}

void display() {
    printf("Circular Linked List : \n");
    if (head == NULL) {  // ✅ FIXED: handle empty list safely
        printf("Empty List \n");
        return;
    }
    temp = head;
    do {  // ✅ FIXED: do-while loop for circular traversal
        printf("%d <-> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("HEAD\n");
}

void insertBeg() {
    newNode = (struct Node *) malloc(sizeof(struct Node));
    printf("Enter Data : ");
    scanf("%d", &newNode->data);

    if (head == NULL) {  // ✅ FIXED: handle empty list
        head = newNode;
        newNode->next = head;
    } else {
        temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        newNode->next = head;
        temp->next = newNode;
        head = newNode;
    }
    display();
}

void insertEnd() {
    newNode = (struct Node *) malloc(sizeof(struct Node));
    printf("Enter Data : ");
    scanf("%d", &newNode->data);

    if (head == NULL) {  // ✅ FIXED: handle empty list
        head = newNode;
        newNode->next = head;
    } else {
        temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }
    display();
}

void insertAtLoc() {
    length();
    if (head == NULL) {
        return;
    }
    printf("Enter Position : ");
    scanf("%d", &pos);

    if (pos < 1 || pos > count + 1) {
        printf("Invalid Position");
        return;
    } else if (pos == 1) {
        insertBeg();
    } else {
        newNode = (struct Node *) malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory Allocation Failed\n");
            return;
        }
        printf("Enter Data : ");
        scanf("%d", &newNode->data);
        temp = head;
        while (i < pos - 1) {
            temp = temp->next;
            i++;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    display();
}

void deleteBeg() {
    if (head == NULL) {
        printf("Empty List\n");
        return;
    }
    if (head->next == head) {
        free(head);
        head = NULL;
        return;
    }
    struct Node *last = head;
    while (last->next != head) {
        last = last->next;
    }
    struct Node *del = head;
    head = head->next;
    last->next = head;
    free(del);
}

void deleteEnd() {
    if (head == NULL) {
        printf("Empty List \n");
        return;
    }
    // If there is only one Node
    if (head->next == head) {
        free(head);
        head = NULL;
        return;
    }

    temp = head;
    struct Node *preNode;
    do {
        preNode = temp;
        temp = temp->next;
    } while (temp->next != head);
    preNode->next = head;
    free(temp);
}

void deleteLoc() {
    if (head == NULL) {
        printf("Empty List\n");
        return;
    }

    int pos, i = 1;
    printf("Enter Location : ");
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
    while (i < pos - 1) {
        temp = temp->next;
        i++;
    }
    struct Node *nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    free(nodeToDelete);
}

void BubbleSort() {
    if (head == NULL || head->next == head)
        return;  // Empty or single node

    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr && ptr1->next != head) {
            if (ptr1->data > ptr1->next->data) {
                // Swap data
                int tempData = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = tempData;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;  // Last sorted node
    } while (swapped);
}

void search() {
    temp = head;
    if (head == NULL) {
        printf("Empty List\n");
        return;
    }
    int target, count = 0;
    bool found = false;
    printf("Enter Target : ");
    scanf("%d", &target);
    while (temp->next != head) {
        if (target == temp->data) {
            printf("Element Found At Index %d", count);
            found = true;
        }
        temp = temp->next;
        count++;
    }
    if (found == false) {
        printf("Element Not Found\n");
    }
}

int main() {
    head = NULL;
    int n;
    printf("Enter Number of Elements : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        newNode = (struct Node *) malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory Allocation Failed\n");
            return 1;
        }
        printf("Enter Data : ");
        scanf("%d", &newNode->data);
        newNode->next = NULL;
        if (head == NULL) {
            head = temp = newNode;
        } else {
            temp->next = newNode;
            temp = newNode;
            temp->next = head;
        }
    }
    display();

    int ch;
    do {
        printf("\n1. Display list");
        printf("\n2. Insert an item at the first node");
        printf("\n3. Insert an item at the last node");
        printf("\n4. Insert an item in the middle of the list");
        printf("\n5. Delete an item at the first node");
        printf("\n6. Delete an item at the last node");
        printf("\n7. Delete an item in the middle of the list");
        printf("\n8. Count nodes");
        printf("\n9. Search an element");
        printf("\n10. Sort the list using Bubble Sort");
        printf("\n11. Exit");
        printf("\n----------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                display();
                break;
            case 2:
                display();
                break;
            case 3:
                insertBeg();
                display();
                break;
            case 4:
                insertEnd();
                display();
                break;
            case 5:
                insertAtLoc();
                display();
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
                deleteLoc();
                display();
                break;
            case 9:
                length();
                break;
            case 10:
                search();
                break;
            case 11:
                BubbleSort();
                display();
                break;
            case 12:
                exit(0);
            default:
                printf("\nInvalid choice!\n");
        }
    } while (1);
    return 0;
}
