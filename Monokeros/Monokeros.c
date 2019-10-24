#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _node {
    struct _node* left;
    struct _node* right;
    struct _node* parent;
    long value;
    uint16_t level;
}Node;

int insert (Node* root, long value) {
    if (value <= root->value) {
        if (root->left) {
            return insert(root->left, value);
        }
        else {
            // Create the Node
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->parent = root;
            new_node->value = value;
            new_node->level = root->level+1;
            
            root->left = new_node;
            return new_node->level;
        }
    }
    else {
        if (root->right) {
            return insert(root->right, value);
        }
        else {
            // Create the Node
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->parent = root;
            new_node->value = value;
            new_node->level = root->level+1;
            
            root->right = new_node;
            return new_node->level;
        }
    }
}

int main() {
    int n;
    long val;
    scanf("%d", &n);
    
    Node* root = (Node*)malloc(sizeof(Node));
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    scanf("%ld", &root->value);
    root->level = 1;
    printf("%d", root->level);
    for (int i = 1; i < n; i++) {
        scanf("%ld", &val);
        printf(" %d", insert(root, val));
    }
    printf("\n");

    return 0;
}
