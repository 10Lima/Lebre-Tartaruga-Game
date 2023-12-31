// Lebre e Tartaruga - Daniel e Tiago.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h> 

typedef enum _BOOLEAN {FALSE = 0, TRUE = 1} BOOLEAN;


typedef struct
{
	char runner;
	int color;
	char nome[50];
} card;

typedef struct
{
	char v[81];
	int n;
} deck;

typedef struct
{
	char v[8];
	int n;
} mesa;

typedef struct
{
	char v[7];
	int n;
} hand;

typedef struct
{
	char v[3];
	int n;
}aposta;

typedef struct
{
	char v[5];
	int n;
}deck_aposta;

typedef struct
{
	char nome[20];
	hand mao;
	aposta aposta_mao;
}player;

void troca(char* a, char* b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

//Opção A 1. Pedir o Nome do jogador (Máximo 20 caracteres)  2. Selecionar aleatoriamente quem é o primeiro jogador, humano ou BOT.
void pedirNome(player* player)
{
	printf("Digite o nome do jogador (maximo 20 caracteres): ");
	scanf("%s", player->nome);
}
void selecionarPrimeiroJogador()
{
	srand(time(NULL));
	int numeroAleatorio = rand() % 2;

	if (numeroAleatorio == 0) {
		printf("Voce joga primeiro!\n");
	}
	else {
		printf("O Bot joga primeiro!\n");
	}
}

// 3. O tabuleiro de jogo com os 11 espaços sorteados.
char tabuleiro[11] = { 'P','C','C','C','C','C','C','C','R','R','F' };
void embaralhar_tabuleiro(char tabuleiro[])
{
	srand(time(NULL));


	for (int i = 1; i < 9; i++)
	{
		int j = rand() % 8 + 1;
		char temp = tabuleiro[i];
		tabuleiro[i] = tabuleiro[j];
		tabuleiro[j] = temp;
	}
}
void desenhar_tabuleiro(char tabuleiro[])
{
	printf("Tabuleiro: ");

	for (int i = 0; i < 11; i++)
	{
		printf("[%d: %c] ", i, tabuleiro[i]);
	}
	printf("\n");
}

//3. Baralhar as cartas de aposta e distribuí-las pelos jogadores (ver regras).
void deckaposta(card baralho[5])
{
	strcpy(baralho[0].nome, "W");
	strcpy(baralho[1].nome, "H");
	strcpy(baralho[2].nome, "T");
	strcpy(baralho[3].nome, "F");
	strcpy(baralho[4].nome, "S");
}
void embaralhar(deck_aposta* Baposta)
{
	int i, x;
	card baralho[5];
	deckaposta(baralho);

	srand(time(NULL));
	for (i = 0; i < 5; i++)
	{
		x = rand() % 5;
		troca(&Baposta->v[i], &Baposta->v[x]);
	}
}
void darcartas_aposta1(deck_aposta baralho_aposta, aposta* mesa1) // dar as cartas de aposta ao jogador1 que vao estar na mesa1
{
	int i;
	for (i = 0; i < 2; i++)
	{
		mesa1->v[i] = baralho_aposta.v[baralho_aposta.n - 1 - i];
	}
	baralho_aposta.n -= 2;
	mesa1->n += 2;
}
void darcartas_aposta2(deck_aposta baralho_aposta, aposta* mesa2) // dar cartas ao jogador2 que vao estar na mesa2
{
	int i;
	for (i = 0; i < 2; i++)
	{
		mesa2->v[i] = baralho_aposta.v[baralho_aposta.n - 1 - i];
	}
	baralho_aposta.n -= 2;
	mesa2->n += 2;
}

void mesa_players() //mesa de aposta

{
	deck_aposta baralho_aposta;
	baralho_aposta.n = 5;
	aposta mesa1, mesa2;

	mesa1.n = 0;
	mesa2.n = 0;

	darcartas_aposta1(baralho_aposta, &mesa1);
	darcartas_aposta2(baralho_aposta, &mesa2);
}
//3. Baralhar as cartas de corrida, distribuir as mãos iniciais dos jogadores(ver regras) e fazer o deck de corrida

void initbaralho(deck* baralho)
{
	int i;
	baralho->n = 0;

	for (i = 0; i < 13; i++)
	{
		baralho->v[i + baralho->n] = 'W';
	}
	baralho->n += 13;

	for (i = 0; i < 3; i++)
	{
		baralho->v[i + baralho->n] = 'U';
	}
	baralho->n += 3;

	for (i = 0; i < 18; i++)
	{
		baralho->v[i + baralho->n] = 'H';
	}
	baralho->n += 18;

	for (i = 0; i < 17; i++)
	{
		baralho->v[i + baralho->n] = 'T';
	}
	baralho->n += 17;

	for (i = 0; i < 15; i++)
	{
		baralho->v[i + baralho->n] = 'S';
	}
	baralho->n += 15;

	for (i = 0; i < 15; i++)
	{
		baralho->v[i + baralho->n] = 'F';
	}
	baralho->n += 15;
}
void baralhar(deck* baralho)
{
	int i, x;
	srand(time(NULL));

	for (i = 0; i < 81; i++)
	{
		x = rand() % 81;
		troca(&baralho->v[i], &baralho->v[x]);
	}
}
void mao_j1(hand* mao_j1, deck* baralho)
{
	int i;
	mao_j1->n = 7;
	for (i = 0; i < 7; i++)
	{
		mao_j1->v[i] = baralho->v[baralho->n - 1 - i];

		baralho->n -= 1;
	}
}
void mao_j2(hand* mao_j2, deck* baralho)
{
	int i;
	mao_j2->n = 7;
	for (i = 0; i < 7; i++)
	{
		mao_j2->v[i] = baralho->v[baralho->n - 1 - i];
		baralho->n -= 1;
	}
}

//3. Escolher a 2ª aposta para cada jogador
void aposta2humano(hand mao_j1, aposta* mesa1)
{
	int i;
	for (i = 0; i < 1; i++)
	{
		mesa1->v[i] = mao_j1.v[mao_j1.n - 1 - i];
	}
	mao_j1.n -= 1;
	mesa1->n += 1;
}
void aposta2bot(hand mao_j2, aposta* mesa2)
{
	int i;
	for (i = 0; i < 1; i++)
	{
		mesa2->v[i] = mao_j2.v[mao_j2.n - 1 - i];
	}
	mao_j2.n -= 1;
	mesa2->n += 1;
}

//funções que acrescentei

void PrintDeck(deck deck)
{
	int i;
	for (i = 0; i < 81; i++)
		printf("%c", deck.v[i]);
}

void PrintMao(hand hand_player)
{
	int i;
	for (i = 0; i < 7; i++)
		printf("%c", hand_player.v[i]);
}

void InitMesa(mesa* table)
{
	int i;
	for (i = 0; i < 8; i++)
		table->v[i] = ' ';
}


void jogarcarta(hand* jogador, hand* mesa)
{
	int i;
	int carta;
	carta = rand() % jogador->n; // Escolhe uma carta aleatória.
	mesa->v[mesa->n] = jogador->v[carta]; // Coloca a carta na mesa.
	for (i = carta; i < jogador->n - 1; i++) // Remove a carta da mão do jogador.
		jogador->v[i] = jogador->v[i + 1];
	jogador->n--; // Reduz o número de cartas na mão do jogador.
	mesa->n++; // Aumenta o número de cartas na mesa.
}

BOOLEAN endgame(hand table)
{
	if (table.n == 8)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void printgame(hand jogador, hand mesa, int ronda)
{
	printf("Cartas do jogador: %s\n", jogador.v);
	printf("Cartas da mesa: %s\n", mesa.v);
	printf("Ronda: %d\n", ronda);
}

/*void jogadas(player jogador[], mesa* mesa)
{
	int ronda = 0;
	int ativo = 0; // Supondo que 0 representa o índice do jogador humano e 1 o índice do jogador bot

	do
	{
		ronda++;
		jogarcarta(&jogador[ativo].mao, mesa);
		printgame(jogador[0].mao, *mesa, ronda); // Assumindo que o jogador[0] é o jogador humano
		ativo = !ativo; // Alterna o jogador ativo.
	} while (!endgame(*mesa)); // Continua enquanto o jogo não terminar.

	// Supondo que você tenha uma função chamada printwiner para exibir o vencedor
	printwiner(*mesa);
}*/

//4.1. Realizar os turnos dos jogadores.
void realizar_turno_jogador(player* jogador, mesa* mesa)
{
	printf("\n%s, E a sua vez:\n", jogador->nome);

	char animal_escolhido;
	printf("Escolha o animal que pretende jogar (W, H, T, F, S): ");
	scanf(" %c", &animal_escolhido);

	int num_cartas;
	printf("Quantas cartas quer jogar: ");
	scanf("%d", &num_cartas);

	int i;
	int carta;
	//Encontrar os indices das cartas
	for (i = 0; i < jogador->mao.n - 1; i++) // Remove a carta da mão do jogador.
	{
		if (jogador->mao.v[i] == animal_escolhido)
			carta = i;
	}
	

	//carta = rand() % jogador_atual->mao.n; // Escolhe uma carta aleatória.
	mesa->v[mesa->n] = jogador->mao.v[carta]; // Coloca a carta na mesa.
	for (i = carta; i < jogador->mao.n - 1; i++) // Remove a carta da mão do jogador.
		jogador->mao.v[i] = jogador->mao.v[i + 1];
	jogador->mao.n--; // Reduz o número de cartas na mão do jogador.
	mesa->n++; // Aumenta o número de cartas na mesa.

	int opcao_sair;
	printf("Deseja sair? (1 para sim, 0 para nao): ");
	scanf("%d", &opcao_sair);
	if (opcao_sair == 1)
	{
		printf("Jogo interrompido. Gravando estado...\n");
		// Adicione aqui a lógica para gravar o estado do jogo em um arquivo ou outra estrutura de dados
		exit(0);
	}
}


//4.2. Realizar a ação escolhida (humano ou BOT) e atualizar a consola com os novos dados.



/*4.3. Repor a mão do jogador ativo• Se o deck de corrida terminar deve baralhar as cartas descartadas
 e refazer o deck de corrida antes de continuar.*/



 //Opção C Apresentar na consola um resumo das regras do jogo
void regras()
{
	setlocale(LC_ALL, "Portuguese");
	FILE* fp;

	if ((fp = fopen("regras.txt", "r")) != NULL)
	{
		setlocale(LC_ALL, "Portuguese");
		char linhas[500];

		while (fgets(linhas, sizeof(linhas), fp) != NULL)
		{
			setlocale(LC_ALL, "Portuguese");
			printf("%s", linhas);
		}
		fclose(fp);
	}
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
	int escolha, voltar;
	int ronda = 0;

	deck baralho;
	initbaralho(&baralho);
	baralhar(&baralho);

	player jogador[2]; // Assuming there are two players
	mesa mesa_jogo;

	do
	{
		printf("Menu principal \n");
		printf("1- Novo jogo \n");
		printf("2- Carregar jogo \n");
		printf("3- Regras \n");
		printf("4- Sair \n");
		scanf("%d", &escolha);

		switch (escolha)
		{
		case 1:
		{
			// começa novo jogo
			ronda = 0;

			// pergunta pelo nome dos jogadores
			pedirNome(&jogador[0]);
			printf("Jogador 1: %s\n", jogador[0].nome);
			pedirNome(&jogador[1]);
			printf("Jogador 2: %s\n", jogador[1].nome);

			// seleciona aleatoriamente um jogador
			selecionarPrimeiroJogador();

			// baralha o taboleiro
			embaralhar_tabuleiro(tabuleiro);
			desenhar_tabuleiro(tabuleiro);

			// inicializa as apostas e da as cartas aos jogadores para apostarem
			mesa_players();

			// inicializa o baralhho das 81 cartas e da as maos aos jogadores
			initbaralho(&baralho);
			baralhar(&baralho);
			mao_j1(&jogador[0].mao, &baralho);
			mao_j2(&jogador[1].mao, &baralho);

			// seleciona a segunda aposta de cada jogador
			aposta2humano(jogador[0].mao, &jogador[0].aposta_mao);
			aposta2bot(jogador[1].mao, &jogador[1].aposta_mao);

			// loop do jogo
			do
			{
				ronda++;
				printf("\nRonda %d\n", ronda);

				// print do jogo atual
				printf("\nEstado Atual:\n");
				printf("Tabuleiro: ");
				desenhar_tabuleiro(tabuleiro);
				printf("Jogador 1: \n");
				PrintMao(jogador[0].mao);
				printf("\nJogador 2: \n");
				PrintMao(jogador[1].mao);

				// turnos dos jogadores em ação
				realizar_turno_jogador(&jogador[0], &mesa_jogo);
				realizar_turno_jogador(&jogador[1], &mesa_jogo);

			} while (!endgame(jogador[0].mao) && !endgame(jogador[1].mao)); // continua ate o jogo acabar

			// mostra o vencedor
			printf("\nJogo Concluido! Vencedor: ");
			// logica para determinar o jogador

			break;
		}
		case 2:
		{

			break;
		}
		case 3:
		{
			regras();
			setlocale(LC_ALL, "Portuguese");
			do
			{
				printf("\n Pressine 1 para voltar ao menu principal: \n");
				scanf("%d", &voltar);
			} while (voltar != 1);
			system("cls");
			break;
		}
		case 4:
		{
			printf("Saindo do jogo. \n");

			exit(0);
			break;
		}
		default:
			printf("Opcao invalida. \n");
		}
	} while (escolha != 4);

	return 0;
}	