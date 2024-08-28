/*
Aluno: Vinícius Frigulha Ribeiro
CC6N - Estrutura de Dados II
GitHub:
https://github.com/vinifrigulha/Estrutura_Dados_II/tree/main/Meus_Codigos_VFR
*/

// -=-=-=-=-=- BIBLIOTECAS -=-=-=-=-=-
#include <stdio.h>
#include <stdlib.h>

// -=-=-=-=-=- ESTRUTURAS -=-=-=-=-=-
struct Node {
  int valor;
  struct Node *esquerda;
  struct Node *direita;
};

// -=-=-=-=-=- FUNÇÕES AUXILIARES -=-=-=-=-=-
// Função auxiliar para encontrar um valor mínimo entre os nós de uma raiz
struct Node *encontrarMinimo(struct Node *raiz) {
  struct Node *atual = raiz;
  while (atual->esquerda != NULL) {
    atual = atual->esquerda;
  }
  return atual;
}

// Função auxiliar para exbir a árvore
void exibirArvore(struct Node *raiz) {
  exibirArvore(raiz->esquerda);
  printf("\n%i", raiz->valor);
  exibirArvore(raiz->direita);
}

// -=-=-=-=-=- FUNÇÕES DO PROGRAMA -=-=-=-=-=-
// Função para criar um novo Nó
struct Node *criarNo(int valor) {
  struct Node *novoNo = (struct Node *)malloc(sizeof(struct Node));
  if (novoNo == NULL) // Verificando se a raiz é NULL
  {
    printf("Erro ao alocar o Nó\n\n");
    exit(-1);
  }
  novoNo->valor = valor;
  novoNo->direita = NULL;
  novoNo->esquerda = NULL;
  return novoNo;
}

// Função para inserir um novo Nó
struct Node *inserirNo(struct Node *raiz, int valor) {
  if (raiz == NULL) // Verificando se a raiz é NULL
  {
    return criarNo(valor);
  } else {
    if (valor <= raiz->valor) {
      raiz->esquerda = inserirNo(raiz->esquerda, valor);
    } else {
      raiz->direita = inserirNo(raiz->direita, valor);
    }
  }
  return raiz;
}

// Função para procurar um Nó
void procurarNo(struct Node *raiz, int valor) {
  if (raiz == NULL) // Verificando se a raiz é NULL
  {
    printf("Elemento %d não encontrado.\n\n", valor);
    return;
  } else {
    if (valor == raiz->valor) {
      printf("O valor %d foi encontrado!\n\n", valor);
    } else if (valor < raiz->valor) {
      printf("O valor %d é menor que %d\n", valor, raiz->valor);
      procurarNo(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
      printf("O valor %d é maior que %d\n", valor, raiz->valor);
      procurarNo(raiz->direita, valor);
    }
    return;
  }
}

// Função para excluir um Nó
struct Node *excluirNo(struct Node *raiz, int valor) {
  if (raiz == NULL) {
    printf("Elemento %d não encontrado\n\n", valor);
    return raiz;
  }
  if (valor < raiz->valor) {
    raiz->esquerda = excluirNo(raiz->esquerda, valor);
  } else if (valor > raiz->valor) {
    raiz->direita = excluirNo(raiz->direita, valor);
  } else {
    // 1º Caso: Nó folha ou nó com um filho
    if (raiz->esquerda == NULL) {
      struct Node *temp = raiz->direita;
      printf("Elemento %d excluído\n\n", valor);
      return temp;
    } else if (raiz->direita == NULL) {
      struct Node *temp = raiz->esquerda;
      printf("Elemento %d excluído\n\n", valor);
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

// -=-=-=-=-=- PROGRAMA PRINCIPAL -=-=-=-=-=-
int main() {
  struct Node *raiz = NULL;

  int n = 0;
  printf("Digite a quantidade de nós a serem adicionados: ");
  scanf("%i", &n);

  while (n > 0) {
    int num = 0;
    printf("Digite um valor: ");
    scanf("%i", &num);
    raiz = inserirNo(raiz, num);
    n--;
  }

  int opcao = -1;
  int valor;
  while (opcao != 0) {
    printf("\n-=-=-=-=-=- MENU -=-=-=-=-=-=-");
    printf("\n\n[1] Procurar um elemento na árvore");
    printf("\n[2] Excluir um elemento da árvore");
    printf("\n[3] Exibir a árvore");
    printf("\n\n[0] Sair do programa");
    printf("\nDigite a sua opção: ");
    scanf("%i", &opcao);

    switch (opcao) {
    case 1:
      printf("\n-=-=-=-=-=- PROCURAR NÓ -=-=-=-=-=-");
      printf("\nDigite um valor a ser procurado: ");
      scanf("%i", &valor);
      procurarNo(raiz, valor);
      break;

    case 2:
      printf("\n-=-=-=-=-=- EXCLUIR NÓ -=-=-=-=-=-");
      printf("\nDigite um valor a ser excluído: ");
      scanf("%i", &valor);
      raiz = excluirNo(raiz, valor);
      break;

    case 3:
      printf("\n-=-=-=-=-=- EXIBIR ÁRVORE -=-=-=-=-=-");
      exibirArvore(raiz);
      break;

    case 0:
      printf("\n-=-=-=-=-=- SAIR DO PROGRAMA -=-=-=-=-=-");
      printf("\nAté mais!!");
      break;

    default:
      printf("\nValor Inválido. Tente novamente.");
      opcao = -1;
      break;
    }
  }

  return 0;
}
