#include <stdio.h>
#include <string.h>

// STRUCTS
typedef struct {
	int codigo, quartosTotais, quartosDisponiveis;
	char nome[100], cidade[50];
	float diaria;
} Hotel;

typedef struct {
    char nome[50], data[11], nomeHotel[100];
    int codigoHotel;
    float diariaHotel;
} Reserva;


// GLOBAL VARIABLES
FILE *arquivo_hoteis, *arquivo_reservas;
Hotel hotel;
Reserva reserva;

// FUNCTIONS
void cadastra_Hotel() {
	printf("\n");

	printf("Codigo: ");
	scanf("%i", &hotel.codigo);
	while(getchar() != '\n');

	printf("Nome: ");
	gets(hotel.nome);

	printf("Cidade: ");
	gets(hotel.cidade);

	printf("Total de quartos: ");
	scanf("%i", &hotel.quartosTotais);
	while(getchar() != '\n');

	printf("Quartos disponiveis: ");
	scanf("%i", &hotel.quartosDisponiveis);
	while(getchar() != '\n');

	printf("Valor da diaria: ");
	scanf("%f", &hotel.diaria);
	while(getchar() != '\n');

	printf("Hotel %s cadastrado!\n", hotel.nome);
	
	// Salva dados em hoteis.txt 
	arquivo_hoteis = fopen("hoteis.txt", "a");
	if(arquivo_hoteis == NULL) {
		printf("Erro no arquivo!");
		return;
	} else {
		fprintf(arquivo_hoteis, "%i\t%s\t%s\t%i\t%i\t%.2f\n",
		        hotel.codigo,
		        hotel.nome,
		        hotel.cidade,
		        hotel.quartosTotais,
		        hotel.quartosDisponiveis,
		        hotel.diaria);
		fclose(arquivo_hoteis);
	}
}

void reserva_hotel() {
	Hotel tempH;
	Reserva tempR;

	printf("\n");
	printf("Insira seu nome: ");
	gets(reserva.nome);
	
	printf("\n");
	printf("Insira a data da reserva: ");
	gets(reserva.data);

	printf("Insira o codigo do hotel: ");
	scanf("%i", &reserva.codigoHotel);
	while(getchar() != '\n');

    // Busca hotel
    FILE *tempFile = fopen("temp.txt", "w");
    
    arquivo_hoteis = fopen("hoteis.txt", "r");
    while(fscanf(arquivo_hoteis, "%i", tempH.codigo) == 1 &&
        fscanf(arquivo_hoteis, "%s", tempH.nome) == 1 &&
        fscanf(arquivo_hoteis, "%s", tempH.cidade) == 1 &&
        fscanf(arquivo_hoteis, "%i", tempH.quartosTotais) == 1 &&
        fscanf(arquivo_hoteis, "%i", tempH.quartosDisponiveis) == 1 &&
        fscanf(arquivo_hoteis, "%f", tempH.diaria) == 1) {
        if(reserva.codigoHotel == tempH.codigo) {
            break;
        } else {
			printf("Hotel nao encontrado!");
			break;
		}
	}
	
	// Salva reserva
	arquivo_reservas = fopen("reservas.txt", "w");
	if(arquivo_reservas == NULL) {
		printf("Erro no arquivo!");
		return;
	} else {
		fprintf(arquivo_reservas, "%s\t%s\t%i\t%s\t%.2f\n",
		        reserva.nome,
		        reserva.data,
		        tempH.codigo,
		        tempH.nome,
		        tempH.diaria);
		        
		fclose(arquivo_reservas);
	}
}

int main()
{
	int menu;

	do {
		printf("\nMENU\n");
		printf("0- Sair\n");
		printf("1- Cadastrar hotel\n");
		printf("2- Buscar hotel\n");
		printf("3- Fazer uma reserva\n");
		printf("4- Gerar relatorio de reservas\n");
		printf("Escolha uma opcao: ");
		scanf("%i", &menu);
		while(getchar() != '\n');

		switch(menu) {
		case 0:
			printf("Programa encerrado!");
			break;
		case 1:
			cadastra_Hotel();
			break;
		case 2:
      printf("Ainda nao implementado!\n");
			break;
		case 3:
		    reserva_hotel();
			break;
		case 4:
      printf("Ainda nao implementado!\n");
			break;
		default:
			printf("Número inválido!\n");
			break;
		}
	} while(menu !=0);

	return 0;
}
