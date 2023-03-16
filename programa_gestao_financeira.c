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

int menu()
{
    int opt;
    printf("Escolha uma opção:\n");
    printf("1 - Inserir gasto\n2 - Remover gasto\n3 - Mostrar gastos\n4 - Sair\n");
    scanf("%d", &opt);
    if (opt == 1)
    {
        printf("1\n");
    }
    else if (opt == 2)
    {
        printf("2\n");
    }
    else if (opt == 3)
    {
        printf("3\n");
    }
    else if (opt == 4)
    {
        printf("Volte sempre!\n");
    }
    else
    {
        printf("Opção inválida\n");
    }

    return opt;
}

void criar_node_geral(geral_head* head, char string[50]){
    geral_node *novo;
    novo = (geral_node*)malloc(sizeof(geral_node));
    novo->proximo = NULL;
    strcpy(novo->class_geral, string);
}

int main(int argc, char const *argv[])
{
    while (1)
    {
        int opcao_1 = menu();
        if (opcao_1 == 4)
            break;
    }
    return 0;
}
