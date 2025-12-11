// Write a program to implement Breadth-First Search and Depth-First Search.


#include <stdio.h>
#include <stdlib.h>
 
#define MAX 20
 
int adj[MAX][MAX];   // Adjacency matrix
int visited[MAX];    // Visited array
int n;               // Number of vertices
 
// ===== Queue for BFS =====
int queue[MAX], front = -1, rear = -1;
 
void enqueue(int v) {
    if (rear == MAX - 1)
        printf("Queue overflow!\n");
    else {
        if (front == -1) front = 0;
        queue[++rear] = v;
    }
}
 
int dequeue() {
    if (front == -1 || front > rear)
        return -1;
    else
        return queue[front++];
}
 
// ===== BFS Traversal =====
void BFS(int start) {
    for (int i = 0; i < n; i++)
        visited[i] = 0;
 
    enqueue(start);
    visited[start] = 1;
 
    printf("BFS Traversal: ");
    while (front <= rear) {
        int v = dequeue();
        printf("%d ", v);
 
        for (int i = 0; i < n; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
 
    // Reset queue
    front = rear = -1;
}
 
// ===== DFS Traversal =====
void DFSUtil(int v) {
    visited[v] = 1;
    printf("%d ", v);
 
    for (int i = 0; i < n; i++) {
        if (adj[v][i] == 1 && !visited[i])
            DFSUtil(i);
    }
}
 
void DFS(int start) {
    for (int i = 0; i < n; i++)
        visited[i] = 0;
 
    printf("DFS Traversal: ");
    DFSUtil(start);
    printf("\n");
}
 
// ===== Main Function =====
int main() {
    int choice, start;
 
    printf("Enter number of vertices: ");
    scanf("%d", &n);
 
    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);
 
    do {
        printf("\n--- Graph Traversal Menu ---\n");
        printf("1. BFS\n");
        printf("2. DFS\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
 
        if (choice == 1 || choice == 2) {
            printf("Enter starting vertex (0 to %d): ", n - 1);
            scanf("%d", &start);
            if (choice == 1)
                BFS(start);
            else
                DFS(start);
        } else if (choice != 3) {
            printf("Invalid choice!\n");
        }
    } while (choice != 3);
 
    return 0;
}
