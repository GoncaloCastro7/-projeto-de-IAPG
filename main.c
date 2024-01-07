#include <stdio.h>
#include <string.h>

#define MAX_CAES 1000
#define MAX_EVENTOS 5000

typedef struct {
    int id;
    char genero;
    float peso;
    char raca[50];
    char nome[50];
} Cao;

typedef struct {
    char tipo[20];
    int id_cao;
} Evento;

Cao base_dados_caes[MAX_CAES];
Evento historico_caes[MAX_EVENTOS];
int num_caes = 0;
int num_eventos = 0;

void lerConfiguracoes();
void menuPrincipal();
void inserirNovoCao();
void inserirNovoEvento();
void pesquisarCaoPorID();
void pesquisarCaoPorPorte();
void salvarDadosEmBinario();
void carregarDadosEmBinario();
void salvarDadosEmTexto();
void carregarDadosEmTexto();

int main() {
    lerConfiguracoes();
    carregarDadosEmBinario();
    menuPrincipal();
    salvarDadosEmBinario();
    return 0;
}
void lerConfiguracoes() {

    FILE *file_config = fopen("config_bd_canina.txt", "r");

    if (file_config == NULL) {
        printf("Erro ao abrir o arquivo de configuração.\n");
        return;
    }

    // Adicione a lógica para ler as configurações aqui

    fclose(file_config);
}

void menuPrincipal() {
    int opcao;
    do {
        printf("\n----- Menu Principal -----\n");
        printf("1. Inserir novo cao\n");
        printf("2. Inserir novo evento\n");
        printf("3. Pesquisar cao por ID\n");
        printf("4. Pesquisar cao por porte\n");
        printf("5. Salvar dados em binario\n");
        printf("6. Carregar dados em binario\n");
        printf("7. Salvar dados em texto\n");
        printf("8. Carregar dados em texto\n");
        printf("0. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirNovoCao();
                break;
            case 2:
                inserirNovoEvento();
                break;
            case 3:
                pesquisarCaoPorID();
                break;
            case 4:
                pesquisarCaoPorPorte();
                break;
            case 5:
                salvarDadosEmBinario();
                break;
            case 6:
                carregarDadosEmBinario();
                break;
            case 7:
                salvarDadosEmTexto();
                break;
            case 8:
                carregarDadosEmTexto();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}
void inserirNovoCao() {
    if (num_caes < MAX_CAES) {
        printf("ID do novo cao: ");
        scanf("%d", &base_dados_caes[num_caes].id);

        printf("Genero (M/F): ");
        scanf(" %c", &base_dados_caes[num_caes].genero);

        printf("Peso: ");
        scanf("%f", &base_dados_caes[num_caes].peso);

        printf("Raca: ");
        scanf("%s", base_dados_caes[num_caes].raca);

        printf("Nome: ");
        scanf("%s", base_dados_caes[num_caes].nome);

        num_caes++;
        printf("Cao inserido com sucesso.\n");
    } else {
        printf("Limite maximo de caes atingido.\n");
    }
}

void inserirNovoEvento() {

    if (num_eventos < MAX_EVENTOS) {
        printf("ID do cao associado ao evento: ");
        scanf("%d", &historico_caes[num_eventos].id_cao);

        printf("Tipo de evento (Acidente/Doenca/MudancaMorada/MudancaDono): ");
        scanf("%s", historico_caes[num_eventos].tipo);


        num_eventos++;
        printf("Evento inserido com sucesso.\n");
    } else {
        printf("Limite maximo de eventos atingido.\n");
    }
}


void pesquisarCaoPorID() {
    int id;
    printf("Digite o ID do cao a ser pesquisado: ");
    scanf("%d", &id);

    for (int i = 0; i < num_caes; i++) {
        if (base_dados_caes[i].id == id) {
            printf("Cao encontrado:\n");
            printf("ID: %d\n", base_dados_caes[i].id);
            printf("Genero: %c\n", base_dados_caes[i].genero);
            printf("Peso: %.2f\n", base_dados_caes[i].peso);
            printf("Raca: %s\n", base_dados_caes[i].raca);
            printf("Nome: %s\n", base_dados_caes[i].nome);
            printf("eventos: %s\n", historico_caes[i].tipo);

            return;
        }
    }

    printf("Cao com ID %d não encontrado.\n", id);
}

void pesquisarCaoPorPorte() {
    char porte[20];
    printf("Digite o porte desejado (pequeno/medio/grande): ");
    scanf("%s", porte);

    float limite_inferior, limite_superior;

    if (strcmp(porte, "pequeno") == 0) {
        limite_inferior = 0;
        limite_superior = 10;
    } else if (strcmp(porte, "medio") == 0) {
        limite_inferior = 10;
        limite_superior = 25;
    } else if (strcmp(porte, "grande") == 0) {
        limite_inferior = 25;
        limite_superior = 100;
    } else {
        printf("Porte invalido.\n");
        return;
    }

    printf("Caes no porte %s:\n", porte);
    for (int i = 0; i < num_caes; i++) {
        if (base_dados_caes[i].peso >= limite_inferior && base_dados_caes[i].peso < limite_superior) {
            printf("Cao encontrado:\n");
            printf("ID: %d\n", base_dados_caes[i].id);
            printf("Genero: %c\n", base_dados_caes[i].genero);
            printf("Peso: %.2f\n", base_dados_caes[i].peso);
            printf("Raca: %s\n", base_dados_caes[i].raca);
            printf("Nome: %s\n", base_dados_caes[i].nome);
            printf("eventos: %s\n", historico_caes[i].tipo);
        }
    }
}

void salvarDadosEmBinario() {
    FILE *file_caes = fopen("bd_caes.dat", "wb");
    FILE *file_eventos = fopen("historico_caes.dat", "wb");

    if (file_caes == NULL || file_eventos == NULL) {
        printf("Erro ao abrir arquivos binários para escrita.\n");
        return;
    }

    fwrite(&num_caes, sizeof(int), 1, file_caes);
    fwrite(base_dados_caes, sizeof(Cao), num_caes, file_caes);

    fwrite(&num_eventos, sizeof(int), 1, file_eventos);
    fwrite(historico_caes, sizeof(Evento), num_eventos, file_eventos);

    fclose(file_caes);
    fclose(file_eventos);
}

void carregarDadosEmBinario() {
    FILE *file_caes = fopen("bd_caes.dat", "rb");
    FILE *file_eventos = fopen("historico_caes.dat", "rb");

    if (file_caes == NULL || file_eventos == NULL) {
        printf("Arquivos binários não encontrados ou erro ao abrir.\n");
        return;
    }

    fread(&num_caes, sizeof(int), 1, file_caes);
    fread(base_dados_caes, sizeof(Cao), num_caes, file_caes);

    fread(&num_eventos, sizeof(int), 1, file_eventos);
    fread(historico_caes, sizeof(Evento), num_eventos, file_eventos);

    fclose(file_caes);
    fclose(file_eventos);
}

void salvarDadosEmTexto() {
    FILE *file_caes = fopen("bd_caes.txt", "w");
    FILE *file_eventos = fopen("historico_caes.txt", "w");

    if (file_caes == NULL || file_eventos == NULL) {
        printf("Erro ao abrir arquivos de texto para escrita.\n");
        return;
    }

    for (int i = 0; i < num_caes; i++) {
        fprintf(file_caes, "%d %c %f %s %s\n", base_dados_caes[i].id, base_dados_caes[i].genero,
                base_dados_caes[i].peso, base_dados_caes[i].raca, base_dados_caes[i].nome);
    }

    for (int i = 0; i < num_eventos; i++) {
        fprintf(file_eventos, "%s %d\n", historico_caes[i].tipo, historico_caes[i].id_cao);
    }

    fclose(file_caes);
    fclose(file_eventos);
}

void carregarDadosEmTexto() {
    FILE *file_caes = fopen("bd_caes.txt", "r");
    FILE *file_eventos = fopen("historico_caes.txt", "r");

    if (file_caes == NULL || file_eventos == NULL) {
        printf("Arquivos de texto não encontrados ou erro ao abrir.\n");
        return;
    }

    while (fscanf(file_caes, "%d %c %f %s %s", &base_dados_caes[num_caes].id, &base_dados_caes[num_caes].genero,
                  &base_dados_caes[num_caes].peso, base_dados_caes[num_caes].raca,
                  base_dados_caes[num_caes].nome) == 5) {
        num_caes++;
    }

    while (fscanf(file_eventos, "%s %d", historico_caes[num_eventos].tipo, &historico_caes[num_eventos].id_cao) == 2) {
        num_eventos++;
    }

    fclose(file_caes);
    fclose(file_eventos);
}
