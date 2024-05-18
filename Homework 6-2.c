#include <stdio.h>
#include <stdlib.h>


struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
};


struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


int sumTree(struct TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->value + sumTree(node->left) + sumTree(node->right);
}

int main() {
    
    struct TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(13);
    root->right->right = createNode(18);
    root->left->left->left = createNode(1);
    root->left->right->left = createNode(6);

    
    int total_sum = sumTree(root);
    printf("%d\n", total_sum);
    return 0;
    return 0;
}

