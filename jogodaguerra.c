#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
    COPAS, 
    OUROS, 
    ESPADAS, 
    PAUS} Naipe;

typedef enum {
    AS = 1, 
    DOIS, 
    TRES, 
    QUATRO, 
    CINCO, 
    SEIS, 
    SETE,         
    OITO, 
    NOVE, 
    DEZ, 
    VALETE, 
    DAMA, 
    REI
    } Valor;

typedef struct {
    Naipe naipe;
    Valor valor;
} Carta;

typedef struct cartaNo {
    Carta carta;
    struct cartaNo* prox;
} cartaNo;

typedef struct {
    char nome[30];
    cartaNo* pilha;
    int pontos;
} Jogador;

Carta criarCarta(Naipe naipe, Valor valor) {
    Carta c;
    c.naipe = naipe;
    c.valor = valor;
    return c;
}

void adicionarCarta(cartaNo** pilha, Carta carta) {
    cartaNo* nova = (cartaNo*)malloc(sizeof(cartaNo));
    nova->carta = carta;
    nova->prox = NULL;

    if (*pilha == NULL) {
        *pilha = nova;
    } else {
        cartaNo* aux = *pilha;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = nova;
    }
}

void mostrarCarta(Carta c) {
    char* naipes[] = {"Copas", "Ouros", "Espadas", "Paus"};
    char* valores[] = {"", "As", "2", "3", "4", "5", "6", "7",
                        "8", "9", "10", "Valete", "Dama", "Rei"};
    printf("%s de %s", valores[c.valor], naipes[c.naipe]);
}


Carta removerCarta(cartaNo** pilha) {
    if (*pilha == NULL) {
        Carta cartaVazia = {COPAS, AS};
        return cartaVazia;
    }

    cartaNo* temp = *pilha;
    Carta carta = temp->carta;
    *pilha = temp->prox;
    free(temp);
    return carta;
}

void criarBaralho(Carta baralho[], int* tamanho) {
    int index = 0;
    for (int n = 0; n < 4; n++) {
        for (int v = 1; v <= 13; v++) {
            baralho[index++] = criarCarta((Naipe)n, (Valor)v);
        }
    }
    *tamanho = index;
}


void embaralhar(Carta baralho[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int r = rand() % tamanho;
        Carta temp = baralho[i];
        baralho[i] = baralho[r];
        baralho[r] = temp;
    }
}

void listarCartas(cartaNo* pilha) {
    if (pilha == NULL) {
        printf("Sem cartas.\n");
        return;
    }

    cartaNo* aux = pilha;
    int i = 1;
    while (aux != NULL) {
        printf("%d - ", i++);
        mostrarCarta(aux->carta);
        printf("\n");
        aux = aux->prox;
    }
}

int contarCartas(cartaNo* pilha) {
    int cont = 0;
    cartaNo* aux = pilha;
    while (aux != NULL) {
        cont++;
        aux = aux->prox;
    }
    return cont;
}



void mensagensVitorias(const char* nome) {
    const char* frases[] = {
        "Mandou bem, %s! você venceu essa rodada",
        "Parabens, %s",
        "Boa jogada, %s! 1 ponto pra você",
        "Inteligente, %s"
    };
    int r = rand() % 4;
    printf(frases[r], nome);
    printf("\n");
}



void mensagensDerrotas() {
    const char* frases[] = {
        "Computador ganhou essa :(",
        "Não foi dessa vez",
        "Computador saiu por cima",
        "O computador se deu bem nessa "
    };
    int r = rand() % 4;
    printf("%s\n", frases[r]);
}



void mensagensEmpate() {
    const char* frases[] = {
        "Empate, Cartas descartadas",
        "Vish, empate. Ninguém ganhou",
        "Empatouu!!",
        "Empate. Próxima rodada vai"
    };
    int r = rand() % 4;
    printf("%s\n", frases[r]);
}



void salvarPlacar(Jogador jogador, Jogador computador) {
    FILE* arquivo = fopen("placar.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return ;
    }

    fprintf(arquivo, "Jogador: %s - Pontos: %d\n", jogador.nome, jogador.pontos);
    fprintf(arquivo, "Computador - Pontos: %d\n", computador.pontos);

    if (jogador.pontos > computador.pontos) {
        fprintf(arquivo, "Vencedor: %s\n", jogador.nome);
    } else if (computador.pontos > jogador.pontos) {
        fprintf(arquivo, "Vencedor: Computador\n");
    } else {
        fprintf(arquivo, "Empate\n");
    }
    fprintf(arquivo, "--------------------------\n");

    fclose(arquivo);
}



void mostrarPlacar() {
    FILE* arquivo = fopen("placar.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum placar registrado pois o jogo nao foi finalizado.\n");
        return;
    }

    char linha[100];
    printf("\n===== PLACAR =====\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }
    printf("===================\n");

    fclose(arquivo);
}



Carta removeCartaAleatoria(cartaNo** pilha) {
    int total = contarCartas(*pilha);

    if (total == 0) {
        Carta cartaVazia = {COPAS, AS};
        return cartaVazia;
    }

    int posicao = (rand() % total) + 1;

    cartaNo** ptr = pilha;
    for (int i = 1; i < posicao; i++) {
        ptr = &((*ptr)->prox);
    }

    cartaNo* escolhida = *ptr;
    Carta carta = escolhida->carta;
    *ptr = escolhida->prox;
    free(escolhida);

    return carta;
}





int main() {
    srand(time(NULL));

    Jogador jogador, computador;
    jogador.pilha = NULL;
    computador.pilha = NULL;
    jogador.pontos = 0;
    computador.pontos = 0;


    printf("Digite seu nome: ");
    fgets(jogador.nome, sizeof(jogador.nome), stdin);
    jogador.nome[strcspn(jogador.nome, "\n")] = 0;



    Carta baralho[52];
    int tamanhoBaralho;
    criarBaralho(baralho, &tamanhoBaralho);
    embaralhar(baralho, tamanhoBaralho);

    for (int i = 0; i < tamanhoBaralho; i++) {
        if (i % 2 == 0)
            adicionarCarta(&jogador.pilha, baralho[i]);
        else
            adicionarCarta(&computador.pilha, baralho[i]);
    }



    int opcao, rodada = 0;
    do {
        printf("\n------ MENU ------\n");
        printf("Rodada atual: %d\n", rodada + 1);
        printf("1 - Jogar uma rodada\n");
        printf("2 - Ver minhas cartas\n");
        printf("3 - Ver cartas do computador\n");
        printf("4 - Ver placar \n");
        printf("5 - Sair\n");
        printf("------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();



        switch (opcao) {
            case 1:
                if (jogador.pilha == NULL || computador.pilha == NULL) {
                    printf("\nO jogo terminou!\n");
                    break;
                }
                rodada++;


                printf("\n===== Rodada %d =====\n", rodada);

                listarCartas(jogador.pilha);

                int escolha;
                int totalCartas = contarCartas(jogador.pilha);


                do {
                    printf("=====================\n");
                    printf("Escolha o numero da carta que deseja jogar: ");
                    scanf("%d", &escolha);
                    if (escolha > totalCartas)
                    {
                      printf("Esta carta nao existe\n");
                    }
                    
                    getchar();
                } while (escolha < 1 || escolha > totalCartas);



                cartaNo** ptr = &jogador.pilha;
                for (int j = 1; j < escolha; j++) {
                    ptr = &((*ptr)->prox);
                }

                cartaNo* escolhida = *ptr;

                Carta cartaJogador = escolhida->carta;

                *ptr = escolhida->prox;

                free(escolhida);

                Carta cartaComputador = removeCartaAleatoria(&computador.pilha);


                printf("\nJogando cartas...\n");

                printf("\n%s jogou: ", jogador.nome);
                mostrarCarta(cartaJogador);
                printf("\n");


                printf("Computador jogou: ");
                mostrarCarta(cartaComputador);
                printf("\n");


                if (cartaJogador.valor > cartaComputador.valor) {
                    mensagensVitorias(jogador.nome);
                    adicionarCarta(&jogador.pilha, cartaJogador);
                    adicionarCarta(&jogador.pilha, cartaComputador);
                    jogador.pontos++;
                } else if (cartaComputador.valor > cartaJogador.valor) {
                    mensagensDerrotas();
                    adicionarCarta(&computador.pilha, cartaJogador);
                    adicionarCarta(&computador.pilha, cartaComputador);
                    computador.pontos++;
                } else {
                    mensagensEmpate();
                }

                printf("\n===== Resultado da rodada =====\n");
                printf("%s - Cartas: %d | Pontos: %d\n", jogador.nome, contarCartas(jogador.pilha), jogador.pontos);
                printf("Computador - Cartas: %d | Pontos: %d\n", contarCartas(computador.pilha), computador.pontos);

                if (jogador.pilha == NULL) {
                    printf("\n%s ficou sem cartas...\n", jogador.nome);
                    printf("===> COMPUTADOR É O CAMPEÃO DA GUERRA!\n");
                    salvarPlacar(jogador, computador);
                    opcao = 5;
                } else if (computador.pilha == NULL) {
                    printf("\nO computador ficou sem cartas...\n");
                    printf("===> %s É O CAMPEÃO DA GUERRA!\n", jogador.nome);
                    salvarPlacar(jogador, computador);
                    opcao = 5;
                }
                break;

            case 2:
                printf("\nSuas cartas:\n");
                listarCartas(jogador.pilha);
                break;


            case 3:
                printf("\nCartas do computador:\n");
                listarCartas(computador.pilha);
                break;


            case 4:
                printf("\nPlacar atual:\n");
                printf("%s: %d pontos\n", jogador.nome, jogador.pontos);
                printf("Computador: %d pontos\n", computador.pontos);
                break;

            case 5:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (opcao != 5);

    int verPlacar;
    printf("\nDeseja ver o placar salvo? (1-Sim / 2-Nao): ");
    scanf("%d", &verPlacar);
    getchar();

    
    if (verPlacar == 1) {
        mostrarPlacar();
    }

    printf("\nObrigado por jogar o jogo da guerra!\n");
    return 0;
}
