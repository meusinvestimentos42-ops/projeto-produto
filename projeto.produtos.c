#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nome do arquivo e constantes do sistema
#define ARQUIVO "acervo_livraria.csv"
#define TAM_NOME 100
#define TAM_CAT 50

typedef struct {
    char nome[TAM_NOME];
    char categoria[TAM_CAT];
    float preco;
    int quantidade;
    int codigo;
} Produto;

// Declaração das funções
void cadastrar();
void listar();
void buscarPorNome();
void buscarPorCategoria();
void buscarPorPreco();
void remover();
void atualizar();

int main() {
    int op;
    do {
        system("cls"); // limpa a tela (Windows), Se estiver no Linux/Mac, utilize system("clear")
        printf("===================================\n");
        printf("   LIVRARIA - CONTROLE DE ACERVO   \n");
        printf("===================================\n");
        printf("1 - Cadastrar produto/item\n");
        printf("2 - Listar acervo completo\n");
        printf("3 - Buscar produto por nome\n");
        printf("4 - Buscar produtos por categoria/genero\n");
        printf("5 - Buscar produtos por faixa de preco\n");
        printf("6 - Remover produto do acervo\n");
        printf("7 - Atualizar dados do produto\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &op) != 1) {
            while (getchar() != '\n'); // Limpa entrada invalida
            op = -1;
        }

        switch(op) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            case 3: buscarPorNome(); break;
            case 4: buscarPorCategoria(); break;
            case 5: buscarPorPreco(); break;
            case 6: remover(); break;
            case 7: atualizar(); break;
            case 0: printf("\nSaindo do sistema da livraria...\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
        system("pause");
    } while(op != 0);

    return 0;
}

// ==========================================
// Implementações das Funções Padronizadas
// ==========================================

void cadastrar() {
    Produto p;
    FILE *f = fopen(ARQUIVO, "a");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo do acervo!\n");
        return;
    }

    printf("\n=== CADASTRAR PRODUTO/ITEM ===\n");
    printf("Nome do produto (Livro, Item de Papelaria, etc.): ");
    scanf(" %99[^\n]", p.nome);

    printf("Categoria/Genero (ex: Ficcao, Papelaria, Tecnico): ");
    scanf(" %49[^\n]", p.categoria);

    // Validação de preço não negativo
    do {
        printf("Preco: R$ ");
        scanf("%f", &p.preco);
        if (p.preco < 0) {
            printf("Erro: O preco nao pode ser negativo! Tente novamente.\n");
        }
    } while (p.preco < 0);

    // Validação de quantidade não negativa
    do {
        printf("Quantidade em estoque: ");
        scanf("%d", &p.quantidade);
        if (p.quantidade < 0) {
            printf("Erro: A quantidade nao pode ser negativa! Tente novamente.\n");
        }
    } while (p.quantidade < 0);

    printf("Codigo do produto/ISBN: ");
    scanf("%d", &p.codigo);

    // Grava no arquivo CSV
    fprintf(f, "%s;%s;%.2f;%d;%d\n", p.nome, p.categoria, p.preco, p.quantidade, p.codigo);
    fclose(f);

    printf("Produto/Item cadastrado com sucesso no acervo!\n");
}

void listar() {
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Nenhum produto cadastrado no acervo.\n");
        return;
    }

    Produto p;
    char linha[250];
    int contador = 0;

    printf("\n----- PRODUTOS CADASTRADOS NO ACERVO -----\n");

    while (fgets(linha, sizeof(linha), f) != NULL) {
        char *token;

        token = strtok(linha, ";");
        if (token != NULL) strcpy(p.nome, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(p.categoria, token);

        token = strtok(NULL, ";");
        if (token != NULL) p.preco = atof(token);

        token = strtok(NULL, ";");
        if (token != NULL) p.quantidade = atoi(token);

        token = strtok(NULL, ";\n");
        if (token != NULL) p.codigo = atoi(token);

        contador++;
        printf("\nItem %d\n", contador);
        printf("Nome: %s\n", p.nome);
        printf("Categoria/Genero: %s\n", p.categoria);
        printf("Preco: R$ %.2f\n", p.preco);
        printf("Quantidade em Estoque: %d\n", p.quantidade);
        printf("Codigo/ISBN: %d\n", p.codigo);
    }

    if (contador == 0) {
        printf("Nenhum produto encontrado no arquivo.\n");
    }

    fclose(f);
}

void buscarPorNome() {
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Nenhum produto cadastrado no acervo.\n");
        return;
    }

    Produto p;
    char linha[250];
    char nomeBusca[TAM_NOME];
    int encontrou = 0;

    printf("Digite o nome do produto que deseja buscar: ");
    scanf(" %99[^\n]", nomeBusca);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        char *token;

        token = strtok(linha, ";");
        if (token != NULL) strcpy(p.nome, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(p.categoria, token);

        token = strtok(NULL, ";");
        if (token != NULL) p.preco = atof(token);

        token = strtok(NULL, ";");
        if (token != NULL) p.quantidade = atoi(token);

        token = strtok(NULL, ";\n");
        if (token != NULL) p.codigo = atoi(token);

        if (strcmp(p.nome, nomeBusca) == 0) {
            encontrou = 1;
            printf("\nProduto encontrado!\n");
            printf("Nome: %s\n", p.nome);
            printf("Categoria/Genero: %s\n", p.categoria);
            printf("Preco: R$ %.2f\n", p.preco);
            printf("Quantidade em Estoque: %d\n", p.quantidade);
            printf("Codigo/ISBN: %d\n", p.codigo);
            break;
        }
    }

    fclose(f);

    if (!encontrou) {
        printf("Produto nao encontrado no acervo.\n");
    }
}

void buscarPorCategoria() {
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Nenhum produto cadastrado no acervo.\n");
        return;
    }

    Produto p;
    char linha[250];
    char categoriaBusca[TAM_CAT];
    int encontrou = 0;

    printf("Digite a categoria/genero que deseja buscar: ");
    scanf(" %49[^\n]", categoriaBusca);

    printf("\n--- PRODUTOS NA CATEGORIA/GENERO: %s ---\n", categoriaBusca);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        char *token;

        token = strtok(linha, ";");
        if (token != NULL) strcpy(p.nome, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(p.categoria, token);

        token = strtok(NULL, ";");
        if (token != NULL) p.preco = atof(token);

        token = strtok(NULL, ";");
        if (token != NULL) p.quantidade = atoi(token);

        token = strtok(NULL, ";\n");
        if (token != NULL) p.codigo = atoi(token);

        if (strcmp(p.categoria, categoriaBusca) == 0) {
            encontrou = 1;
            printf("%s - R$ %.2f (Estoque: %d)\n", p.nome, p.preco, p.quantidade);
        }
    }

    fclose(f);

    if (!encontrou) {
        printf("Nenhum produto encontrado nesta categoria/genero.\n");
    }
}

void buscarPorPreco() {
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Nenhum produto cadastrado no acervo.\n");
        return;
    }

    Produto p;
    char linha[250];
    float precoMin, precoMax;
    int encontrou = 0;

    do {
        printf("Preco minimo: R$ ");
        scanf("%f", &precoMin);
        printf("Preco maximo: R$ ");
        scanf("%f", &precoMax);

        if (precoMin < 0 || precoMax < 0) {
            printf("Erro: Os precos nao podem ser negativos!\n\n");
        } else if (precoMin > precoMax) {
            printf("Erro: O preco minimo nao pode ser maior que o preco maximo!\n\n");
        }
    } while (precoMin < 0 || precoMax < 0 || precoMin > precoMax);

    printf("\n--- PRODUTOS NA FAIXA DE R$ %.2f A R$ %.2f ---\n", precoMin, precoMax);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        char *token;

        token = strtok(linha, ";");
        if (token != NULL) strcpy(p.nome, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(p.categoria, token);

        token = strtok(NULL, ";");
        if (token != NULL) p.preco = atof(token);

        token = strtok(NULL, ";");
        if (token != NULL) p.quantidade = atoi(token);

        token = strtok(NULL, ";\n");
        if (token != NULL) p.codigo = atoi(token);

        if (p.preco >= precoMin && p.preco <= precoMax) {
            encontrou = 1;
            printf("%s - R$ %.2f\n", p.nome, p.preco);
        }
    }

    fclose(f);

    if (!encontrou) {
        printf("Nenhum produto encontrado nesta faixa de preco.\n");
    }
}

void remover() {
    FILE *f = fopen(ARQUIVO, "r");
    FILE *temp = fopen("temp.csv", "w");

    Produto p;
    char linha[250];
    char copia[250];
    char nomeBusca[TAM_NOME];
    int encontrou = 0;

    if (f == NULL) {
        printf("Nenhum produto cadastrado no acervo.\n");
        if (temp) fclose(temp);
        return;
    }

    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(f);
        return;
    }

    printf("Digite o nome do produto que deseja remover: ");
    scanf(" %99[^\n]", nomeBusca);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        strcpy(copia, linha);

        char *token = strtok(copia, ";");
        if (token != NULL) strcpy(p.nome, token);

        if (strcmp(p.nome, nomeBusca) == 0) {
            encontrou = 1;
        } else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.csv", ARQUIVO);

    if (encontrou) {
        printf("Produto/Item removido do acervo com sucesso!\n");
    } else {
        printf("Produto nao encontrado.\n");
    }
}

void atualizar() {
    FILE *f = fopen(ARQUIVO, "r");
    FILE *temp = fopen("temp.csv", "w");

    Produto p;
    char linha[250];
    char copia[250];
    char nomeBusca[TAM_NOME];
    int encontrou = 0;

    if (f == NULL) {
        printf("Nenhum produto cadastrado no acervo.\n");
        if (temp) fclose(temp);
        return;
    }

    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(f);
        return;
    }

    printf("Digite o nome do produto que deseja atualizar: ");
    scanf(" %99[^\n]", nomeBusca);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        strcpy(copia, linha);

        char *token;
        token = strtok(copia, ";");
        if (token != NULL) strcpy(p.nome, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(p.categoria, token);

        token = strtok(NULL, ";");
        if (token != NULL) p.preco = atof(token);

        token = strtok(NULL, ";");
        if (token != NULL) p.quantidade = atoi(token);

        token = strtok(NULL, ";\n");
        if (token != NULL) p.codigo = atoi(token);

        if (strcmp(p.nome, nomeBusca) == 0) {
            encontrou = 1;

            printf("\nProduto encontrado! Digite os novos dados:\n");
            printf("Novo nome: ");
            scanf(" %99[^\n]", p.nome);

            printf("Nova categoria/genero: ");
            scanf(" %49[^\n]", p.categoria);

            do {
                printf("Novo preco: R$ ");
                scanf("%f", &p.preco);
                if (p.preco < 0) {
                    printf("Erro: O preco nao pode ser negativo!\n");
                }
            } while (p.preco < 0);

            do {
                printf("Nova quantidade: ");
                scanf("%d", &p.quantidade);
                if (p.quantidade < 0) {
                    printf("Erro: A quantidade nao pode ser negativa!\n");
                }
            } while (p.quantidade < 0);

            printf("Novo codigo/ISBN: ");
            scanf("%d", &p.codigo);

            fprintf(temp, "%s;%s;%.2f;%d;%d\n", p.nome, p.categoria, p.preco, p.quantidade, p.codigo);
        } else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.csv", ARQUIVO);

    if (encontrou) {
        printf("Produto atualizado no acervo com sucesso!\n");
    } else {
        printf("Produto nao encontrado.\n");
    }
}
