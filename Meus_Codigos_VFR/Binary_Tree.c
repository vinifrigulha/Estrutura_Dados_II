/*
Aluno: Vinícius Frigulha Ribeiro
CC6N - Estrutura de Dados II
GitHub:
https://github.com/vinifrigulha/Estrutura_Dados_II/blob/main/Meus_Codigos_VFR/AVL.c
*/

// -=-=-=-=- BIBLIOTECAS -=-=-=-=- 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// -=-=-=-=- ESTRUTURAS -=-=-=-=- 
struct NoTreap {
    int valor;
    int prioridade;
    struct NoTreap *esquerda;
    struct NoTreap *direita;
};

// Função para criar um novo nó
struct NoTreap *criarNo(int valor) {
    struct NoTreap *novoNo = (struct NoTreap *)malloc(sizeof(struct NoTreap));
    if (novoNo == NULL) {
        printf("Erro ao alocar o Nó\n\n");
        exit(-1);
    }
    novoNo->valor = valor;
    novoNo->prioridade = rand() % 100; // Atribuindo uma prioridade aleatória
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para realizar a rotação direita
struct NoTreap *rotacaoDireita(struct NoTreap *no) {
    struct NoTreap *novaRaiz = no->esquerda;
    struct NoTreap *subArvore = novaRaiz->direita;

    novaRaiz->direita = no;
    no->esquerda = subArvore;

    return novaRaiz;
}

// Função para realizar a rotação esquerda
struct NoTreap *rotacaoEsquerda(struct NoTreap *no) {
    struct NoTreap *novaRaiz = no->direita;
    struct NoTreap *subArvore = novaRaiz->esquerda;

    novaRaiz->esquerda = no;
    no->direita = subArvore;

    return novaRaiz;
}

// Função para inserir um novo nó na treap
struct NoTreap *inserirNo(struct NoTreap *raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    
    if (valor < raiz->valor) {
        raiz->esquerda = inserirNo(raiz->esquerda, valor);
        if (raiz->esquerda->prioridade > raiz->prioridade) {
            raiz = rotacaoDireita(raiz);
        }
    } else if (valor > raiz->valor) {
        raiz->direita = inserirNo(raiz->direita, valor);
        if (raiz->direita->prioridade > raiz->prioridade) {
            raiz = rotacaoEsquerda(raiz);
        }
    }
    return raiz;
}

// Função para procurar um nó
void procurarNo(struct NoTreap *raiz, int valor) {
    if (raiz == NULL) {
        printf("Elemento %d não encontrado.\n\n", valor);
        return;
    }
    
    if (valor == raiz->valor) {
        printf("O valor %d foi encontrado! (Prioridade: %d)\n\n", valor, raiz->prioridade);
    } else if (valor < raiz->valor) {
        procurarNo(raiz->esquerda, valor);
    } else {
        procurarNo(raiz->direita, valor);
    }
}

// Função para excluir um nó
struct NoTreap *excluirNo(struct NoTreap *raiz, int valor) {
    if (raiz == NULL) {
        printf("Elemento %d não encontrado\n\n", valor);
        return raiz;
    }
    
    if (valor < raiz->valor) {
        raiz->esquerda = excluirNo(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = excluirNo(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL) {
            struct NoTreap *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            struct NoTreap *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        if (raiz->esquerda->prioridade > raiz->direita->prioridade) {
            raiz = rotacaoDireita(raiz);
            raiz->direita = excluirNo(raiz->direita, valor);
        } else {
            raiz = rotacaoEsquerda(raiz);
            raiz->esquerda = excluirNo(raiz->esquerda, valor);
        }
    }
    return raiz;
}

// Função para exibir a árvore em pré-ordem
void preOrder(struct NoTreap *raiz) {
    if (raiz != NULL) {
        printf("%i (P: %i) ", raiz->valor, raiz->prioridade);
        preOrder(raiz->esquerda);
        preOrder(raiz->direita);
    }
}

// -=-=-=-=- PROGRAMA PRINCIPAL -=-=-=-=-
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    struct NoTreap *raiz = NULL;

    int opcao, valor;
    do {
        printf("\n-=-=-=-=-=- MENU -=-=-=-=-=-=-");
        printf("\n\n[1] Inserir um elemento na treap");
        printf("\n[2] Procurar um elemento na treap");
        printf("\n[3] Excluir um elemento da treap");
        printf("\n[4] Exibir a treap (PRE-ORDER)");
        printf("\n[0] Sair do programa");
        printf("\n\nDigite a sua opção: ");

        scanf("%i", &opcao);

        switch (opcao) {
        case 1:
            printf("\nDigite um valor: ");
            scanf("%i", &valor);
            raiz = inserirNo(raiz, valor);
            break;

        case 2:
            printf("\nDigite um valor a ser procurado: ");
            scanf("%i", &valor);
            procurarNo(raiz, valor);
            break;

        case 3:
            printf("\nDigite um valor a ser excluído: ");
            scanf("%i", &valor);
            raiz = excluirNo(raiz, valor);
            break;

        case 4:
            printf("\n-=-=-=-=-=- EXIBIR TREAP -=-=-=-=-=-\n");
            printf("\nPRE-ORDER: ");
            preOrder(raiz);
            printf("\n");
            break;

        case 0:
            printf("\n-=-=-=-=-=- SAIR DO PROGRAMA -=-=-=-=-=-");
            printf("\nAté mais!!");
            free(raiz);
            break;

        default:
            printf("\nValor Inválido. Tente novamente.");
            break;
        }
    } while (opcao != 0);

    return 0;
}
