#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

#define TAMANHO 1024
#define TAMANHO_MENOR 256
#define CAMINHO "geral.csv"

// struct no lista no
typedef struct no
{
    int contagem_de_ponto_e_virgula;      // contagem de argumentos
    char linha_inteira[TAMANHO];          // todo o conteúdo da linha
    char class_geral[TAMANHO_MENOR];      // classificação geral do gasto
    char class_especifico[TAMANHO_MENOR]; // classificação específica do gasto
    float valor;                          // Valor gasto
    char mes[TAMANHO_MENOR];              // mes
    int ano;                              // ano
    struct no *proximo;                   // próximo da lista

} no;

// struct cabeça lista no
typedef struct cabeca
{
    no *primeiro;

} head;

void menuValor(char *geral_escolhido, char *especifico_escolhido, head *cabeca);
const char *menu_mes();

void mostrar_lista(head *cabeca)
{
    no *atual;
    atual = cabeca->primeiro;
    if (cabeca->primeiro == NULL)
    {
        printf("Cabeça está vazia\n");
        return;
    }

    int count = 0;
    while (atual != NULL)
    {
        count++;
        atual = atual->proximo;
    }

    if (count > 5)
    {
        int skipCount = count - 5;
        atual = cabeca->primeiro;
        while (skipCount > 0)
        {
            atual = atual->proximo;
            skipCount--;
        }
    }

    while (atual != NULL)
    {
        printf("    especifico:%s\n", atual->class_especifico);
        printf("        valor:%.2f\n", atual->valor);
        printf("            mes:%s\n\n", atual->mes);
        atual = atual->proximo;
    }
}

void criar_no_geral_leitura(head *cabeca, char *string)
{
    no *novo;
    novo = (no *)malloc(sizeof(no));
    if (novo == NULL)
    {
        printf("Falha ao alocar novo node");
        return;
    }

    strcpy(novo->linha_inteira, string);
    if (cabeca->primeiro == NULL)
    {
        cabeca->primeiro = novo;
        return;
    }

    no *atual = cabeca->primeiro;
    while (atual->proximo != NULL)
        atual = atual->proximo;
    atual->proximo = novo;
    novo->proximo = NULL;
}

void concatenar_tudo(char *linha_inteira, char *geral, char *especifico, float valor, char *mes)
{
    char txt_float[10];
    snprintf(txt_float, sizeof(txt_float), "%.2f", valor); // convert float value to string with 2 decimal places

    strcat(linha_inteira, geral);      // concatenate geral to string with a maximum of (sizeof(string) - strlen(string) - 1) characters
    strcat(linha_inteira, ";");        // concatenate ";" to string
    strcat(linha_inteira, especifico); // concatenate especifico to string
    strcat(linha_inteira, ";");        // concatenate ";" to string
    strcat(linha_inteira, txt_float);  // concatenate txt_float to string
    strcat(linha_inteira, ";");        // concatenate ";" to string
    strcat(linha_inteira, mes);        // concatenate mes to string
    strcat(linha_inteira, "\r");       // concatenate "\r" to string
    strcat(linha_inteira, "\0");       // concatenate "\0" to string
}

void printar_no_arquivo(char *linha_inteira)
{
    FILE *geral;
    geral = fopen(CAMINHO, "a");
    if (geral == NULL)
    {
        printf("Erro ao abrir arquivo");
        exit;
    }

    fprintf(geral, "%s", linha_inteira);

    fclose(geral);
}

void criar_no_geral_escrita(head *cabeca, char *geral, char *especifico, float valor, char *mes)
{
    no *novo;
    novo = (no *)malloc(sizeof(no));
    novo->proximo = NULL;
    if (novo == NULL)
    {
        printf("Falha ao alocar novo node");
        return;
    }

    if (cabeca->primeiro == NULL)
    {
        strcpy(novo->class_geral, geral);
        strcpy(novo->class_especifico, especifico);
        novo->valor = valor;
        strcpy(novo->mes, mes);
        strcpy(novo->linha_inteira, "\0");
        concatenar_tudo(novo->linha_inteira, geral, especifico, valor, mes);
        puts(novo->linha_inteira);
        printar_no_arquivo(novo->linha_inteira);
        cabeca->primeiro = novo;
        return;
    }

    no *atual = cabeca->primeiro;
    while (atual->proximo != NULL)
        atual = atual->proximo;
    atual->proximo = novo;
    strcpy(novo->class_geral, geral);
    strcpy(novo->class_especifico, especifico);
    novo->valor = valor;
    strcpy(novo->mes, mes);
    strcpy(novo->linha_inteira, "\0");
    concatenar_tudo(novo->linha_inteira, geral, especifico, valor, mes);
    puts(novo->linha_inteira);
    printar_no_arquivo(novo->linha_inteira);
}

void liberar_memoria(head *cabeca)
{
    no *atual;
    no *auxiliar;
    atual = cabeca->primeiro;
    while (atual != NULL)
    {
        auxiliar = atual;
        atual = auxiliar->proximo;
        free(auxiliar);
    }
    free(cabeca);
}

void menu_i(TreeNode *root, TreeNode *geral_escolhido, head *cabeca)
{
    int escolha;
    system("clear");
    printf("Sua escolha foi: %s\n\n", geral_escolhido->data);
    printf("Escolha a Classe específica:\n");
    cont = 1;
    searchAndPrintNodesWithParent(root, geral_escolhido->data);
    scanf("%d", &escolha);
    system("clear");
    TreeNode *especifico_escolhido = geral_escolhido->children[escolha - 1];
    printf("Sua escolha: %s\n", especifico_escolhido->data);
    menuValor(geral_escolhido->data, especifico_escolhido->data, cabeca);
}

void menu_e(head *cabeca)
{
    int escolha;
    FILE *file = openFile("arqOpcoes.txt");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo");
        exit;
    }
    TreeNode *root = NULL;
    root = readFileAndCreateTree(file, root);

    fclose(file);
    char parentValueToSearch[12] = "pai de todos";
    printf("Escolha a Classe geral:\n");
    searchAndPrintNodesWithParent(root, parentValueToSearch);
    scanf("%d", &escolha);
    TreeNode *geral_escolhido = root->children[escolha - 1];
    if (root->children[escolha - 1] == NULL)
    {
        printf("Opção inválida\n");
        return;
    }
    
    printf("Sua escolha: %s\n", geral_escolhido->data);
    menu_i(root, geral_escolhido, cabeca);
}

void menuValor(char *geral_escolhido, char *especifico_escolhido, head *cabeca)
{
    float valor;
    char mes[10] = "\0";
    printf("\nInsira o valor:\n");
    scanf("%f", &valor);
    strcpy(mes, menu_mes()) ;
    criar_no_geral_escrita(cabeca, geral_escolhido, especifico_escolhido, valor, mes);
}

const char *menu_mes()
{
    int num_mes;
    printf("Insira o número do mês a ser adicionado:\n");
    printf("1 - Janeiro\n");
    printf("2 - Fevereiro\n");
    printf("3 - Marco\n");
    printf("4 - Abril\n");
    printf("5 - Maio\n");
    printf("6 - Junho\n");
    printf("7 - Julho\n");
    printf("8 - Agosto\n");
    printf("9 - Setembro\n");
    printf("10 - Outubro\n");
    printf("11 - Novembro\n");
    printf("12 - Dezembro\n");
    printf("Mes:\n");
    scanf("%d", &num_mes);
    if (num_mes == 1)
        return "Janeiro";
    else if (num_mes == 2)
        return "Fevereiro";
    else if (num_mes == 3)
        return "Março";
    else if (num_mes == 4)
        return "Abril";
    else if (num_mes == 5)
        return "Maio";
    else if (num_mes == 6)
        return "Junho";
    else if (num_mes == 7)
        return "Julho";
    else if (num_mes == 8)
        return "Agosto";
    else if (num_mes == 9)
        return "Setembro";
    else if (num_mes == 10)
        return "Outubro";
    else if (num_mes == 11)
        return "Novembro";
    else if (num_mes == 12)
        return "Dezembro";
    else
    {
        printf("Número inválido, insira novamente\n");
        return menu_mes();
    }
}

int menu(int *opt, head *cabeca)
{

    printf("---------------------------------------------------------------------\n");
    printf("Escolha uma opcao:\n");
    printf("1 - Inserir registro\n2 - Remover último registro\n3 - Mostrar registros\n4 - Sair\n");
    scanf("%d", opt);
    if (*opt == 1)
        menu_e(cabeca);
    else if (*opt == 2)
        printf("2\n");
    else if (*opt == 3)
    {
        system("clear");
        mostrar_lista(cabeca);
    }
    else if (*opt == 4)
    {
        liberar_memoria(cabeca);
        printf("Volte sempre!\n");
    }
    else
    {
        printf("Opção invalida\n");
        return 4;
    }

    return *opt;
}

void pegar_todo_o_conteudo_do_arquivo(head *cabeca)
{
    FILE *geral;
    geral = fopen(CAMINHO, "r");
    if (geral == NULL)
    {
        printf("Erro ao abrir arquivo");
        fclose(geral);
        return;
    }

    char line[TAMANHO_MENOR];

    fgets(line, TAMANHO_MENOR, geral);
    while (!feof(geral))
    {
        fgets(line, TAMANHO_MENOR, geral);
        line[strcspn(line, "\r")] = '\0';
        criar_no_geral_leitura(cabeca, line);
    }
    fclose(geral);
}

void separar_linha(head *cabeca)
{
    no *atual = cabeca->primeiro;
    char *next = atual->linha_inteira;
    int entrar = 0;
    while (atual != NULL)
    {
        next = strtok(atual->linha_inteira, ";");
        while (next != NULL)
        {
            if (entrar == 0)
            {
                strcpy(atual->class_geral, next);
                // printf("geral: %s\n", atual->class_geral);
                next = strtok(NULL, ";"); // get the next substring
                entrar++;
            }
            else if (entrar == 1)
            {
                strcpy(atual->class_especifico, next);
                // printf("especifico: %s\n", next);
                next = strtok(NULL, ";"); // get the next substring
                entrar++;
            }
            else if (entrar == 2)
            {
                atual->valor = atof(next);
                entrar++;
                // printf("valor: %.2f\n", atual->valor);
                next = strtok(NULL, ";"); // get the next substring
            }
            else if (entrar == 3)
            {
                strcpy(atual->mes, next);
                // printf("mes: %s\n\n", next);
                entrar = 0;
                break;
            }
        }
        atual = atual->proximo;
    }
}

int main(int argc, char const *argv[])
{

    int opcao_1;
    head *lista = (head *)malloc(sizeof(head));
    if (lista == NULL)
    {
        printf("Erro ao alocar lista");
        return -1;
    }
    lista->primeiro = NULL;

    pegar_todo_o_conteudo_do_arquivo(lista);
    separar_linha(lista);
    while (1)
    {
        menu(&opcao_1, lista);
        if (opcao_1 == 4)
            break;
    }
    return 0;
}
