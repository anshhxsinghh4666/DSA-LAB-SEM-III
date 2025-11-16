// Write a program to implement operations on Binary Search Tree.

#include <stdio.h>
#include <stdlib.h>

/* Node structure for the binary search tree */
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

/* Function prototypes */
struct Node* insert(struct Node* root, int data);
struct Node* search(struct Node* root, int key);
struct Node* deleteNode(struct Node* root, int key);
void inorder(struct Node* root);
void preorder(struct Node* root);
void postorder(struct Node* root);
struct Node* findMin(struct Node* node);

int main() {
    struct Node* root = NULL;
    int choice, data;

    do {
        printf("\n\nBinary Search Tree Operations:");
        printf("\n1. Insert");
        printf("\n2. Search");
        printf("\n3. Delete");
        printf("\n4. Inorder Traversal");
        printf("\n5. Preorder Traversal");
        printf("\n6. Postorder Traversal");
        printf("\n7. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Inserted %d in the BST.\n", data);
                break;
            case 2:
                printf("Enter value to search: ");
                scanf("%d", &data);
                if (search(root, data)) {
                    printf("Value %d found in the BST.\n", data);
                } else {
                    printf("Value %d not found in the BST.\n", data);
                }
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                printf("Deleted %d from the BST (if it existed).\n", data);
                break;
            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 6:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 7:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);

    return 0;
}

/* Function to create a new node */
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/* Function to insert a node in the BST */
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

/* Function to search for a node in the BST */
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

/* Function to find the node with the minimum value in a subtree */
struct Node* findMin(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

/* Function to delete a node from the BST */
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

/* Function for inorder traversal (Left, Root, Right) */
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

/* Function for preorder traversal (Root, Left, Right) */
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

/* Function for postorder traversal (Left, Right, Root) */
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}
