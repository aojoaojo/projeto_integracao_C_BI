#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_CHILDREN 15
extern int cont;

typedef struct TreeNode
{
    char data[50];
    struct TreeNode *parent; // Novo campo para apontar para o nó pai
    struct TreeNode *children[MAX_CHILDREN];
} TreeNode;

TreeNode *createNode(const char *data, TreeNode *parent);
void addChild(TreeNode *parent, TreeNode *child);
void printPreOrder(TreeNode *node);
void freeTree(TreeNode *node);
TreeNode *searchTreeNode(TreeNode *node, const char *data);
TreeNode *searchByParent(TreeNode *node, const char *parentValue);
void searchAndPrintNodesWithParent(TreeNode *node, const char *parentString);
TreeNode *returnNodeByIndex(TreeNode *node, const char *parentString, int escolha);
FILE *openFile(const char *filename);
TreeNode *readFileAndCreateTree(FILE *file, TreeNode *root);

#endif
