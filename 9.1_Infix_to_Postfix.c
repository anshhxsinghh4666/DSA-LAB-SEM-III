// Write a C program to implement conversion from infix to postfix and evaluation of postfix expression.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
 
#define MAX 100   /* Maximum size for stack and expressions */
 
typedef struct {
    int top;
    int items[MAX];
} Stack;
 
void initStack(Stack* stack) {
    stack->top = -1;
}
 
int isEmpty(Stack* stack) {
    return stack->top == -1;
}
 
void push(Stack* stack, int value) {
    if (stack->top == MAX - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack->items[++stack->top] = value;
}
 
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->items[stack->top--];
}
 
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack->items[stack->top];
}
 
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
 
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
 
void infixToPostfix(char infix[], char postfix[]) {
    Stack stack;
    initStack(&stack);
    int i, j = 0;
 
    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];
 
        if (isdigit(ch)) {  // If operand, add to postfix
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            pop(&stack);  // Remove '(' from stack
        } else if (isOperator(ch)) {
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(ch)) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }
 
    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }
    postfix[j] = '\0';
}
 
int evaluatePostfix(char postfix[]) {
    Stack stack;
    initStack(&stack);
 
    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
 
        if (isdigit(ch)) {
            push(&stack, ch - '0');  // Convert char to int and push
        } else if (isOperator(ch)) {
            int val2 = pop(&stack);
            int val1 = pop(&stack);
 
            switch (ch) {
                case '+': push(&stack, val1 + val2); break;
                case '-': push(&stack, val1 - val2); break;
                case '*': push(&stack, val1 * val2); break;
                case '/': 
                    if (val2 == 0) {
                        printf("Error: Division by zero\n");
                        exit(1);
                    }
                    push(&stack, val1 / val2); 
                    break;
            }
        }
    }
 
    return pop(&stack);  // Final result in stack
}
 
int main() {
    char infix[MAX], postfix[MAX];
 
    printf("Enter an infix expression: ");
    scanf("%s", infix);
 
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
 
    int result = evaluatePostfix(postfix);
    printf("Result of postfix evaluation: %d\n", result);
    return 0;
}

