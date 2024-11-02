/*
Aluno: Vinícius Frigulha Ribeiro
CC6N - Estrutura de Dados II
GitHub:
https://github.com/vinifrigulha/Estrutura_Dados_II/blob/main/Meus_Codigos_VFR/Treap.c
*/

// -=-=-=-=-=- BIBLIOTECAS -=-=-=-=-=- //
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// -=-=-=-=-=- ESTRUTURAS -=-=-=-=-=- //
struct NoTreap {
  int valor;
  int prioridade;
  struct NoTreap *esquerda;
  struct NoTreap *direita;
};

// -=-=-=-=-=- FUNÇÕES AUXILIARES -=-=-=-=-=- //
// Função auxiliar para verificar se o valor de entrada é inteiro
int verificaEntrada() {
  int ehValido, valor;
  while (1) {
    ehValido = scanf("%i", &valor);
    if (ehValido == 1) {
      if (valor < 0) { // Não permitir valores negativos
        printf("\nValor inválido.\nTente novamente: ");
        while (getchar() != '\n')
          ; // Limpar a entrada
      } else {
        break;
      }
    } else {
      printf("\nValor inválido.\nTente novamente: ");
      while (getchar() != '\n')
        ; // Limpar a entrada
    }
  }
  return valor;
}

// Função para rotacionar à direita
struct NoTreap *rotacaoDireita(struct NoTreap *no) {
  struct NoTreap *noB = no->esquerda;
  no->esquerda = noB->direita;
  noB->direita = no;
  return noB;
}

// Função para rotacionar à esquerda
struct NoTreap *rotacaoEsquerda(struct NoTreap *no) {
  struct NoTreap *noB = no->direita;
  no->direita = noB->esquerda;
  noB->esquerda = no;
  return noB;
}

// -=-=-=-=-=- FUNÇÕES DO PROGRAMA -=-=-=-=-=- //
// Função para criar um novo Nó com prioridade aleatória
struct NoTreap *criarNo(int valor) {
  struct NoTreap *novoNo = (struct NoTreap *)malloc(sizeof(struct NoTreap));
  if (novoNo == NULL) {
    printf("Erro ao alocar o Nó\n\n");
    exit(-1);
  }
  novoNo->valor = valor;
  novoNo->prioridade = rand() % 100; // Prioridade aleatória
  novoNo->esquerda = NULL;
  novoNo->direita = NULL;
  return novoNo;
}

// Função para inserir um nó
struct NoTreap *inserirNo(struct NoTreap *raiz, int valor) {
    // Inserção na posição de árvore binária de busca
    if (raiz == NULL)
        return criarNo(valor);

    if (valor < raiz->valor) {
        raiz->esquerda = inserirNo(raiz->esquerda, valor);

        // Realizar rotação de acordo com a prioridade para manter a propriedade de heap
        if (raiz->esquerda->prioridade > raiz->prioridade)
            raiz = rotacaoDireita(raiz);

    } else {
        raiz->direita = inserirNo(raiz->direita, valor);

        // Realizar rotação de acordo com a prioridade para manter a propriedade de heap
        if (raiz->direita->prioridade > raiz->prioridade)
            raiz = rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Função para excluir um Nó
struct NoTreap *excluirNo(struct NoTreap *raiz, int valor) {
  if (raiz == NULL) {
    printf("Elemento %d não encontrado.\n\n", valor);
    return NULL;
  }

  if (valor < raiz->valor)
    raiz->esquerda = excluirNo(raiz->esquerda, valor);
  else if (valor > raiz->valor)
    raiz->direita = excluirNo(raiz->direita, valor);
  else { 
    // Encontrou o nó
    printf("Elemento %d excluído com sucesso.\n\n", valor);
    if (raiz->esquerda == NULL) {
      struct NoTreap *temp = raiz->direita;
      free(raiz);
      return temp;
    } else if (raiz->direita == NULL) {
      struct NoTreap *temp = raiz->esquerda;
      free(raiz);
      return temp;
    } else {
      // Rotacionar o nó até que tenha um filho nulo
      if (raiz->esquerda->prioridade > raiz->direita->prioridade) {
        raiz = rotacaoDireita(raiz);
        raiz->direita = excluirNo(raiz->direita, valor);
      } else {
        raiz = rotacaoEsquerda(raiz);
        raiz->esquerda = excluirNo(raiz->esquerda, valor);
      }
    }
  }
  return raiz;
}

// Função para procurar um nó
void procurarNo(struct NoTreap *raiz, int valor) {
  if (raiz == NULL) {
    printf("Elemento %d não encontrado.\n\n", valor);
    return;
  } else if (valor == raiz->valor) {
    printf("O valor %d (%d) foi encontrado!\n\n", valor, raiz->prioridade);
  } else if (valor < raiz->valor) {
    procurarNo(raiz->esquerda, valor);
  } else {
    procurarNo(raiz->direita, valor);
  }
}

// Função para exibir árvore em pé
void exibeArvore(struct NoTreap *raiz, int h) {
  if (raiz != NULL) {
    // Exibe subárvore direita
    exibeArvore(raiz->direita, h + 1);

    // Exibe o valor e a prioridade do nó atual
    for (int i = 0; i < h; i++) {
      printf("       "); // Espaçamento para ajustar a visualização
    }
    printf("%d (%d)\n", raiz->valor, raiz->prioridade);

    // Exibe subárvore esquerda
    exibeArvore(raiz->esquerda, h + 1);
  }
}


// -=-=-=-=-=- PROGRAMA PRINCIPAL -=-=-=-=-=- //
int main() {
  struct NoTreap *raiz = NULL;
  int opcao, valor;
  srand(time(NULL)); // Usado para sempre gerar valores aleatórios da prioridade

  do {
    printf("\n-=-=-=-=-=- MENU -=-=-=-=-=-=-");
    printf("\n\n[1] Inserir um elemento na árvore");
    printf("\n[2] Procurar um elemento na árvore");
    printf("\n[3] Excluir um elemento da árvore");
    printf("\n[4] Exibir a árvore");
    printf("\n[0] Sair do programa");
    printf("\n\nDigite a sua opção: ");

    opcao = verificaEntrada();

    switch (opcao) {
    case 1:
      printf("\nDigite a quantidade de nós a serem adicionados: ");
      int n = verificaEntrada();
      while (n > 0) {
        printf("\nDigite um valor: ");
        int num = verificaEntrada();
        raiz = inserirNo(raiz, num);
        n--;
      }
      break;

    case 2:
      printf("\nDigite um valor para procurar: ");
      valor = verificaEntrada();
      procurarNo(raiz, valor);
      break;

    case 3:
      printf("\nDigite um valor para excluir: ");
      valor = verificaEntrada();
      raiz = excluirNo(raiz, valor);
      break;

    case 4:
      printf("\n-=-=-=-=-=- EXIBIR ÁRVORE -=-=-=-=-=-\n");
      exibeArvore(raiz, 0);
      break;

    case 0:
      printf("\nSaindo do programa...\n");
      free(raiz);
      break;

    default:
      printf("\nValor Inválido. Tente novamente.\n");
      break;
    }
  } while (opcao != 0);

  return 0;
}
