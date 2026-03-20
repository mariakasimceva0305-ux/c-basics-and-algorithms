#ifndef TREE_H
#define TREE_H

typedef struct TreeNode {
    int vertex;
    struct TreeNode* next;
} TreeNode;

typedef struct Tree {
    int n;
    TreeNode** adjacency_list;
} Tree;

Tree* prufer_to_tree(const int* prufer, int n);
Tree* generate_random_tree(int n);
void free_tree(Tree* tree);

#endif