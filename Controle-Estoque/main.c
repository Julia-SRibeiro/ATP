#include <stdio.h>
#include <string.h>

// STRUCTS
typedef struct {
    char nome[50], codigo[10];
    int estoque;
    float preco;
} Produtos;


// GLOBAL VARIABLES
FILE *arquivo;
Produtos produto;


// FUNCTIONS
void cadastra_produto() {
    getchar();
  
    printf("Codigo do produto: ");
    gets(produto.codigo);  
    
    printf("Nome: ");
    gets(produto.nome);
    
    printf("Quantidade em estoque: ");
    scanf("%i", &produto.estoque);
    
    printf("Preco unitario: ");
    scanf("%f", &produto.preco);
}

void salva_dados() {
    arquivo = fopen("estoque.txt", "a");
    if(arquivo == NULL) {
        printf("Erro no arquivo!\n");
    } else {
        fprintf(arquivo, "%s    ", produto.codigo);
        fprintf(arquivo, "%s    ", produto.nome);
        fprintf(arquivo, "%i    ", produto.estoque);
        fprintf(arquivo, "%.2f\n", produto.preco);
        
        fclose(arquivo);
    }
}

void conta_produtos() {
    int nProdutos=0;
    
    arquivo = fopen("estoque.txt", "r");
    if(arquivo == NULL) {
        printf("Erro no arquivo!\n");
    } else {
        Produtos temp;
        while (fscanf(arquivo, "%s", temp.codigo) == 1 &&
        fscanf(arquivo, "%s", temp.nome) == 1 &&
        fscanf(arquivo, "%i", &temp.estoque) == 1 &&
        fscanf(arquivo, "%f", &temp.preco) == 1) 
        {
            nProdutos++;
        }
        fclose(arquivo);
        
        printf("Nº de produtos: %i\n", nProdutos);
    }
}

void mostra_dados() {
    arquivo = fopen("estoque.txt", "r");
    if(arquivo == NULL) {
        printf("Erro no arquivo!\n");
    } else {
        Produtos temp;
        
        while (fscanf(arquivo, "%s", temp.codigo) == 1 &&
        fscanf(arquivo, "%s", temp.nome) == 1 &&
        fscanf(arquivo, "%i", &temp.estoque) == 1 &&
        fscanf(arquivo, "%f", &temp.preco) == 1) 
        {
            printf("\n");
            printf("Codigo: %s\n", temp.codigo);
            printf("Nome: %s\n", temp.nome);
            printf("Quantidade em estoque: %i\n", temp.estoque);
            printf("Preco unitario: R$%.2f\n", temp.preco);
        }
        
        fclose(arquivo);
    }

}

void busca_codigo() {
    arquivo = fopen("estoque.txt", "r");
    if(arquivo == NULL) {
        printf("Erro no arquivo!\n");
    } else {
        Produtos temp;
        char codigo[10];
        int i=0;
        
        getchar();
        printf("Codigo: ");
        gets(codigo);
        
        while (fscanf(arquivo, "%s", temp.codigo) == 1 &&
        fscanf(arquivo, "%s", temp.nome) == 1 &&
        fscanf(arquivo, "%i", &temp.estoque) == 1 &&
        fscanf(arquivo, "%f", &temp.preco) == 1) 
        {
            if((strcmp(codigo, temp.codigo)) == 0) {
                printf("Nome: %s\n", temp.nome);
                printf("Quantidade em estoque: %i\n", temp.estoque);
                printf("Preco unitario: R$%.2f\n", temp.preco);
                
                i ++;
            }
        }
        
        fclose(arquivo);
        
        if(i == 0) {
            printf("Codigo nao encontrado!\n");
        }
    }
}

void valor_estoque() {
    float valor=0;
    arquivo = fopen("estoque.txt", "r");
    
    if(arquivo == NULL) {
        printf("Erro no arquivo!\n");
    } else {
        Produtos temp;
        while (fscanf(arquivo, "%s", temp.codigo) == 1 &&
        fscanf(arquivo, "%s", temp.nome) == 1 &&
        fscanf(arquivo, "%i", &temp.estoque) == 1 &&
        fscanf(arquivo, "%f", &temp.preco) == 1) 
        {
            valor+= temp.estoque * temp.preco;
        }
        
        fclose(arquivo);
        
        printf("Valor total em estoque: R$ %.2f\n", valor);
    }
}


// MAIN
int main()
{
    int menu;
    
    do {
        printf("\nMENU\n");
        printf("0- Sair\n");
        printf("1- Adicionar produto\n");
        printf("2- Mostrar estoque\n");
        printf("3- Buscar produto por codigo\n");
        printf("4- Calcular valor total em estoque\n");
        printf("Escolha uma opção: ");
        scanf("%i", &menu);
        printf("\n");
        
        switch (menu) {
            case 0:
            printf("Programa encerrado");
                break;
            case 1:
                cadastra_produto();
                salva_dados();
                break;
            case 2:
                conta_produtos();
                mostra_dados();
                break;
            case 3:
                busca_codigo();
                break;
            case 4:
                valor_estoque();
                break;
            default:
                printf("Numero invalido!\n");
        }
        
    } while (menu != 0);
    
    return 0;
}
