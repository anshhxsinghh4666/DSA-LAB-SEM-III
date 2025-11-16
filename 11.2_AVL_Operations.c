// Write a program to implement operations on AVL Tree.

#include <stdio.h>
#include <stdlib.h>
// -------- AVL Tree Node --------
typedef struct Node {
    int key;
    struct Node *left, *right;
    int height;
} Node;
// Function to get height of node
int height(Node* n) {
    if (n == NULL)
        return 0;
    return n->height;
}
// Utility function to get maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }
// Create new node
Node* newNode(int key) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    // new node is initially at height 1
    return node;
}
// -------- ROTATIONS --------
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;  // new root
}
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;  // new root
}
// Get balance factor
int getBalance(Node* n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}
// -------- INSERTION --------
Node* insert(Node* node, int key) {
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else  // duplicate keys not allowed
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get balance factor
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;  // unchanged
}
// -------- MINIMUM VALUE NODE --------
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL) current = current->left;
    return current;
}
// -------- DELETION --------
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;
    // Standard BST delete
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with one or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {  // no child
                temp = root;
                root = NULL;
            } else  // one child
                *root = *temp;
            free(temp);
        } else {
            // Node with two children
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // Balance factor
    int balance = getBalance(root);

    // Balancing
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
// -------- SEARCH --------
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return search(root->left, key);
    return search(root->right, key);
}
// -------- TRAVERSALS --------
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}
void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}
// -------- MAIN --------
int main() {
    Node* root = NULL;
    int choice, key;
    do {
        printf("\n--- AVL Tree Menu ---\n");
        printf(
            "1. Insert\n2. Delete\n3. Search\n4. In-order Traversal\n5. Pre-order Traversal\n6. Post-order "
            "Traversal\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(root, key))
                    printf("Key %d found in tree.\n", key);
                else
                    printf("Key %d not found.\n", key);
                break;
            case 4:
                printf("In-order: ");
                inOrder(root);
                printf("\n");
                break;
            case 5:
                printf("Pre-order: ");
                preOrder(root);
                printf("\n");
                break;
            case 6:
                printf("Post-order: ");
                postOrder(root);
                printf("\n");
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 7);

    return 0;
}
