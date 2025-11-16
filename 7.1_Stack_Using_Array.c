// : Write a program to implement stack and its operations using array and linked-list.

/* IMPLEMENTATION OF STACK USING ARRAY : 

ARRAY : 

Index:  4     3     2     1     0
        +-----+-----+-----+-----+-----+
Stack:  | 50  | 40  | 30  | 20  | 10  |
        +-----+-----+-----+-----+-----+
Top -> Index 4
Bottom -> Index 0


ARRAY TO STACK : 

Top -> Index 4
        +-----+
        | 50  |
        +-----+
Index 3 | 40  |
        +-----+
Index 2 | 30  |
        +-----+
Index 1 | 20  |
        +-----+
Bottom->Index 0
        | 10  |
        +-----+

*/

/*
ALGORITHM : 

1. Start
2. Define N -> size of stack
3. Declare Global Variables : stack[N] , top = -1
4. Repeat until user chooses exit (ch != 0):
	•	Print menu options:
    1 → Push
    2 → Pop
    3 → Peek
    4 → Display
    0 → Exit
	•	Input user choice ch
	•	switch(ch) : 
	•	    Case 1 → call push()
	•	    Case 2 → call pop()
	•	    Case 3 → call peek()
	•	    Case 4 → call display()
	•	    Case 0 → Print exit message
	•	    Default → Print “Invalid Choice”

Function push()
1. Declare x
2. Input data in x
3. if top == n-1 -> Print "Overflow condition"
4. else 
    ~ Increment top++
    ~ Set stack[top] = x

Function pop()
1. Declare x
2. if top == -1 -> Print "Underflow Condition"
3. else 
    ~ x = stack[top]
    ~ top--
    ~ Print "Deleted Value : x"

Function peek()
1. if top == -1 -> Empty Stack
2. else -> Print top element : stack[top]

Function display()
1. if top == -1 -> Print "Empty Stack"
2. else 
    ~ Loop from i=top to i>=0
        print stack[i]

*/

#include <stdio.h>
#include <stdlib.h>

#define N 5  // Defines value of N (Macro)

// Global Variables :
int stack[N];  // As value of N is defined (Fixed) and size of stack is N so Size of stack is fixed
int top = -1;

void push() {  // Can also make it parametric
    int x;
    printf("Enter Data : ");
    scanf("%d", &x);

    if (top == N - 1) {
        printf("Overflow Condition : Cannot Insert\n");
    } else {
        top++;
        stack[top] = x;
    }
    printf("\n");
}

void pop() {
    int x;
    if (top == -1) {
        printf("UnderFlow\n");
    } else {
        x = stack[top];
        top--;
        printf("Deleted Value is : %d\n", x);
    }
    printf("\n");
}

void peek() {
    if (top == -1) {
        printf("Empty Stack \n");
    } else {
        printf("Top Element : %d", stack[top]);
    }
    printf("\n");
}

void display() {
    if (top == -1) {
        printf("Empty Stack \n");
    } else {
        printf("Stack Contents : \n");
        for (int i = top; i >= 0; i--) {
            printf(" %d ", stack[i]);
        }
    }
    printf("\n");
}

int main() {
    int ch;
    do {
        printf("Enter Choice :\n 1. Push\n 2. Pop\n 3. Peek\n 4. Display\n 0. Exit...\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                display();
                break;
            case 0:
                printf("Exiting...");
                break;
            default:
                printf("Invalid Choice \n");
                break;
        }
    } while (ch != 0);

    return 0;
}