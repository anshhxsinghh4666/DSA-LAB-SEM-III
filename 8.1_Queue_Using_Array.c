// IMPLEMENTATIONS OF QUEUE USING ARRAYS : Using static memory allocation

#include <stdio.h>

#define N 5
int queue[N];
int front = -1;
int rear = -1;

void enqueue(int x) {
    if (rear == N - 1) {
        printf("OverFlow\n");
    } else if (front == -1 && rear == -1) {
        front = rear = 0;
        queue[rear] = x;
    } else {
        rear++;
        queue[rear] = x;
    }
}

void dequeue() {
    if (front == -1 && rear == -1) {
        printf("UnderFlow\n");
    } else if (front == rear) {
        front = rear = -1;
    } else {
        printf("Dequeue : %d\n", queue[front]);
        front++;
    }
}

void display() {
    int i;
    printf("Display : ");
    if (front == -1 && rear == -1) {
        printf("Empty List\n");
    } else {
        for (i = front; i < rear + 1; i++) {
            printf("%d \t ", queue[i]);
        }
    }
    printf("\n");
}

void peek() {
    if (front == 1 && rear == -1) {
        printf("Empty Queue\n");
    } else {
        printf("Peek : %d\n", queue[front]);
    }
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    peek();
    display();
    dequeue();
    peek();
    dequeue();
    peek();
    dequeue();
    display();

    return 0;
}
