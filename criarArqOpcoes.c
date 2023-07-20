#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char confirmar;

void inserirTipoEspecifico(FILE *arq, char opcao[50])
{
    char especifico[50];
    system("clear");
    printf("Digite um tipo especifico de gasto que deseja inserir em '%s' (por exemplo: Aluguel, Luz, Água, Gasolina, Remédios):\n", opcao);
    fflush(stdin);
    fgets(especifico, sizeof(especifico), stdin);
    especifico[strcspn(especifico, "\n")] = '\0';
    system("clear");
    printf("Tem certeza que deseja inserir o tipo especifico '%s' no arquivo? (S/N)\n", especifico);
    scanf("%c%*c", &confirmar);
    if (confirmar == 'S' || confirmar == 's')
    {
        fprintf(arq, "  %s\n", especifico);
        system("clear");
        printf("Tipo especifico inserido com sucesso\n\n");
    }
    else
    {
        system("clear");
        printf("Tipo especifico não inserido\n");
        exit(0);
    }
    printf("Deseja inserir outro tipo especifico? (S/N)\n");
    scanf("%c%*c", &confirmar);
    if (confirmar == 'S' || confirmar == 's')
    {
        inserirTipoEspecifico(arq, opcao);
    }
}

void inserirGastoGeral(FILE *arq)
{
    char opcao[50];
    system("clear");
    printf("Digite uma classe de gastos que deseja inserir no arquivo (por exemplo: Pessoal, Saúde, Casa, Viagens, Transporte):\n");
    fgets(opcao, sizeof(opcao), stdin);
    opcao[strcspn(opcao, "\n")] = '\0';
    system("clear");
    printf("Tem certeza que deseja inserir a classe '%s' no arquivo? (S/N)\n", opcao);
    scanf("%c%*c", &confirmar);
    if (confirmar == 'S' || confirmar == 's')
    {
        fprintf(arq, "%s\n", opcao);
        system("clear");
        printf("Classe inserida com sucesso\n");
        inserirTipoEspecifico(arq, opcao);
    }
    else
    {
        printf("Classe não inserida");
    }
}

void menu(FILE *arq)
{
    int opMenu;
    while (1)
    {
        system("clear");
        printf("Digite uma opção:\n");
        printf("1 - Inserir gasto geral\n");
        printf("2 - Sair\n");
        scanf("%d%*c", &opMenu);
        if (opMenu == 1)
            inserirGastoGeral(arq);
        else if (opMenu == 2)
            break;
    }
}
int main()
{
    FILE *arq;
    arq = fopen("arqOpcoes.txt", "r");
    // if (arq != NULL)
    // {
    //     printf("Arquivo aberto com sucesso");
    //     fclose(arq);
    //     return 0;
    // }

    arq = fopen("arqOpcoes.txt", "w");
    printf("Arquivo criado com sucesso\n");

    menu(arq);

    fclose(arq);
    return 0;
}