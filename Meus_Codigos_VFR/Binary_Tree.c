/* 
Aluno: Vinícius Frigulha Ribeiro
CC6N - Estrutura de Dados II
GitHub: vinifrigulha
*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int valor;
  struct Node *esquerda;
  struct Node *direita;
};

struct Node *criarNo(int valor)
{
  struct Node *novoNo = (struct Node *)malloc(sizeof(struct Node));
  if (novoNo == NULL)
  {
    printf("Erro ao alocar o Nó\n\n");
    return 1;
  }
  novoNo->valor = valor;
  novoNo->direita = NULL;
  novoNo->esquerda = NULL;
  return novoNo;
}

struct Node *inserirNo(struct Node *raiz, int valor)
{
  if (raiz == NULL)
  {
    return criarNo(valor);
  }
  else 
  {
    if (valor <= raiz->valor)
    {
      raiz->esquerda = inserirNo(raiz->esquerda, valor);
    }
    else
    {
      raiz->direita = inserirNo(raiz->direita, valor);
    }
  }
  return raiz;
}

void procurarNo(struct Node *raiz, int valor)
{
  if (raiz == NULL)
  {
    printf("Elemento %d não encontrado.\n\n", valor);
    return;
  }
  else
  {
    if (valor == raiz->valor)
    {
      printf("O valor %d foi encontrado!\n\n", valor);
    }
    else if (valor < raiz->valor)
    {
      printf("O valor %d é menor que %d\n", valor, raiz->valor);
      procurarNo(raiz->esquerda, valor);
    }
    else if (valor > raiz->valor)
    {
      printf("O valor %d é maior que %d\n", valor, raiz->valor);
      procurarNo(raiz->direita, valor);
    }
    return;
  }
}

struct Node *encontrarMinimo(struct Node *raiz)
{
  struct Node *atual = raiz;
  while (atual->esquerda != NULL)
  {
    atual = atual->esquerda;
  }
  return atual;
}

struct Node *excluirNo(struct Node *raiz, int valor)
{
  if (raiz == NULL)
  {
    printf("Elemento %d não encontrado\n\n", valor);
    return raiz;
  }
  if (valor < raiz->valor)
  {
    raiz->esquerda = excluirNo(raiz->esquerda, valor);
  }
  else if (valor > raiz->valor)
  {
    raiz->direita = excluirNo(raiz->direita, valor);
  }
  else
  {
    // 1º Caso: Nó folha ou nó com um filho
    if (raiz->esquerda == NULL)
    {
      struct Node *temp = raiz->direita;
      free(raiz);
      printf("Elemento %d excluído\n\n", valor);
      return temp;
    }
    else if (raiz->direita == NULL)
    {
      struct Node *temp = raiz->esquerda;
      printf("Elemento %d excluído\n\n", valor);
      free(raiz);
      return temp;
    }

    // 2º Caso: Nó com filhos
    struct Node *temp = encontrarMinimo(raiz->direita);
    raiz->valor = temp->valor;
    raiz->direita = excluirNo(raiz->direita, temp->valor);
    printf("Elemento %d excluído\n", valor);
  }
  return raiz;
}

int main()
{
  struct Node *raiz = NULL;

  raiz = inserirNo(raiz, 3);
  raiz = inserirNo(raiz, 2);
  raiz = inserirNo(raiz, 1);
  raiz = inserirNo(raiz, 6);
  raiz = inserirNo(raiz, 5);
  raiz = inserirNo(raiz, 4);

  printf("BORA PROCURAR ESSA PESTE\n");
  procurarNo(raiz, 7);

  printf("BORA EXCLUIR ESSA PESTE\n");
  excluirNo(raiz, 4);

  printf("BORA PROCURAR ESSA PESTE\n");
  procurarNo(raiz, 3);
  
  return 0;
}
