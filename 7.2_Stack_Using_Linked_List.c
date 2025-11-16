// : Write a program to implement stack and its operations using array and linked-list.

/*  IMPLEMENTATION OF STACK USING LINKED LIST : 

Time Complexity : O(1)

Linked List : 
Head
 |
 v
+----+----+     +----+----+     +----+----+     +----+----+     +----+----+
| 10 | -> |     | 20 | -> |     | 30 | -> |     | 40 | -> |     | 50 |NULL|
+----+----+     +----+----+     +----+----+     +----+----+     +----+----+

Stack Linked List : 
Top ->
+---------+------------------+
| Data    | Next Address     |
+---------+------------------+
| 50      | 0x1008           |
+---------+------------------+
| 40      | 0x100C           |
+---------+------------------+
| 30      | 0x1010           |
+---------+------------------+
| 20      | 0x1014           |
+---------+------------------+
| 10      | NULL             |
+---------+------------------+
Bottom


NOTE : No need to mention the stack size as we did in Array.
    No specified size of stack here.
*/

/*
ALGORITHM : 

1. Start
2. Declare structure Node with fields : 
    ~ data (int)
    ~ next (pointer to next node)
3. Initialize Pointer top = NULL -> Points to top of the stack
4. Function Calls 

Function push(int x)
1. Allocate memory to newNode 
2. Input x in newNode->data
3. Set newNode->next = top
4. Update top = newNode

Function pop()
1. Allocate memory to temp
2. set temp = top
3. if top == NULL -> print "UnderFlow Condition"
4. else : 
    ~ Print deleted element : top->data
    ~ update top = top->next
    ~ free memory -> free(temp)

Function peek()
1. if top == NULL -> Print "Empty Stack"
2. else Print "Top element : top->data"

Function display()
1. Allocate memory to temp
2. temp = top
3. if top == NULL -> Print "Empty Stack"
4. else : 
    ~ while temp != NULL
        print temp->data
        update temp = temp->next

END
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL;

void push(int x) {
    struct Node *newNode;
    newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = top;
    top = newNode;
}

void display() {
    struct Node *temp;
    temp = top;
    if (top == NULL) {
        printf("Empty Stack");
    } else {
        while (temp != NULL) {
            printf(" %d ", temp->data);
            temp = temp->next;
        }
    }
    printf("\n");
}

void peek() {
    if (top == NULL) {
        printf("Empty Stack\n");
    } else {
        printf("Top Element : %d ", top->data);
    }
    printf("\n");
}

void pop() {
    struct Node *temp;
    temp = top;
    if (top == NULL) {
        printf("UnderFlow Condition \n");
    } else {
        printf("Deleted Element : %d\n", top->data);
        top = top->next;
        free(temp);
    }
    printf("\n");
}

int main() {
    push(10);
    push(11);
    push(12);
    push(13);
    push(14);
    push(15);

    display();

    pop();
    display();

    pop();
    display();

    peek();
    return 0;
}