/*
DSA Mini Project - Final
Features:
  - Binary Search Tree (BST) (linked-node)
  - AVL Tree (linked-node)
  - Max Heap (array, 1-based)
  - Min Heap (array, 1-based)
Menu-driven CLI to choose DS and perform operations:
  Insert, Delete (where applicable), Search, Display traversals,
  Height & Balance (where applicable), Find min/max, Heap peek/extract.
Compile:
  gcc DSA_Mini_Project_Final.c -o dsa_final
Run:
  ./dsa_final
Author: (Your Name)
Date: (Date)
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* ---------------------- Node (BST & AVL) ---------------------- */
typedef struct Node {
    int key;
    struct Node *left, *right;
    int height;  // used for AVL balancing
} Node;

Node* newNode(int key) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

/* convenience */
int max_int(int a, int b) { return (a > b) ? a : b; }
int height_node(Node* n) { return (n == NULL) ? 0 : n->height; }

/* --------------- BST basic operations --------------- */
Node* bst_insert(Node* root, int key) {
    if (root == NULL)
        return newNode(key);
    if (key < root->key)
        root->left = bst_insert(root->left, key);
    else if (key > root->key)
        root->right = bst_insert(root->right, key);
    // duplicates ignored
    return root;
}

Node* bst_minValueNode(Node* node) {
    Node* cur = node;
    while (cur && cur->left) cur = cur->left;
    return cur;
}

Node* bst_delete(Node* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = bst_delete(root->left, key);
    else if (key > root->key)
        root->right = bst_delete(root->right, key);
    else {
        if (root->left == NULL) {
            Node* tmp = root->right;
            free(root);
            return tmp;
        } else if (root->right == NULL) {
            Node* tmp = root->left;
            free(root);
            return tmp;
        } else {
            Node* tmp = bst_minValueNode(root->right);
            root->key = tmp->key;
            root->right = bst_delete(root->right, tmp->key);
        }
    }
    return root;
}

Node* bst_search(Node* root, int key) {
    if (!root || root->key == key)
        return root;
    if (key < root->key)
        return bst_search(root->left, key);
    else
        return bst_search(root->right, key);
}

/* traversals */
void preorder(Node* root) {
    if (root) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

int tree_height(Node* root) {
    if (!root)
        return 0;
    return 1 + max_int(tree_height(root->left), tree_height(root->right));
}

/* --------------------- AVL operations --------------------- */
int getBalance(Node* n) {
    if (!n)
        return 0;
    return height_node(n->left) - height_node(n->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + max_int(height_node(y->left), height_node(y->right));
    x->height = 1 + max_int(height_node(x->left), height_node(x->right));
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max_int(height_node(x->left), height_node(x->right));
    y->height = 1 + max_int(height_node(y->left), height_node(y->right));
    return y;
}

Node* avl_insert(Node* node, int key) {
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = avl_insert(node->left, key);
    else if (key > node->key)
        node->right = avl_insert(node->right, key);
    else
        return node;  // duplicates ignored

    node->height = 1 + max_int(height_node(node->left), height_node(node->right));
    int balance = getBalance(node);

    // LL
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    // RR
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* avl_delete(Node* root, int key) {
    if (!root)
        return root;
    if (key < root->key)
        root->left = avl_delete(root->left, key);
    else if (key > root->key)
        root->right = avl_delete(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;  // copy contents
            }
            free(temp);
        } else {
            Node* temp = bst_minValueNode(root->right);
            root->key = temp->key;
            root->right = avl_delete(root->right, temp->key);
        }
    }
    if (!root)
        return root;
    root->height = 1 + max_int(height_node(root->left), height_node(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

/* ---------------------- Heaps (array-based 1-indexed) ---------------------- */
#define HEAP_CAP 1000
typedef struct {
    int arr[HEAP_CAP + 1];  // 1-based index: root at 1
    int size;
} Heap;

/* Max heap helpers */
void maxheap_init(Heap* h) { h->size = 0; }
void minheap_init(Heap* h) { h->size = 0; }

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/* heapify up for max heap (1-indexed) */
void maxheapify_up(Heap* h, int idx) {
    while (idx > 1) {
        int parent = idx / 2;
        if (h->arr[parent] < h->arr[idx]) {
            swap(&h->arr[parent], &h->arr[idx]);
            idx = parent;
        } else
            break;
    }
}

/* heapify down for max heap */
void maxheapify_down(Heap* h, int idx) {
    while (1) {
        int left = 2 * idx, right = left + 1, largest = idx;
        if (left <= h->size && h->arr[left] > h->arr[largest])
            largest = left;
        if (right <= h->size && h->arr[right] > h->arr[largest])
            largest = right;
        if (largest != idx) {
            swap(&h->arr[idx], &h->arr[largest]);
            idx = largest;
        } else
            break;
    }
}

void maxheap_insert(Heap* h, int val) {
    if (h->size >= HEAP_CAP) {
        printf("MaxHeap full\n");
        return;
    }
    h->size++;
    h->arr[h->size] = val;
    maxheapify_up(h, h->size);
}

int maxheap_extract(Heap* h) {
    if (h->size == 0) {
        printf("MaxHeap empty\n");
        return INT_MIN;
    }
    int root = h->arr[1];
    h->arr[1] = h->arr[h->size--];
    maxheapify_down(h, 1);
    return root;
}

int maxheap_peek(Heap* h) {
    if (h->size == 0) {
        printf("MaxHeap empty\n");
        return INT_MIN;
    }
    return h->arr[1];
}

void maxheap_display(Heap* h) {
    if (h->size == 0) {
        printf("MaxHeap empty\n");
        return;
    }
    printf("MaxHeap (level order): ");
    for (int i = 1; i <= h->size; ++i) printf("%d ", h->arr[i]);
    printf("\n");
}

/* --- Min Heap helpers (mirror of max heap) --- */
void minheapify_up(Heap* h, int idx) {
    while (idx > 1) {
        int parent = idx / 2;
        if (h->arr[parent] > h->arr[idx]) {
            swap(&h->arr[parent], &h->arr[idx]);
            idx = parent;
        } else
            break;
    }
}

void minheapify_down(Heap* h, int idx) {
    while (1) {
        int left = 2 * idx, right = left + 1, smallest = idx;
        if (left <= h->size && h->arr[left] < h->arr[smallest])
            smallest = left;
        if (right <= h->size && h->arr[right] < h->arr[smallest])
            smallest = right;
        if (smallest != idx) {
            swap(&h->arr[idx], &h->arr[smallest]);
            idx = smallest;
        } else
            break;
    }
}

void minheap_insert(Heap* h, int val) {
    if (h->size >= HEAP_CAP) {
        printf("MinHeap full\n");
        return;
    }
    h->size++;
    h->arr[h->size] = val;
    minheapify_up(h, h->size);
}

int minheap_extract(Heap* h) {
    if (h->size == 0) {
        printf("MinHeap empty\n");
        return INT_MIN;
    }
    int root = h->arr[1];
    h->arr[1] = h->arr[h->size--];
    minheapify_down(h, 1);
    return root;
}

int minheap_peek(Heap* h) {
    if (h->size == 0) {
        printf("MinHeap empty\n");
        return INT_MIN;
    }
    return h->arr[1];
}

void minheap_display(Heap* h) {
    if (h->size == 0) {
        printf("MinHeap empty\n");
        return;
    }
    printf("MinHeap (level order): ");
    for (int i = 1; i <= h->size; ++i) printf("%d ", h->arr[i]);
    printf("\n");
}

/* ---------------------- Menus ---------------------- */

void bst_menu(Node** root) {
    int choice = -1, x;
    while (choice != 0) {
        printf(
            "\n-- BST Menu --\n1. Insert\n2. Delete\n3. Search\n4. Display (Pre/In/Post)\n5. Height\n6. Find "
            "Min/Max\n0. Back\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input\n");
            choice = -1;
            continue;
        }
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &x);
                *root = bst_insert(*root, x);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &x);
                *root = bst_delete(*root, x);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &x);
                {
                    Node* res = bst_search(*root, x);
                    if (res)
                        printf("Found %d\n", res->key);
                    else
                        printf("Not found\n");
                }
                break;
            case 4:
                printf("Preorder: ");
                preorder(*root);
                printf("\nInorder: ");
                inorder(*root);
                printf("\nPostorder: ");
                postorder(*root);
                printf("\n");
                break;
            case 5:
                printf("Height: %d\n", tree_height(*root));
                break;
            case 6:
                if (*root) {
                    Node* mn = bst_minValueNode(*root);
                    Node* cur = *root;
                    while (cur->right) cur = cur->right;
                    printf("Min: %d, Max: %d\n", mn->key, cur->key);
                } else
                    printf("Tree empty\n");
                break;
            case 0:
                printf("Back to main menu\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}

void avl_menu(Node** root) {
    int choice = -1, x;
    while (choice != 0) {
        printf(
            "\n-- AVL Menu --\n1. Insert\n2. Delete\n3. Search\n4. Display (Pre/In/Post)\n5. Height & Balance "
            "(root)\n6. Find Min/Max\n0. Back\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input\n");
            choice = -1;
            continue;
        }
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &x);
                *root = avl_insert(*root, x);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &x);
                *root = avl_delete(*root, x);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &x);
                {
                    Node* res = bst_search(*root, x);
                    if (res)
                        printf("Found %d\n", res->key);
                    else
                        printf("Not found\n");
                }
                break;
            case 4:
                printf("Preorder: ");
                preorder(*root);
                printf("\nInorder: ");
                inorder(*root);
                printf("\nPostorder: ");
                postorder(*root);
                printf("\n");
                break;
            case 5:
                printf("Height (root): %d, Balance factor (root): %d\n", height_node(*root), getBalance(*root));
                break;
            case 6:
                if (*root) {
                    Node* mn = bst_minValueNode(*root);
                    Node* cur = *root;
                    while (cur->right) cur = cur->right;
                    printf("Min: %d, Max: %d\n", mn->key, cur->key);
                } else
                    printf("Tree empty\n");
                break;
            case 0:
                printf("Back to main menu\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}

void maxheap_menu(Heap* h) {
    int choice = -1, x;
    while (choice != 0) {
        printf("\n-- Max Heap Menu --\n1. Insert\n2. Extract Max\n3. Peek Max\n4. Display\n0. Back\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input\n");
            choice = -1;
            continue;
        }
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &x);
                maxheap_insert(h, x);
                break;
            case 2: {
                int v = maxheap_extract(h);
                if (v != INT_MIN)
                    printf("Extracted: %d\n", v);
            } break;
            case 3: {
                int v = maxheap_peek(h);
                if (v != INT_MIN)
                    printf("Max: %d\n", v);
            } break;
            case 4:
                maxheap_display(h);
                break;
            case 0:
                printf("Back to main menu\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}

void minheap_menu(Heap* h) {
    int choice = -1, x;
    while (choice != 0) {
        printf("\n-- Min Heap Menu --\n1. Insert\n2. Extract Min\n3. Peek Min\n4. Display\n0. Back\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input\n");
            choice = -1;
            continue;
        }
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &x);
                minheap_insert(h, x);
                break;
            case 2: {
                int v = minheap_extract(h);
                if (v != INT_MIN)
                    printf("Extracted: %d\n", v);
            } break;
            case 3: {
                int v = minheap_peek(h);
                if (v != INT_MIN)
                    printf("Min: %d\n", v);
            } break;
            case 4:
                minheap_display(h);
                break;
            case 0:
                printf("Back to main menu\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}

int main() {
    Node *bst_root = NULL, *avl_root = NULL;
    Heap maxh, minh;
    maxheap_init(&maxh);
    minheap_init(&minh);

    int choice = -1;
    while (choice != 0) {
        printf(
            "\n=== DSA Mini Project ===\n1. Binary Search Tree (BST)\n2. AVL Tree\n3. Max Heap (array, 1-based)\n4. "
            "Min Heap (array, 1-based)\n0. Exit\nChoose data structure: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input\n");
            continue;
        }
        switch (choice) {
            case 1:
                bst_menu(&bst_root);
                break;
            case 2:
                avl_menu(&avl_root);
                break;
            case 3:
                maxheap_menu(&maxh);
                break;
            case 4:
                minheap_menu(&minh);
                break;
            case 0:
                printf("Exiting. Goodbye!\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
