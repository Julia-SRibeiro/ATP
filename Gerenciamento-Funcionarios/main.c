#include <stdio.h>
#include <stdlib.h>

// STRUCTS
typedef struct {
    int id;
    char nome[100], cargo[50];
    float salario;
 } Funcionario;

// GLOBAL VARIABLES
FILE *arquivo;
Funcionario funcionario;

// FUNCTIONS
void cadastra_funcionario() {
    // Tratar digitação inválida
    
    // Verificar se já existe
    printf("Código do funcionário: ");
    scanf("%i", &funcionario.id);
    while(getchar() != '\n');
    
    printf("Nome completo: ");
    gets(funcionario.nome);
    
    printf("Cargo: ");
    gets(funcionario.cargo);
    
    printf("Salário mensal: ");
    scanf("%f", &funcionario.salario);
    while(getchar() != '\n');
}
void salva_dados() {
    arquivo = fopen("funcionarios.bin", "ab");
    if(arquivo == NULL) {
        printf("Erro no arquivo!");
        return;
    } else {
        fwrite(&funcionario, sizeof(Funcionario), 1, arquivo);
        fclose(arquivo);
    }
}

void conta_funcionario() {
    int nFuncionarios=0;
    
    arquivo = fopen("funcionarios.bin", "rb");
    if(arquivo == NULL) {
        printf("Erro no arquivo!");
        return;
    } else {
        Funcionario temp;
        while(fread(&temp, sizeof(Funcionario), 1, arquivo) == 1) {
            nFuncionarios++;
        }
        fclose(arquivo);
        
        printf("Nº de funcionários: %i\n", nFuncionarios);
    }
}
void mostra_dados() {
    arquivo = fopen("funcionarios.bin", "rb");
    if(arquivo == NULL) {
        printf("Erro no arquivo!");
        return;
    } else {
        Funcionario temp;
        printf("ID\tNome\tCargo\tSalário\n");
        
        while (fread(&temp, sizeof(Funcionario), 1, arquivo) == 1) {
            printf("%i\t%s\t%s\tR$%.2f\n", temp.id, temp.nome, temp.cargo, temp.salario);
        }
        fclose(arquivo);
    }
}

void busca_id() {
    arquivo = fopen("funcionarios.bin", "rb");
    if(arquivo == NULL) {
        printf("Erro no arquivo!");
        return;
    } else {
        Funcionario temp;
        int i=0, id;
        
        printf("ID: ");
        scanf("%i", &id);
        while(getchar() != '\n');

        while (fread(&temp, sizeof(Funcionario), 1, arquivo) == 1) {
            if(id == temp.id) {
                printf("%i\t%s\t%s\tR$%.2f\n", temp.id, temp.nome, temp.cargo, temp.salario);
                i++;
            }
        }
        
        fclose(arquivo);
        
        if(i == 0) {
            printf("ID nao encontrado!\n");
        }
    }
}

void altera_dados() {
    arquivo = fopen("funcionarios.bin", "r+b");
    
    if(arquivo == NULL) {
        printf("Erro no arquivo!\n");
        return;
    }

    int id, encontrou = 0;
    Funcionario temp;

    printf("\nDigite o ID do funcionário para alterar: ");
    scanf("%i", &id);
    while(getchar() != '\n');

    while(fread(&temp, sizeof(Funcionario), 1, arquivo) == 1) {
        if(temp.id == id) {
            encontrou = 1;
            printf("Dados atuais:\n");
            printf("%i\t%s\t%s\tR$%.2f\n", temp.id, temp.nome, temp.cargo, temp.salario);
            printf("Insira os dados novos:\n");
            
            printf("Novo Nome: ");
            gets(temp.nome);
            
            printf("Novo Cargo: ");
            gets(temp.cargo);
            
            printf("Novo Salário: ");
            scanf("%f", &temp.salario);
            while(getchar() != '\n');

            // Volta o ponteiro do arquivo para o início deste registro
            // fseek(arquivo, -tamanho_do_struct, SEEK_CUR_(posição atual))
            fseek(arquivo, -sizeof(Funcionario), SEEK_CUR);
            
            // Sobrescreve os dados
            fwrite(&temp, sizeof(Funcionario), 1, arquivo);
            printf("Dados atualizados com sucesso!\n");
            break;
        }
    }

    if(!encontrou) printf("ID não encontrado.\n");
    fclose(arquivo);
}

void remove_funcionario() {
    arquivo = fopen("funcionarios.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");
    
    if(arquivo == NULL || temp == NULL) {
        printf("Erro ao manipular arquivos!\n");
        if (arquivo) fclose(arquivo);
        if (temp) fclose(temp);
        return;
    }

    int id, encontrou = 0;
    Funcionario func;

    printf("\nID: ");
    scanf("%i", &id);
    while(getchar() != '\n');

    // Copia todos os registros PARA o temp, MENOS o que sera deletado
    while(fread(&func, sizeof(Funcionario), 1, arquivo) == 1) {
        if(func.id == id) {
            encontrou = 1; // NÃO escreve no temp
        } else {
            fwrite(&func, sizeof(Funcionario), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if(encontrou) {
        remove("funcionarios.bin"); // Deleta o original
        rename("temp.bin", "funcionarios.bin"); // Renomeia o temp para o nome original
        printf("Funcionário removido!\n");
    } else {
        remove("temp.bin"); // Se não achou nada, apaga o temp
        printf("ID não encontrado.\n");
    }
}

int main()
{
    int menu;
    
    do {printf("\nMENU\n");
        printf("0- Sair\n");
        printf("1- Cadastrar novo funcionario\n");
        printf("2- Listar todos os funcionarios\n");
        printf("3- Buscar funcionário por ID\n");
        printf("4- Alterar dados de um funcionario\n");
        printf("5- Remover funcionario\n");
        printf("Escolha uma opcao: ");
        scanf("%i", &menu);
        while(getchar() != '\n');
        printf("\n");
        
        switch (menu) {
            case 0:
                printf("Programa encerrado");
                break;
            case 1:
                cadastra_funcionario();
                salva_dados();
                break;
            case 2:
                conta_funcionario();
                mostra_dados();
                break;
            case 3:
                busca_id();
                break;
            case 4:
                altera_dados();
                break;
            case 5:
                remove_funcionario();
                break;
            default:
                printf("Numero invalido!\n");
        }
    } while(menu !=0);

    return 0;
}
