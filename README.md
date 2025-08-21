# Detective-quest
Implementação em linguagem C de um sistema de exploração de uma mansão para o jogo: detective quest.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========================= Estruturas =========================
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// ========================= Criação =========================
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    if (!nova) {
        fprintf(stderr, "Erro ao alocar memoria!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita  = NULL;
    return nova;
}

// Mapa padrão da mansão (árvore binária)
Sala* montarMapaPadrao(void) {
    Sala* hall = criarSala("Hall de Entrada");
    hall->esquerda = criarSala("Biblioteca");
    hall->direita  = criarSala("Sala de Jantar");

    hall->esquerda->esquerda = criarSala("Escritorio");
    hall->esquerda->direita  = criarSala("Sala Secreta");

    hall->direita->esquerda  = criarSala("Cozinha");
    hall->direita->direita   = criarSala("Jardim de Inverno");
    return hall;
}

// ========================= Jogo =========================
void explorar(Sala* atual) {
    char escolha;
    while (1) {
        printf("\nVoce esta na sala: %s\n", atual->nome);

        if (!atual->esquerda && !atual->direita) {
            printf("Esta sala nao possui mais saidas. Fim da exploracao!\n");
            break;
        }

        printf("Opcoes de navegacao:\n");
        if (atual->esquerda) printf("  [e] Ir para %s\n", atual->esquerda->nome);
        if (atual->direita)  printf("  [d] Ir para %s\n", atual->direita->nome);
        printf("  [s] Sair do jogo\n");
        printf("Escolha: ");

        if (scanf(" %c", &escolha) != 1) { // leitura segura
            fprintf(stderr, "Entrada invalida.\n");
            break;
        }

        if (escolha == 'e' && atual->esquerda)      atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita)  atual = atual->direita;
        else if (escolha == 's') {
            printf("Voce decidiu encerrar a exploracao.\n");
            break;
        } else {
            printf("Caminho invalido! Tente novamente.\n");
        }
    }
}

// ========================= Desalocacao =========================
// Libera toda a arvore (pos-ordem)
void liberarArvore(Sala* raiz) {
    if (!raiz) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

// ========================= main =========================
int main(void) {
    Sala* mapa = montarMapaPadrao();
    explorar(mapa);
    liberarArvore(mapa); // evita vazamento de memoria
    return 0;
}
