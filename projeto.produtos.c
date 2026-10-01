#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "acervo_livraria.csv"

typedef struct {
    char nome[100];
    char categoria[50];
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
        system("cls"); // limpa a tela (Windows)
        printf("===========================\n");
        printf("CONTROLE DE PRODUTOS\n");
        printf("===========================\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Buscar produto por nome\n");
        printf("4 - Buscar produtos por categoria\n");
        printf("5 - Buscar produtos por faixa de preÃ§os\n");
        printf("6 - Remover produto\n");
        printf("7 - Atualizar produto\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);

        switch(op) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            case 3: buscarPorNome(); break;
            case 4: buscarPorCategoria(); break;
            case 5: buscarPorPreco(); break;
            case 6: remover(); break;
            case 7: atualizar(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
        system("pause");
    } while(op != 0);

    return 0;
}

// ==========================
// Implementação das funções
// ==========================

void cadastrar() {
    Produto p;
    FILE *f = fopen(ARQUIVO, "a"); // abre em modo append (nâo apaga os existentes)
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("\n=== CADASTRAR PRODUTO ===\n");
    printf("Nome do produto: ");
    scanf(" %99[^\n]", p.nome);

    printf("Categoria: ");
    scanf(" %49[^\n]", p.categoria);

    printf("Preco: ");
    scanf("%f", &p.preco);

    printf("Quantidade em estoque: ");
    scanf("%d", &p.quantidade);

    printf("Codigo do produto: ");
    scanf("%d", &p.codigo);

    // grava no arquivo CSV
    fprintf(f, "%s;%s;%.2f;%d;%d\n", 
            p.nome, 
            p.categoria, 
            p.preco, 
            p.quantidade, 
            p.codigo);

    fclose(f);
    printf("Produto cadastrado com sucesso!\n");
}

void listar() {
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    Produto p;
    char linha[250];
    int contador = 0;

    printf("\n----- PRODUTOS CADASTRADOS -----\n");

    while (fgets(linha, sizeof(linha), f) != NULL) {
        // separa os campos usando strtok
        strcpy(p.nome, strtok(linha, ";"));
        strcpy(p.categoria, strtok(NULL, ";"));
        p.preco = atof(strtok(NULL, ";"));
        p.quantidade = atoi(strtok(NULL, ";"));
        p.codigo = atoi(strtok(NULL, ";\n"));

        contador++;
        printf("\nProduto %d\n", contador);
        printf("Nome: %s\n", p.nome);
        printf("Categoria: %s\n", p.categoria);
        printf("Preco: R$ %.2f\n", p.preco);
        printf("Quantidade: %d\n", p.quantidade);
        printf("Codigo: %d\n", p.codigo);
    }

    fclose(f);
}

void buscarPorNome() {
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("A agenda de produtos está vazia.\n");
        return;
    }

    Produto p;
    char linha[250];
    char nomeBusca[100];
    int encontrou = 0;

    printf("Digite o nome do produto que deseja buscar: ");
    scanf(" %99[^\n]", nomeBusca);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        // separa os campos
        strcpy(p.nome, strtok(linha, ";"));
        strcpy(p.categoria, strtok(NULL, ";"));
        p.preco = atof(strtok(NULL, ";"));
        p.quantidade = atoi(strtok(NULL, ";"));
        p.codigo = atoi(strtok(NULL, ";\n"));

        // compara strings
        if (strcmp(p.nome, nomeBusca) == 0) {
            encontrou = 1;
            printf("\nProduto encontrado!\n");
            printf("Nome: %s\n", p.nome);
            printf("Categoria: %s\n", p.categoria);
            printf("Preco: R$ %.2f\n", p.preco);
            printf("Quantidade: %d\n", p.quantidade);
            printf("Codigo: %d\n", p.codigo);
            break; // já¡ encontrou, pode parar
        }
    }

    fclose(f);

    if (!encontrou) {
        printf("Produto nao encontrado.\n");
    }
}

void buscarPorCategoria() {
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    Produto p;
    char linha[250];
    char categoriaBusca[50];
    int encontrou = 0;
    int contador = 0;

    printf("Digite a categoria que deseja buscar: ");
    scanf(" %49[^\n]", categoriaBusca);

    printf("\n--- PRODUTOS DA CATEGORIA: %s ---\n", categoriaBusca);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        // separa os campos
        strcpy(p.nome, strtok(linha, ";"));
        strcpy(p.categoria, strtok(NULL, ";"));
        p.preco = atof(strtok(NULL, ";"));
        p.quantidade = atoi(strtok(NULL, ";"));
        p.codigo = atoi(strtok(NULL, ";\n"));

        // compara categoria
        if (strcmp(p.categoria, categoriaBusca) == 0) {
            encontrou = 1;
            contador++;
            printf("\nProduto %d\n", contador);
            printf("Nome: %s\n", p.nome);
            printf("Categoria: %s\n", p.categoria);
            printf("Preco: R$ %.2f\n", p.preco);
            printf("Quantidade: %d\n", p.quantidade);
            printf("Codigo: %d\n", p.codigo);
        }
    }

    fclose(f);

    if (!encontrou) {
        printf("Nenhum produto encontrado nesta categoria.\n");
    }
}

void buscarPorPreco() {
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    Produto p;
    char linha[250];
    float precoMin, precoMax;
    int encontrou = 0;
    int contador = 0;

    printf("Digite o preco minimo: ");
    scanf("%f", &precoMin);

    printf("Digite o preco maximo: ");
    scanf("%f", &precoMax);

    printf("\n--- PRODUTOS NA FAIXA DE PRECO R$ %.2f a R$ %.2f ---\n", precoMin, precoMax);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        // separa os campos
        strcpy(p.nome, strtok(linha, ";"));
        strcpy(p.categoria, strtok(NULL, ";"));
        p.preco = atof(strtok(NULL, ";"));
        p.quantidade = atoi(strtok(NULL, ";"));
        p.codigo = atoi(strtok(NULL, ";\n"));

        // verifica se o preço está¡ dentro da faixa
        if (p.preco >= precoMin && p.preco <= precoMax) {
            encontrou = 1;
            contador++;
            printf("\nProduto %d\n", contador);
            printf("Nome: %s\n", p.nome);
            printf("Categoria: %s\n", p.categoria);
            printf("Preco: R$ %.2f\n", p.preco);
            printf("Quantidade: %d\n", p.quantidade);
            printf("Codigo: %d\n", p.codigo);
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
    char nomeBusca[100];
    int encontrou = 0;

    if (f == NULL) {
        printf("Nenhum produto cadastrado.\n");
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
        // separa os campos
        strcpy(p.nome, strtok(linha, ";"));
        strcpy(p.categoria, strtok(NULL, ";"));
        p.preco = atof(strtok(NULL, ";"));
        p.quantidade = atoi(strtok(NULL, ";"));
        p.codigo = atoi(strtok(NULL, ";\n"));

        // verifica se são o produto a remover
        if (strcmp(p.nome, nomeBusca) == 0) {
            encontrou = 1;
            // não escreve no arquivo temporÃ¡rio ? produto removido
        } else {
            fprintf(temp, "%s;%s;%.2f;%d;%d\n",
                    p.nome, p.categoria, p.preco, p.quantidade, p.codigo);
        }
    }

    fclose(f);
    fclose(temp);

    // substitui o arquivo original pelo temporário
    remove(ARQUIVO);
    rename("temp.csv", ARQUIVO);

    if (encontrou) {
        printf("Produto removido com sucesso!\n");
    } else {
        printf("Produto nao encontrado.\n");
    }
}

void atualizar() {
    FILE *f = fopen(ARQUIVO, "r");
    FILE *temp = fopen("temp.csv", "w");

    Produto p;
    char linha[250];
    char nomeBusca[100];
    int encontrou = 0;

    if (f == NULL) {
        printf("Nenhum produto cadastrado.\n");
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
        // separa os campos
        strcpy(p.nome, strtok(linha, ";"));
        strcpy(p.categoria, strtok(NULL, ";"));
        p.preco = atof(strtok(NULL, ";"));
        p.quantidade = atoi(strtok(NULL, ";"));
        p.codigo = atoi(strtok(NULL, ";\n"));

        if (strcmp(p.nome, nomeBusca) == 0) {
            encontrou = 1;

            printf("\nProduto encontrado! Informe os novos dados:\n");
            printf("Novo nome: ");
            scanf(" %99[^\n]", p.nome);

            printf("Nova categoria: ");
            scanf(" %49[^\n]", p.categoria);

            printf("Novo preco: ");
            scanf("%f", &p.preco);

            printf("Nova quantidade: ");
            scanf("%d", &p.quantidade);

            printf("Novo codigo: ");
            scanf("%d", &p.codigo);
        }

        // grava no arquivo temporário (se atualizado, grava os novos dados)
        fprintf(temp, "%s;%s;%.2f;%d;%d\n",
                p.nome, p.categoria, p.preco, p.quantidade, p.codigo);
    }

    fclose(f);
    fclose(temp);

    // substitui o arquivo original pelo temporário
    remove(ARQUIVO);
    rename("temp.csv", ARQUIVO);

    if (encontrou) {
        printf("Produto atualizado com sucesso!\n");
    } else {
        printf("Produto nao encontrado.\n");
    }
}
