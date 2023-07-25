#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_CHILDREN 15
int cont = 1;

// Definição da estrutura do nó da árvore
typedef struct TreeNode
{
    char data[50];
    struct TreeNode *parent; // Novo campo para apontar para o nó pai
    struct TreeNode *children[MAX_CHILDREN];
} TreeNode;

// Função para criar um novo nó da árvore
TreeNode *createNode(const char *data, TreeNode *parent)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    strcpy(newNode->data, data);
    newNode->parent = parent; // Configurar o nó pai
    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Função para inserir um novo nó filho em um nó pai
void addChild(TreeNode *parent, TreeNode *child)
{
    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        if (parent->children[i] == NULL)
        {
            parent->children[i] = child;
            child->parent = parent; // Configurar o nó pai do filho
            return;
        }
    }
    printf("O nó não pode ter mais filhos.\n");
}

// Função para imprimir a árvore em pré-ordem (raiz-esquerda-direita)
void printPreOrder(TreeNode *node)
{
    if (node == NULL)
    {
        return;
    }

    printf("%s", node->data);

    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        printPreOrder(node->children[i]);
    }
}

// Função para liberar a memória da árvore recursivamente
void freeTree(TreeNode *node)
{
    if (node == NULL)
    {
        return;
    }

    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        freeTree(node->children[i]);
    }

    free(node);
}

// Função para pesquisar um nó na árvore
TreeNode *searchTreeNode(TreeNode *node, const char *data)
{
    if (node == NULL)
    {
        return NULL;
    }

    // Verificar se o dado do nó atual é igual ao dado procurado
    if (strcmp(node->data, data) == 0)
    {
        return node;
    }

    // Pesquisar nos filhos do nó atual
    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        TreeNode *result = searchTreeNode(node->children[i], data);
        if (result != NULL)
        {
            return result;
        }
    }

    // Se o dado não for encontrado em nenhum dos nós da subárvore, retornar NULL
    return NULL;
}

// Função para pesquisar um nó pelo valor do pai
TreeNode *searchByParent(TreeNode *node, const char *parentValue)
{
    if (node == NULL)
    {
        return NULL;
    }

    // Verificar se o pai do nó atual possui o valor desejado
    if (node->parent != NULL && strcmp(node->parent->data, parentValue) == 0)
    {
        return node;
    }

    // Pesquisar nos filhos do nó atual
    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        TreeNode *result = searchByParent(node->children[i], parentValue);
        if (result != NULL)
        {
            return result;
        }
    }

    // Se o nó com o pai desejado não for encontrado em nenhum dos nós da subárvore, retornar NULL
    return NULL;
}

// Função para pesquisar e imprimir todos os nós em que o pai é igual a uma variável string
void searchAndPrintNodesWithParent(TreeNode *node, const char *parentString)
{
    if (node == NULL)
    {
        return;
    }

    // Verificar se o nó tem um pai e se o valor do pai é igual à variável parentString
    if (node->parent != NULL && strcmp(node->parent->data, parentString) == 0)
    {
        printf("%d - %s\n", cont, node->data);
        cont++;
    }

    // Pesquisar nos filhos do nó atual
    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        if (node->children[i] != NULL)
            searchAndPrintNodesWithParent(node->children[i], parentString);        
    }
}

FILE *openFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        exit(1);
    }
    return file;
}

void removeLeadingSpaces(char* str) {
    int len = strlen(str);
    int i, j;

    // Find the index of the first non-space character
    for (i = 0; i < len; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            break;
        }
    }

    // Shift the string to the left, removing leading spaces
    for (j = 0; i < len; i++, j++) {
        str[j] = str[i];
    }

    // Add null terminator to end the string
    str[j] = '\0';
}

TreeNode *readFileAndCreateTree(FILE *file, TreeNode *root)
{
    char line[100];

    TreeNode *parent = NULL;
    TreeNode *atual = NULL;
    root = createNode("pai de todos", NULL);

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (isalpha(line[0]))
        {
            line[strcspn(line, "\n")] = '\0';
            atual = createNode(line, root);
            parent = atual;
            addChild(root, atual);
        }
        else
        {
            line[strcspn(line, "\n")] = '\0';
            removeLeadingSpaces(line);
            TreeNode *grandchild = createNode(line, parent);
            addChild(parent, grandchild);
        }
    }
    return root;
}

// int main()
// {
//     FILE *file = openFile("arqOpcoes.txt");

//     TreeNode *root = NULL;
//     root = readFileAndCreateTree(file, root);

//     fclose(file);

//     const char *parentValueToSearch = "pai de todos";
//     cont = 1;
//     searchAndPrintNodesWithParent(root, parentValueToSearch);

//     // Liberar a memória da árvore
//     freeTree(root);

//     return 0;
// }