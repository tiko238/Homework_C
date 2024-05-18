#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


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


int findMin(struct TreeNode* node) {
    if (node == NULL) {
        return INT_MAX;
    }
    int leftMin = findMin(node->left);
    int rightMin = findMin(node->right);
    int minValue = node->value < leftMin ? node->value : leftMin;
    return minValue < rightMin ? minValue : rightMin;
}


int findMax(struct TreeNode* node) {
    if (node == NULL) {
        return INT_MIN;
    }
    int leftMax = findMax(node->left);
    int rightMax = findMax(node->right);
    int maxValue = node->value > leftMax ? node->value : leftMax;
    return maxValue > rightMax ? maxValue : rightMax;
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
    int minValue = findMin(root);
    int maxValue = findMax(root);
    int difference = maxValue - minValue;
    printf("%d\n", difference);
    return 0;
}

