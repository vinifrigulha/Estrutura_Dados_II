/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct No
{
    int valor, prioridade;
    struct No *esq, *dir;
};

struct No* criarNo(int valor)
{
    struct No *novoNo = (struct No*)malloc(sizeof(No));
    if (novoNo == NULL)
    {
        printf("Erro: Falha na alocação de memória.\n");
        return NULL;  // Retorna NULL em caso de falha
    }
    novoNo->valor = valor;
    novoNo->prioridade = rand() % 100;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

No* rotacaoDireita(No* no) {
    No* novoNo = no->esq;
    no->esq = novoNo->dir;
    novoNo->dir = no;
    return novoNo;
}

No* rotacaoEsquerda(No* no) {
    No* novoNo = no->dir;
    node->dir = novoNo->esq;
    novoNo->esq = no;
    return novoNo;
}

struct No* insert(struct No* no, int valor) {
    if (no == NULL) {
        return createNode(key);
    }

    if (key < no->key) {
        no->esq = insert(no->esq, valor);
        if (no->esq->prioridade > no->prioridade) {
            no = rotacaoDireita(no);
        }
    } else {
        no->dir = insert(no->dir, valor);
        if (no->dir->prioridade > no->prioridade) {
            no = rotacaoEsquerda(no);
        }
    }
    return no;
}

int main()
{
    srand(time(0));
    int randon = rand() % 100;
    
    printf("%d", randon);

    return 0;
}
