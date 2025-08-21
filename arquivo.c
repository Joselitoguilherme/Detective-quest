#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    struct Sala *esq, *dir;
} Sala;

// Cria uma nova sala
Sala* novaSala(const char* nome) {
    Sala* s = malloc(sizeof(Sala));
    strcpy(s->nome, nome);
    s->esq = s->dir = NULL;
    return s;
}

// Monta o mapa (árvore fixa)
Sala* montarMapa() {
    Sala* h = novaSala("Hall de Entrada");
    h->esq = novaSala("Biblioteca");
    h->dir = novaSala("Sala de Jantar");
    h->esq->esq = novaSala("Escritorio");
    h->esq->dir = novaSala("Sala Secreta");
    h->dir->esq = novaSala("Cozinha");
    h->dir->dir = novaSala("Jardim de Inverno");
    return h;
}

// Exploração do mapa
void explorar(Sala* atual) {
    char op;
    while (1) {
        printf("\nVoce esta em: %s\n", atual->nome);
        if (!atual->esq && !atual->dir) { printf("Fim da exploracao!\n"); break; }

        if (atual->esq) printf("[e] %s  ", atual->esq->nome);
        if (atual->dir) printf("[d] %s  ", atual->dir->nome);
        printf("[s] Sair\nEscolha: ");
        scanf(" %c", &op);

        if (op=='e' && atual->esq) atual=atual->esq;
        else if (op=='d' && atual->dir) atual=atual->dir;
        else if (op=='s') { printf("Exploracao encerrada.\n"); break; }
        else printf("Opcao invalida!\n");
    }
}

// Libera memória da árvore
void liberar(Sala* r) {
    if (!r) return;
    liberar(r->esq);
    liberar(r->dir);
    free(r);
}

int main() {
    Sala* mapa = montarMapa();
    explorar(mapa);
    liberar(mapa);
    return 0;
}
