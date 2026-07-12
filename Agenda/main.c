#include <stdio.h>
#include <string.h>

//Structs
typedef struct
{
    int ddd;
    long numero;
} tipo_telefone;

typedef struct
{
    char pais[50], estado[3], cidade[50], bairro[50], rua[50], complemento[100];
    int numero;
    long cep;
} tipo_endereco;

typedef struct
{
    int dia, mes, ano;
} data_nascimento;

typedef struct
{
    char nome[20], email[50], observacao[100];
    tipo_telefone telefone;
    tipo_endereco endereco;
    data_nascimento nascimento;
} agenda;


//Variáveis Globais
agenda pessoa[100];
int nPessoa = 0, menu, i, agendaCompleta=0;


//Funções
void ordena_pessoas() {
    agenda temp;
    int x, y;

    for(x = 0; x < nPessoa - 1; x++) {
        for (y = x + 1; y < nPessoa; y++) {
            if (strcmp(pessoa[x].nome, pessoa[y].nome) > 0) {
                temp = pessoa[x];
                pessoa[x] = pessoa[y];
                pessoa[y] = temp;
            }
        }
    }
}
void insere_pessoa() {
    if (nPessoa < 100) {
        getchar();
        printf("Nome: ");
        gets(pessoa[nPessoa].nome);
        printf("E-mail: ");
        gets(pessoa[nPessoa].email);
        printf("\n");
        
        printf("TELEFONE\n");
        printf("DDD: ");
        scanf("%i", &pessoa[nPessoa].telefone.ddd);
        printf("Número: ");
        scanf("%ld", &pessoa[nPessoa].telefone.numero);
        printf("\n");
        
        printf("ENDEREÇO\n");
        getchar();
        printf("País: ");
        gets(pessoa[nPessoa].endereco.pais);
        printf("Estado(sigla): ");
        gets(pessoa[nPessoa].endereco.estado);
        printf("Cidade: ");
        gets(pessoa[nPessoa].endereco.cidade);
        printf("CEP: ");
        scanf("%ld", &pessoa[nPessoa].endereco.cep);
        getchar();
        printf("Bairro: ");
        gets(pessoa[nPessoa].endereco.bairro);
        printf("Rua: ");
        gets(pessoa[nPessoa].endereco.rua);
        printf("Número: ");
        scanf("%i", &pessoa[nPessoa].endereco.numero);
        getchar();
        printf("Complemento: ");
        gets(pessoa[nPessoa].endereco.complemento);
        printf("\n");
        
        printf("DATA DE NASCIMENTO\n");
        printf("Dia: ");
        scanf("%i", &pessoa[nPessoa].nascimento.dia);
        printf("Mês: ");
        scanf("%i", &pessoa[nPessoa].nascimento.mes);
        printf("Ano: ");
        scanf("%i", &pessoa[nPessoa].nascimento.ano);
        getchar();
        printf("\n");
        
        printf("Observação: ");
        gets(pessoa[nPessoa].observacao);
        printf("\n");
        
        nPessoa++;
        
        ordena_pessoas();
    } else {
        printf("Agenda cheia!\n");
        printf("\n");
    }
}

void mostra_agenda() {
    printf("PESSOA %i \n", i+1);
    printf("Nome: %s \n", pessoa[i].nome);
    printf("Telefone: (%i) %ld \n", pessoa[i].telefone.ddd, pessoa[i].telefone.numero);
    printf("E-mail: %s \n", pessoa[i].email);
    if(agendaCompleta == 1) {
        printf("Endereço: Rua %s, %i, %s, %s - %ld, %s, %s, %s \n", 
            pessoa[i].endereco.rua,
            pessoa[i].endereco.numero,
            pessoa[i].endereco.complemento,
            pessoa[i].endereco.bairro,
            pessoa[i].endereco.cep,
            pessoa[i].endereco.cidade,
            pessoa[i].endereco.estado,
            pessoa[i].endereco.pais);
        
        printf("Data de nascimento: %i/%i/%i \n", 
            pessoa[i].nascimento.dia,
            pessoa[i].nascimento.mes,
            pessoa[i].nascimento.ano);
        
        printf("Observação: %s \n", pessoa[i].observacao);
    }
    printf("\n");
}
void menu_agenda() {
    printf("MENU\n");
    printf("1- Mostrar nome, telefone e e-mail\n");
    printf("2- Mostrar todos os dados\n");
    printf("Insira uma opção: ");
    scanf("%i", &menu);
    
    switch(menu) {
        case 1:
            printf("Número de contatos: %i \n", nPessoa);
            printf("\n");
            for(i=0; i < nPessoa; i++) {
                mostra_agenda();
            }
            break;
        case 2:
            agendaCompleta = 1;
            printf("Número de contatos: %i \n", nPessoa);
            printf("\n");
            for(i=0; i < nPessoa; i++) {
                mostra_agenda();
            }
            agendaCompleta = 0;
            break;
        default:
            printf("Número inválido!\n");
            break;
    }
}

void busca_nome() {
    char nome[50];
    int x=0;
    
    printf("Nome cadastrado: ");
    getchar();
    gets(nome);
    printf("\n");
    
    for(i=0; i < nPessoa; i++) {
        if(strcmp(nome, pessoa[i].nome) == 0) {
            mostra_agenda();
            x = 1;
        }
    }
    
    if (x != 1) {
        printf("Pessoa não encontrada!\n");
    }
}

void busca_mes_aniversario() {
    int mes, x=0;
    
    printf("Mês de aniversário: ");
    scanf("%i", &mes);
    printf("\n");
    
    for(i=0; i < nPessoa; i++) {
        if(mes == pessoa[i].nascimento.mes) {
            mostra_agenda();
            x = 1;
        }
    }
    if (x != 1) {
        printf("Nenhum aniversário nesse mês\n");
    }
}
void busca_dia_mes_aniversario() {
    int dia, mes, x=0;
    
    printf("Mês de aniversário: ");
    scanf("%i", &mes);
    printf("Dia de aniversário: ");
    scanf("%i", &dia);
    printf("\n");
    
    for(i=0; i < nPessoa; i++) {
        if(mes == pessoa[i].nascimento.mes && dia == pessoa[i].nascimento.dia) {
            mostra_agenda();
            x = 1;
        }
    }
    if (x != 1) {
        printf("Nenhum aniversário nesse dia e mês\n");
    }
}
void busca_aniversario() {
    printf("MENU\n");
    printf("1- Mês\n");
    printf("2- Dia e mês\n");
    printf("Insira uma opção: ");
    scanf("%i", &menu);
    printf("\n");
    
    switch(menu) {
        case 1:
            busca_mes_aniversario();
            break;
        case 2:
            busca_dia_mes_aniversario();
            break;
        default:
            printf("Número inválido!\n");
    }
}

void remove_pessoa() {
    char nome[50];
    int x=0, j;
    
    printf("Nome cadastrado: ");
    getchar();
    gets(nome);
    
    for(i=0; i < nPessoa; i++) {
        if(strcmp(nome, pessoa[i].nome) == 0) {
            for(j = i; j < nPessoa - 1; j++) {
                pessoa[j] = pessoa[j + 1];
            }
            nPessoa--;
            x = 1;
        }
    }
    
    if (x == 1) {
        printf("Pessoa removida!\n");
    } else {
        printf("Pessoa não encontrada!\n");
    }
}


//Main
int main()
{
    do {
        printf("\nMENU\n");
        printf("1- Inserir pessoa\n");
        printf("2- Mostrar agenda\n");
        printf("3- Busca por nome\n");
        printf("4- Busca por aniversário\n");
        printf("5- Remover pessoa\n");
        printf("6- Sair\n");
        printf("Insira uma opção: ");
        scanf("%i", &menu);
        printf("\n");
        
        switch(menu) {
            case 1:
                insere_pessoa();
                break;
            case 2:
                menu_agenda();
                break;
            case 3:
                busca_nome();
                break;
            case 4:
                busca_aniversario();
                break;
            case 5:
                remove_pessoa();
                break;
            case 6:
                break;
            default:
                printf("Número inválido\n");
        }
    } while (menu != 6);
    return 0;
}
