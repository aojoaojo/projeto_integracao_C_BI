#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// create a function that tries to open a file called "categorias.txt" and if it doesn't exist, create it
void criar_arquivo_categorias()
{
    FILE *categorias;
    categorias = fopen("categorias.txt", "r");
    if (categorias == NULL)
    {
        categorias = fopen("categorias.txt", "w");
        if (categorias == NULL)
        {
            printf("Erro ao criar arquivo");
            exit;
        }
        fprintf(categorias, "alimentacao\n");
        fprintf(categorias, "   supermercado\n");
        fprintf(categorias, "   restaurante\n");
        fprintf(categorias, "   outros\n");
        fprintf(categorias, "moradia\n");
        fprintf(categorias, "   aluguel\n");
        fprintf(categorias, "   condominio\n");
        fprintf(categorias, "   outros\n");
        fprintf(categorias, "transporte\n");
        fprintf(categorias, "   onibus\n");
        fprintf(categorias, "   uber\n");
        fprintf(categorias, "   outros\n");
        fprintf(categorias, "lazer\n");
        fprintf(categorias, "   parque\n");
        fprintf(categorias, "   cinema\n");
        fprintf(categorias, "   outros\n");
        fprintf(categorias, "outros\n");
        fprintf(categorias, "   outros\n");
        fclose(categorias);
    }
    else
    {
        fclose(categorias);
    }
}

void mostrar_lista(head *cabeca)
{
    no *atual;
    atual = cabeca->primeiro;
    if (cabeca->primeiro == NULL)
    {
        printf("Cabeça está vazia\n");
        return;
    }
    while (atual != NULL)
    {
        // printf("linha inteira:%s\n", atual->linha_inteira);
        printf("geral:%s\n", atual->class_geral);
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

void remover_ultima_linha()
{
    FILE *fp, *fp_temp;
    int ch, count;

    // Open the original file for reading
    fp = fopen(CAMINHO, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s\n", CAMINHO);
        return;
    }

    // Count the number of lines in the file
    count = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            count++;
        }
    }

    // Close the file and reopen it for writing
    fclose(fp);
    fp = fopen(CAMINHO, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s\n", CAMINHO);
        return;
    }
    fp_temp = fopen("temp.csv", "w");
    if (fp_temp == NULL)
    {
        printf("Error: could not create temporary file\n");
        fclose(fp);
        return;
    }

    // Copy all lines except the last one to the temporary file
    int line = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            line++;
        }
        if (line != count)
        {
            fputc(ch, fp_temp);
        }
    }

    // Close the files and replace the original file with the temporary file
    fclose(fp);
    fclose(fp_temp);
    remove(CAMINHO);
    rename("temp.csv", CAMINHO);
}

char *returns_the_line_if_it_do_not_start_with_space_on_a_file(char *file_name, int number_line)
{
    FILE *file;
    file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo");
        exit;
    }
    char line[100];
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (i == number_line)
        {
            if (line[0] != ' ')
            {
                return line;
                fclose(file);
            }
        }
        i++;
    }
    fclose(file);
    return NULL;
}

char *returns_the_line_if_it_starts_with_space(char *file_name, int number_line){
    FILE *file;
    file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo");
        exit;
    }
    char line[40];
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (i == number_line)
        {
            if (line[0] == ' ')
            {
                return line;
                fclose(file);
            }
        }
        i++;
    }
    fclose(file);
    return NULL;
}

// char *removes_space_from_the_beginning_of_a_string(char *string)
// {
//     int i = 0;
//     while (string[i] == ' ')
//     {
//         i++;
//     }
//     return string + i;
// }

char *menu_e_1(int *escolha_geral)
{
    int i = 0;
    // create a vector of strings that will storage the name of the classes that will be taken at the categorias.txt file
    char **vetor;
    // create variables that will storage the name of the classes that will be taken at the categorias.txt file
    char line[40];
    // create a pointer to the file categorias.txt
    FILE *categorias;
    // open the file categorias.txt
    categorias = fopen("categorias.txt", "r");
    if (categorias == NULL)
    {
        printf("Erro ao abrir arquivo");
        exit;
    }
    // read the file categorias.txt and store the name of the classes in the variables created before
    // the loop will stop when the end of the file is reached
    // the loop will also reallocate the vector of strings when the number of classes is bigger than the size of the vector
    // the fscanf will read the file and store the name of the classes in the variables created before
    // the name of the class is the first thing in the line, so the fscanf will read the first thing in the line untill the ";" and store it in the variable

    vetor = (char **)malloc(sizeof(char *));
    while (fgets(line, 40, categorias) != EOF)
    {
        if (returns_the_line_if_it_do_not_start_with_space_on_a_file("categorias.txt", i) != NULL)
        {
            strcpy(line, returns_the_line_if_it_do_not_start_with_space_on_a_file("categorias.txt", i));
        }
        else
        {
            // strcpy(line, removes_space_from_the_beginning_of_a_string(returns_the_line_if_it_starts_with_space("categorias.txt", i)));   
            strcpy(line, returns_the_line_if_it_starts_with_space("categorias.txt", i));   
        }
        
        if (i == 0)
        {
            vetor[i] = (char *)malloc(sizeof(char) * (strlen(line) + 1));
            strcpy(vetor[i], line);
        }
        else
        {
            vetor = (char **)realloc(vetor, sizeof(char *) * (i + 1));
            vetor[i] = (char *)malloc(sizeof(char) * (strlen(line) + 1));
            strcpy(vetor[i], line);
        }
        i++;
    }

    // char e1[] = "Alimentacao", e2[] = "Saude", e3[] = "Transporte", e4[] = "Pessoal", e5[] = "Casa", e6[] = "Viagens", e7[] = "Contas", e8[] = "Investidos", e0[] = "Para retornar";
    printf("Escolha a Classe geral que deseja incluir:\n");
    for (int j = 0; j < i; j++)
    {
        printf("%d - %s\n", j, vetor[j]);
    }
    printf("Digite o número:\n");
    scanf("%d", escolha_geral);
    if (*vetor[*escolha_geral] == NULL)
        return "0";
    return vetor[*escolha_geral];
}

char *menu_i_1(int *escolha_2)
{

    char f1[] = "Mercado", f2[] = "Barzinho", f3[] = "Restaurante";
    printf("Escolha a Classe específica que deseja incluir:\n");
    printf("1 - %s\n", f1);
    printf("2 - %s\n", f2);
    printf("3 - %s\n", f3);
    printf("0 - Para retornar\n");
    scanf("%d", escolha_2);
    if (*escolha_2 == 1)
        return "Mercado";
    else if (*escolha_2 == 2)
        return "Barzinho";
    else if (*escolha_2 == 3)
        return "Restaurante";
    else
        return "0";
}

char *menu_i_2(int *escolha_2)
{
    char g1[] = "Cosmeticos", g2[] = "Medicamentos", g3[] = "Aparelho Auditivo", g4[] = "Dentista", g5[] = "Cassi";
    printf("Escolha a Classe específica que deseja incluir:\n");
    printf("1 - %s\n", g1);
    printf("2 - %s\n", g2);
    printf("3 - %s\n", g3);
    printf("4 - %s\n", g4);
    printf("5 - %s\n", g5);
    printf("0 - Para retornar\n");
    scanf("%d", escolha_2);
    if (*escolha_2 == 1)
        return "Cosmeticos";
    else if (*escolha_2 == 2)
        return "Medicamentos";
    else if (*escolha_2 == 3)
        return "Aparelho Auditivo";
    else if (*escolha_2 == 4)
        return "Dentista";
    else if (*escolha_2 == 5)
        return "Cassi";
    else
        return "0";
}
char *menu_i_3(int *escolha_2)
{
    char h1[] = "Gasolina", h2[] = "Carro Seguro", h3[] = "IPVA", h4[] = "Carro Gasto", h5[] = "Uber";
    printf("Escolha a Classe específica que deseja incluir:\n");
    printf("1 - %s\n", h1);
    printf("2 - %s\n", h2);
    printf("3 - %s\n", h3);
    printf("4 - %s\n", h4);
    printf("5 - %s\n", h5);
    printf("0 - Para retornar\n");
    scanf("%d", escolha_2);
    if (*escolha_2 == 1)
        return "Gasolina";
    else if (*escolha_2 == 2)
        return "Carro Seguro";
    else if (*escolha_2 == 3)
        return "IPVA";
    else if (*escolha_2 == 4)
        return "Carro Gasto";
    else if (*escolha_2 == 5)
        return "Uber";
    else
        return "0";
}
char *menu_i_4(int *escolha_2)
{
    char i1[] = "Celular", i2[] = "Roupa", i3[] = "Presentes", i4[] = "Extra", i5[] = "Formatura Lili", i6[] = "Jogos";
    printf("Escolha a Classe específica que deseja incluir:\n");
    printf("1 - %s\n", i1);
    printf("2 - %s\n", i2);
    printf("3 - %s\n", i3);
    printf("4 - %s\n", i4);
    printf("5 - %s\n", i5);
    printf("6 - %s\n", i6);
    printf("0 - Para retornar\n");
    scanf("%d", escolha_2);
    if (*escolha_2 == 1)
        return "Celular";
    else if (*escolha_2 == 2)
        return "Roupa";
    else if (*escolha_2 == 3)
        return "Presentes";
    else if (*escolha_2 == 4)
        return "Extra";
    else if (*escolha_2 == 5)
        return "Formatura Lili";
    else if (*escolha_2 == 6)
        return "Jogos";
    else
        return "0";
}
char *menu_i_5(int *escolha_2)
{
    char j1[] = "Utensilios", j2[] = "Internet", j3[] = "Luz", j4[] = "Condominio", j5[] = "Reforma/ Moveis", j6[] = "TV", j7[] = "IPTU", j8[] = "Gas";
    printf("Escolha a Classe específica que deseja incluir:\n");
    printf("1 - %s\n", j1);
    printf("2 - %s\n", j2);
    printf("3 - %s\n", j3);
    printf("4 - %s\n", j4);
    printf("5 - %s\n", j5);
    printf("6 - %s\n", j6);
    printf("7 - %s\n", j7);
    printf("8 - %s\n", j8);
    printf("0 - Para retornar\n");
    scanf("%d", escolha_2);
    if (*escolha_2 == 1)
        return "Utensilios";
    else if (*escolha_2 == 2)
        return "Internet";
    else if (*escolha_2 == 3)
        return "Luz";
    else if (*escolha_2 == 4)
        return "Condominio";
    else if (*escolha_2 == 5)
        return "Reforma/ Moveis";
    else if (*escolha_2 == 6)
        return "TV";
    else if (*escolha_2 == 7)
        return "IPTU";
    else if (*escolha_2 == 8)
        return "Gas";
    else
        return "0";
}
char *menu_i_6(int *escolha_2)
{
    char k1[] = "Passagem/ Pct", k2[] = "Local";
    printf("Escolha a Classe específica que deseja incluir:\n");
    printf("1 - %s\n", k1);
    printf("2 - %s\n", k2);
    printf("0 - Para retornar\n");
    scanf("%d", escolha_2);
    if (*escolha_2 == 1)
        return "Passagem/ Pct";
    else if (*escolha_2 == 2)
        return "Local";
    else
        return "0";
}
char *menu_i_7(int *escolha_2)
{
    char l1[] = "DAS", l2[] = "Taxa Cartao";
    printf("Escolha a Classe específica que deseja incluir:\n");
    printf("1 - %s\n", l1);
    printf("2 - %s\n", l2);
    printf("0 - Para retornar\n");
    scanf("%d", escolha_2);
    if (*escolha_2 == 1)
        return "DAS";
    else if (*escolha_2 == 2)
        return "Taxa Cartao";
    else
        return "0";
}
char *menu_i_8(int *escolha_2)
{
    char m1[] = "Investidos";
    printf("Escolha a Classe específica que deseja incluir:\n");
    printf("1 - %s\n", m1);
    printf("0 - Para retornar\n");
    scanf("%d", escolha_2);
    if (*escolha_2 == 1)
        return "Investidos";
    else
        return "0";
}

// Função para selecionar o mês
char *menu_mes()
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
    printf("1 - Inserir gasto\n2 - Remover ultimo gasto\n3 - Mostrar gastos\n4 - Sair\n");
    scanf("%d", opt);
    if (*opt == 1)
    {
        int escolha_geral;
        int escolha_2;
        char geral[TAMANHO_MENOR] = "\0";
        char especifico[TAMANHO_MENOR] = "\0";
        char mes[10] = "\0";
        float valor;
        strcpy(geral, menu_e_1(&escolha_geral));
        switch (escolha_geral)
        {
        case 1:
            strcpy(especifico, menu_i_1(&escolha_2));
            if (escolha_2 == 0)
                break;
            printf("\nInsira o valor:\n");
            scanf("%f", &valor);
            strcpy(mes, menu_mes());
            criar_no_geral_escrita(cabeca, geral, especifico, valor, mes);
            break;
        case 2:
            strcpy(especifico, menu_i_2(&escolha_2));
            if (escolha_2 == 0)
                break;
            printf("\nInsira o valor:\n");
            scanf("%f", &valor);
            strcpy(mes, menu_mes());
            criar_no_geral_escrita(cabeca, geral, especifico, valor, mes);
            break;
        case 3:
            strcpy(especifico, menu_i_3(&escolha_2));
            if (escolha_2 == 0)
                break;
            printf("\nInsira o valor:\n");
            scanf("%f", &valor);
            strcpy(mes, menu_mes());
            criar_no_geral_escrita(cabeca, geral, especifico, valor, mes);
            break;
        case 4:

            strcpy(especifico, menu_i_4(&escolha_2));
            if (escolha_2 == 0)
                break;
            printf("\nInsira o valor:\n");
            scanf("%f", &valor);
            strcpy(mes, menu_mes());
            criar_no_geral_escrita(cabeca, geral, especifico, valor, mes);
            break;
        case 5:

            strcpy(especifico, menu_i_5(&escolha_2));
            if (escolha_2 == 0)
                break;
            printf("\nInsira o valor:\n");
            scanf("%f", &valor);
            strcpy(mes, menu_mes());
            criar_no_geral_escrita(cabeca, geral, especifico, valor, mes);
            break;
        case 6:

            strcpy(especifico, menu_i_6(&escolha_2));
            if (escolha_2 == 0)
                break;
            printf("\nInsira o valor:\n");
            scanf("%f", &valor);
            strcpy(mes, menu_mes());
            criar_no_geral_escrita(cabeca, geral, especifico, valor, mes);
            break;
        case 7:

            strcpy(especifico, menu_i_7(&escolha_2));
            if (escolha_2 == 0)
                break;
            printf("\nInsira o valor:\n");
            scanf("%f", &valor);
            strcpy(mes, menu_mes());
            criar_no_geral_escrita(cabeca, geral, especifico, valor, mes);
            break;
        case 8:
            strcpy(especifico, menu_i_8(&escolha_2));
            if (escolha_2 == 0)
                break;
            printf("\nInsira o valor:\n");
            scanf("%f", &valor);
            strcpy(mes, menu_mes());
            criar_no_geral_escrita(cabeca, geral, especifico, valor, mes);
            break;
        default:
            break;
        }
    }
    else if (*opt == 2)
    {
        char delete;
        printf("Tem certeza que deseja remover o ultimo gasto? S/N\n");
        scanf("%*c%c", &delete);
        if (delete == 'S' || delete == 's')
        {
            remover_ultima_linha();
        }
        else
        {
            return 0;
        }
    }

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
    criar_arquivo_categorias();
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
