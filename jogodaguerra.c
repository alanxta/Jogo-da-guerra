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
