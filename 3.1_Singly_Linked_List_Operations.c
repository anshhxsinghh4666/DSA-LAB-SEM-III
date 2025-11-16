// Write a C program to perform various operations on Singly Linked List.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int count = 0;
struct Node *head = NULL, *temp = NULL, *newNode = NULL;

void display() {
    temp = head;
    if (temp == NULL) {
        printf("List is Empty\n");
        return;
    }
    printf("Linked List : ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void length() {
    count = 0;
    temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Length of Linked List : %d\n", count);
}

void insertBeg() {
    newNode = (struct Node *) malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    printf("Enter Data : ");
    if (scanf("%d", &newNode->data) != 1)
        return;
    newNode->next = head;
    head = newNode;
    display();
}

void insertEnd() {
    newNode = (struct Node *) malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    printf("Enter Data : ");
    if (scanf("%d", &newNode->data) != 1)
        return;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
    display();
}

void insertAtLoc() {
    length();
    int pos, j = 1;
    printf("Insert Position : ");
    if (scanf("%d", &pos) != 1)
        return;
    if (pos < 1 || pos > count + 1) {
        printf("Invalid Position\n");
        return;
    }
    if (pos == 1) {
        insertBeg();
        return;
    }
    newNode = (struct Node *) malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    temp = head;
    while (j < pos - 1 && temp != NULL) {
        temp = temp->next;
        j++;
    }
    printf("Enter Data : ");
    if (scanf("%d", &newNode->data) != 1)
        return;
    newNode->next = (temp ? temp->next : NULL);
    if (temp)
        temp->next = newNode;
    display();
}

void insertMiddle() {
    length();
    if (head == NULL) {
        insertBeg();
        return;
    }
    int mid = (count % 2 == 0) ? (count / 2) : ((count / 2) + 1);
    newNode = (struct Node *) malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    printf("Enter Data : ");
    if (scanf("%d", &newNode->data) != 1)
        return;
    temp = head;
    int j = 1;
    while (j < mid && temp != NULL) {
        temp = temp->next;
        j++;
    }
    newNode->next = (temp ? temp->next : NULL);
    if (temp)
        temp->next = newNode;
    display();
}

void deleteBeg() {
    if (head == NULL) {
        printf("Empty List\n");
        return;
    }
    temp = head;
    head = head->next;
    free(temp);
    display();
}

void deleteEnd() {
    if (head == NULL) {
        printf("Empty List\n");
        return;
    }
    if (head->next == NULL) {
        free(head);
        head = NULL;
        display();
        return;
    }
    temp = head;
    struct Node *preNode = NULL;
    while (temp->next != NULL) {
        preNode = temp;
        temp = temp->next;
    }
    if (preNode)
        preNode->next = NULL;
    free(temp);
    display();
}

void deleteAtLoc() {
    if (head == NULL) {
        printf("List is empty, cannot delete.\n");
        return;
    }
    int pos, j = 1;
    printf("Enter Location: ");
    if (scanf("%d", &pos) != 1)
        return;
    length();
    if (pos < 1 || pos > count) {
        printf("Invalid Position\n");
        return;
    }
    if (pos == 1) {
        deleteBeg();
        return;
    }
    temp = head;
    while (j < pos - 1 && temp != NULL) {
        temp = temp->next;
        j++;
    }
    if (temp && temp->next) {
        struct Node *nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        free(nodeToDelete);
    }
    display();
}

void search() {
    int target;
    printf("Enter Target : ");
    if (scanf("%d", &target) != 1)
        return;
    struct Node *t = head;
    int index = 0;
    bool found = false;
    while (t != NULL) {
        if (t->data == target) {
            printf("Element Found At Index %d\n", index);
            found = true;
            break;
        }
        t = t->next;
        index++;
    }
    if (!found)
        printf("Element Not Found\n");
}

void BubbleSort() {
    if (head == NULL)
        return;
    int swapped;
    do {
        swapped = 0;
        struct Node *p = head;
        while (p->next != NULL) {
            if (p->data > p->next->data) {
                int tmp = p->data;
                p->data = p->next->data;
                p->next->data = tmp;
                swapped = 1;
            }
            p = p->next;
        }
    } while (swapped);
    display();
}

int main() {
    int n;
    printf("Enter Number of Elements : ");
    if (scanf("%d", &n) != 1)
        return 0;
    head = NULL;

    for (int i = 0; i < n; i++) {
        newNode = (struct Node *) malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory Allocation Failed \n");
            return 1;
        }
        printf("Enter Data : ");
        if (scanf("%d", &newNode->data) != 1)
            return 0;
        newNode->next = NULL;
        if (head == NULL) {
            head = temp = newNode;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }

    int ch;
    do {
        printf("\n1. Display list");
        printf("\n2. Insert at beginning");
        printf("\n3. Insert at end");
        printf("\n4. Insert at position");
        printf("\n5. Insert in middle");
        printf("\n6. Delete from beginning");
        printf("\n7. Delete from end");
        printf("\n8. Delete from position");
        printf("\n9. Count nodes");
        printf("\n10. Search element");
        printf("\n11. Sort list");
        printf("\n12. Exit");
        printf("\n----------------------------");
        printf("\nEnter your choice: ");
        if (scanf("%d", &ch) != 1)
            break;
        switch (ch) {
            case 1:
                display();
                break;
            case 2:
                insertBeg();
                break;
            case 3:
                insertEnd();
                break;
            case 4:
                insertAtLoc();
                break;
            case 5:
                insertMiddle();
                break;
            case 6:
                deleteBeg();
                break;
            case 7:
                deleteEnd();
                break;
            case 8:
                deleteAtLoc();
                break;
            case 9:
                length();
                break;
            case 10:
                search();
                break;
            case 11:
                BubbleSort();
                break;
            case 12:
                exit(0);
            default:
                printf("\nInvalid choice!\n");
        }
    } while (1);
    return 0;
}
