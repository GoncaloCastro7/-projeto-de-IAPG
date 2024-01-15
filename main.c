#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CAES 1000
#define MAX_EVENTOS 5000

typedef struct {
    int id;
    char genero;
    float peso;
    char raca[50];
    char nome[50];
    char pelagem[50];
    char cor[50];
    char data_nascimento[11];
    char concelho_nascimento[50];
    int pai;
    int mae;
} Cao;

typedef struct {
    char tipo[20];
    int id_cao;
} Evento;

Cao base_dados_caes[MAX_CAES];
Evento historico_caes[MAX_EVENTOS];
int num_caes = 0;
int num_eventos = 0;
float limiteInferiorPequeno, limiteSuperiorPequeno;
float limiteInferiorMedio, limiteSuperiorMedio;
float limiteInferiorGrande, limiteSuperiorGrande;

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
void limparEstruturas();
void pesquisarCaoPorFaixaEtaria();
void pesquisarTiosPorID();
void estatisticasPorteCao();
void extrairEstatisticas(Cao *baseDados, int tamanhoBase);
void verificarIntegridadeHistorico();


int main() {
    lerConfiguracoes();
    menuPrincipal();
    carregarDadosEmBinario();
    salvarDadosEmBinario();
    return 0;
}

void lerConfiguracoes() {
    FILE *file_config;

    file_config= fopen("config_bd_canina.txt", "w");

    limiteInferiorPequeno = 0;
    limiteSuperiorPequeno = 10;
    limiteInferiorMedio = 10;
    limiteSuperiorMedio = 25;
    limiteInferiorGrande = 25;
    limiteSuperiorGrande = 50;

    if (file_config == NULL) {
        printf("Erro ao abrir o arquivo de configuracao.\n");
    }

//fscanf para ler seis valores do arquivo, correspondentes aos limites mencionados anteriormente. Esses valores são atribuídos às variáveis globais.
    fscanf(file_config, "%f %f %f %f %f %f", &limiteInferiorPequeno, &limiteSuperiorPequeno,
           &limiteInferiorMedio, &limiteSuperiorMedio, &limiteInferiorGrande, &limiteSuperiorGrande);

    fclose(file_config);
//Fechamento do arquivo: Fecha o arquivo usando a função fclose.

    printf("Arquivo criado com sucesso.\n");
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
        printf("9. pesquisarTiosPorID\n");
        printf("10. estatisticasPorteCao\n");
        printf("11. pesquisarCaoPorFaixaEtaria\n");
        printf("12. extrairEstatisticas;\n");
        printf("13. verificarIntegridadeHistorico\n");
        printf("14. limpar\n");
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
            case 9:
                pesquisarTiosPorID();
                break;
            case 10:
                estatisticasPorteCao();
                break;
            case 11:
                pesquisarCaoPorFaixaEtaria();
                break;
            case 12:
                extrairEstatisticas(base_dados_caes,10);
                break;
            case 13:
                verificarIntegridadeHistorico();
                break;
            case 14:
                limparEstruturas();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (opcao != 0);
}

void inserirNovoCao() {
    if (num_caes < MAX_CAES) {
        printf("ID do novo cao: ");
        scanf("%d", &base_dados_caes[num_caes].id);
    //os dados fornecidos pelo utilizador são armazenados nas respectivas variáveis da estrutura base_dados_caes[num_caes].
        printf("Genero (M/F): ");
        scanf(" %c", &base_dados_caes[num_caes].genero);

        printf("Peso: ");
        scanf("%f", &base_dados_caes[num_caes].peso);

        printf("Raca: ");
        scanf("%s", base_dados_caes[num_caes].raca);

        printf("Nome: ");
        scanf("%s", base_dados_caes[num_caes].nome);

        printf("Pelagem: ");
        scanf("%s", base_dados_caes[num_caes].pelagem);

        printf("Cor: ");
        scanf("%s", base_dados_caes[num_caes].cor);

        printf("Data de nascimento (DD/MM/AAAA): ");
        scanf("%s", base_dados_caes[num_caes].data_nascimento);

        printf("Concelho de nascimento: ");
        scanf("%s", base_dados_caes[num_caes].concelho_nascimento);

        printf("Mae (ID): ");
        scanf("%d", &base_dados_caes[num_caes].mae);

        printf("Pai (ID): ");
        scanf("%d", &base_dados_caes[num_caes].pai);

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
// Se encontra um cão cujo ID corresponde ao ID fornecido pelo usuário, exibe as informações associadas
    for (int i = 0; i < num_caes; i++) {
        if (base_dados_caes[i].id == id) {
            printf("Cao encontrado:\n");
            printf("ID: %d\n", base_dados_caes[i].id);
            printf("Nome: %s\n", base_dados_caes[i].nome);
            printf("Genero: %c\n", base_dados_caes[i].genero);
            printf("Peso: %.2f\n", base_dados_caes[i].peso);
            printf("Raca: %s\n", base_dados_caes[i].raca);
            printf("Pelagem: %s\n", base_dados_caes[i].pelagem);
            printf("Cor: %s\n", base_dados_caes[i].cor);
            printf("Concelho: %s\n", base_dados_caes[i].concelho_nascimento);
            printf("Pai (ID): %d\n", base_dados_caes[i].pai);
            printf("Mae (ID): %d\n", base_dados_caes[i].mae);
            printf("Data de nascimento: %s\n", base_dados_caes[i].data_nascimento);
            printf("Eventos: %s\n", historico_caes[i].tipo);

            return;
        }
    }

    printf("Cao com ID %d nao encontrado.\n", id);
}

void pesquisarCaoPorPorte() {
    char porte[20];
    printf("Digite o porte desejado (pequeno/medio/grande): ");
    scanf("%s", porte);

    float limite_inferior, limite_superior;
//A função strcmp em C é usada para comparar duas strings.
    if (strcmp(porte, "pequeno") == 0) {
        limite_inferior = 0;
        limite_superior = 10;
    } else if (strcmp(porte, "medio") == 0) {
        limite_inferior = 10;
        limite_superior = 25;
    } else if (strcmp(porte, "grande") == 0) {
        limite_inferior = 25;
        limite_superior = 50;
    } else {
        printf("Porte invalido.\n");
        return;
    }

    printf("Caes no porte %s:\n", porte);
    for (int i = 0; i < num_caes; i++) {
        if (base_dados_caes[i].peso >= limite_inferior && base_dados_caes[i].peso < limite_superior) {
            printf("Cao encontrado:\n");
            printf("ID: %d\n", base_dados_caes[i].id);
            printf("Nome: %s\n", base_dados_caes[i].nome);
            printf("Genero: %c\n", base_dados_caes[i].genero);
            printf("Peso: %.2f\n", base_dados_caes[i].peso);
            printf("Raca: %s\n", base_dados_caes[i].raca);
            printf("Pelagem: %s\n", base_dados_caes[i].pelagem);
            printf("Cor: %s\n", base_dados_caes[i].cor);
            printf("Concelho: %s\n", base_dados_caes[i].concelho_nascimento);
            printf("Pai (ID): %d\n", base_dados_caes[i].pai);
            printf("Mae (ID): %d\n", base_dados_caes[i].mae);
            printf("Data de nascimento: %s\n", base_dados_caes[i].data_nascimento);
            printf("Eventos: %s\n", historico_caes[i].tipo);
        }
    }
}

void pesquisarTiosPorID(Cao* cao) {
    int id;
    printf("Tios do cao com ID: \n");
    scanf("%d",&id);
    if(id == cao->id) {
        int id_mae = cao->mae;
        int id_pai = cao->pai;

        printf("Tios encontrados:\n");

        for (int i = 0; i < num_caes; i++) {
            if ((base_dados_caes[i].id == id_mae || base_dados_caes[i].id == id_pai ||base_dados_caes[i].id == cao->id) && base_dados_caes[i].id != cao->id) {
                printf("ID: %d, Nome: %s\n", base_dados_caes[i].id, base_dados_caes[i].nome);
            }
        }
        if (id_mae == 0 || id_pai == 0) {
            printf("Pai ou mãe desconhecido. Não é possível identificar tios.\n");
        }
    }
}

void estatisticasPorteCao() {
    int contadorPequeno = 0;
    int contadorMedio = 0;
    int contadorGrande = 0;
    for (int i = 0; i < num_caes; i++) {
        float pesoAtual = base_dados_caes[i].peso;

        if (pesoAtual >= limiteInferiorPequeno && pesoAtual < limiteSuperiorPequeno) {
            contadorPequeno++;
        } else if (pesoAtual >= limiteInferiorMedio && pesoAtual < limiteSuperiorMedio) {
            contadorMedio++;
        } else if (pesoAtual >= limiteInferiorGrande && pesoAtual <= limiteSuperiorGrande) {
            contadorGrande++;
        }
    }
    float totalCoes = num_caes;
    // Calcular proporção
    float proporcaoPequeno = (float)contadorPequeno / totalCoes;
    float proporcaoMedio = (float)contadorMedio / totalCoes;
    float proporcaoGrande = (float)contadorGrande / totalCoes;

    // Exibir estatísticas
    printf("Estatisticas de porte:\n");
    printf("Quantidade de caes pequenos: %d\n", contadorPequeno);
    printf("Proporcao de caes pequenos: %f\n", proporcaoPequeno * 100);

    printf("Quantidade de caes medios: %d\n", contadorMedio);
    printf("Proporcao de caes medios: %f\n", proporcaoMedio * 100);

    printf("Quantidade de caes grandes: %d\n", contadorGrande);
    printf("Proporcao de caes grandes: %f\n", proporcaoGrande * 100);
}

void pesquisarCaoPorFaixaEtaria() {
    int idade_inferior, idade_superior;
    printf("Digite a faixa etaria desejada (anos): ");
    scanf("%d %d", &idade_inferior, &idade_superior);

    char data_atual[11];

    printf("Caes na faixa etaria %d-%d anos:\n", idade_inferior, idade_superior);

    for (int i = 0; i < num_caes; i++) {
//atoi converte a string "12345" para o valor inteiro 12345.
        int ano_nascimento = atoi(strtok(base_dados_caes[i].data_nascimento, "/"));
        int ano_atual = atoi(strtok(data_atual, "11/01/2024"));
//strtok modifica a string original. dividindo a string em partes.
        int idade = ano_atual - ano_nascimento;

        if (idade >= idade_inferior && idade <= idade_superior) {
            printf("Cao encontrado:\n");
            printf("ID: %d\n", base_dados_caes[i].id);
            printf("Nome: %s\n", base_dados_caes[i].nome);
            printf("Genero: %c\n", base_dados_caes[i].genero);
            printf("Peso: %.2f\n", base_dados_caes[i].peso);
            printf("Raca: %s\n", base_dados_caes[i].raca);
            printf("pelagem: %s\n", base_dados_caes[i].pelagem);
            printf("cor: %s", base_dados_caes[i].cor);
            printf("concelho: %s\n", base_dados_caes[i].concelho_nascimento);
            printf("pai: %d\n", base_dados_caes[i].pai);
            printf("mae: %d\n", base_dados_caes[i].mae);
            printf("data: %s\n", base_dados_caes[i].data_nascimento);
        }
    }
}

void extrairEstatisticas(Cao *baseDados, int tamanhoBase) {
    pesquisarCaoPorPorte(baseDados, tamanhoBase);
    pesquisarCaoPorFaixaEtaria(baseDados, tamanhoBase);
}

//A função verificarIntegridadeHistorico tem como objetivo verificar a integridade do histórico de eventos em relação à base de dados de cães.
void verificarIntegridadeHistorico() {
    printf("Verificando integridade do historico...\n");

    for (int i = 0; i < num_eventos; i++) {
        int id_cao = historico_caes[i].id_cao;
        int encontrado = 0;

        for (int j = 0; j < num_caes; j++) {
            if (base_dados_caes[j].id == id_cao) {
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("AVISO: ID %d no historico nao encontrado na base de dados.\n", id_cao);
            // Pode adotar medidas corretivas aqui, se necessário.
        }
    }

    printf("Verificacao concluida.\n");
}

void salvarDadosEmBinario() {
    //Abre dois arquivos binários (bd_caes.dat e historico_caes.dat) para escrita (wb).
    FILE *file_caes;
    file_caes = fopen("bd_caes.dat", "wb");
    FILE *file_eventos;
    file_eventos = fopen("historico_caes.dat", "wb");

    if (file_caes == NULL || file_eventos == NULL) {
        printf("Erro ao abrir arquivos binários para escrita.\n");
        return;
    }
//função fwrite para escrever no arquivo binário
    fwrite(&num_caes, sizeof(int), 1, file_caes);
    fwrite(base_dados_caes, sizeof(Cao), num_caes, file_caes);

    fwrite(&num_eventos, sizeof(int), 1, file_eventos);
    fwrite(historico_caes, sizeof(Evento), num_eventos, file_eventos);

    fclose(file_caes);
    fclose(file_eventos);
}

void carregarDadosEmBinario() {
    //Abre dois arquivos binários (bd_caes.dat e historico_caes.dat) para leitura (rb).
    FILE *file_caes;
    file_caes = fopen("bd_caes.dat", "rb");
    FILE *file_eventos;
    file_eventos = fopen("historico_caes.dat", "rb");

    if (file_caes == NULL || file_eventos == NULL) {
        printf("Arquivos binários não encontrados ou erro ao abrir.\n");
        return;
    }
//fread para ler do arquivo binário
    fread(&num_caes, sizeof(int), 1, file_caes);
    fread(base_dados_caes, sizeof(Cao), num_caes, file_caes);

    fread(&num_eventos, sizeof(int), 1, file_eventos);
    fread(historico_caes, sizeof(Evento), num_eventos, file_eventos);

    fclose(file_caes);
    fclose(file_eventos);
}

void salvarDadosEmTexto() {
    FILE *file_caes;
    file_caes = fopen("bd_caes.txt", "w");
    FILE *file_eventos;
    file_eventos = fopen("historico_caes.txt", "w");

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
    FILE *file_caes;
    file_caes = fopen("bd_caes.txt", "r");
    FILE *file_eventos;
    file_eventos = fopen("historico_caes.txt", "r");

    if (file_caes == NULL || file_eventos == NULL) {
        printf("Arquivos de texto não encontrados ou erro ao abrir.\n");
        return;
    }

    while (fscanf(file_caes, "%d %c %f %s %s %s %s %s %s %d %d",
                  &base_dados_caes[num_caes].id, &base_dados_caes[num_caes].genero,
                  &base_dados_caes[num_caes].peso, base_dados_caes[num_caes].raca,
                  base_dados_caes[num_caes].nome, base_dados_caes[num_caes].pelagem,
                  base_dados_caes[num_caes].cor, base_dados_caes[num_caes].data_nascimento,
                  base_dados_caes[num_caes].concelho_nascimento, &base_dados_caes[num_caes].pai,
                  &base_dados_caes[num_caes].mae) != EOF) {
        num_caes++;
    }//A sigla "EOF" significa "End of File"

    while (fscanf(file_eventos, "%s %d", historico_caes[num_eventos].tipo, &historico_caes[num_eventos].id_cao) != EOF) {
        num_eventos++;
    }

    fclose(file_caes);
    fclose(file_eventos);
}

void limparEstruturas() {
    num_caes = 0;
    num_eventos = 0;
    printf("Estruturas de dados limpas.\n");
}


