#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tipo_geral_node
{
    char class_geral[50];
    struct tipo_geral_node *proximo;

} geral_node;

typedef struct tipo_geral_head
{
    geral_node *primeiro;

} geral_head;

void criar_node_geral(geral_head *head, char string[50]);

void mostrar_lista(geral_head *cabeca)
{
    geral_node *atual;
    atual = cabeca->primeiro;
    if (cabeca->primeiro == NULL)
    {
        printf("Cabeça está vazia\n");
        return;
    }
    while (atual != NULL)
    {
        printf("%s\n", atual->class_geral);
        atual = atual->proximo;
    }
}

void criar_node_geral(geral_head *head, char string[50])
{
    geral_node *novo;
    geral_node *atual = head->primeiro;
    novo = (geral_node *)malloc(sizeof(geral_node));
    strcpy(novo->class_geral, string);
    if (head->primeiro == NULL)
    {
        head->primeiro = novo;
        return;
    }
    while (1)
    {
        if (atual->proximo == NULL)
        {
            atual->proximo = novo;
            novo->proximo = NULL;
            printf("okay\n");
            break;
        }

        atual = atual->proximo;
    }
}

int menu(int *opt, geral_head *head)
{

    printf("Escolha uma opção:\n");
    printf("1 - Inserir gasto\n2 - Remover gasto\n3 - Mostrar gastos\n4 - Sair\n");
    scanf("%d", opt);
    if (*opt == 1)
    {
        char string[50];
        printf("Insira uma string\n");
        // fgets(string);
        scanf("%s", string);
        criar_node_geral(head, string);
    }
    else if (*opt == 2)
    {
        printf("2\n");
    }
    else if (*opt == 3)
    {
        mostrar_lista(head);
    }
    else if (*opt == 4)
    {
        printf("Volte sempre!\n");
    }
    else
    {
        printf("Opção inválida\n");
        return 4;
    }

    return *opt;
}

int main(int argc, char const *argv[])
{
    geral_head *head = (geral_head *)malloc(sizeof(geral_head));
    head->primeiro = NULL;
    int opcao_1;
    while (1)
    {
        menu(&opcao_1, head);
        if (opcao_1 == 4)
            break;
    }
    return 0;
}
