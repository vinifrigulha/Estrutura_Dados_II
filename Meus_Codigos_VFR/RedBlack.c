/*
Aluno: Vinícius Frigulha Ribeiro
CC6N - Estrutura de Dados II
GitHub:
https://github.com/vinifrigulha/Estrutura_Dados_II/blob/main/Meus_Codigos_VFR/RedBlack.c
*/

// -=-=-=-=-=- BIBLIOTECAS -=-=-=-=-=-
#include <stdio.h>
#include <stdlib.h>

// -=-=-=-=-=- ESTRUTURAS -=-=-=-=-=-
struct NoRB {
  int valor;
  struct NoRB *pai;
  struct NoRB *esquerda;
  struct NoRB *direita;
  int cor; // 1 para PRETO e 0 para VERMELHO
};

// -=-=-=-=-=- FUNÇÕES AUXILIARES -=-=-=-=-=-
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

// Função para calcular a altura da árvore
int alturaArvore(struct NoRB *raiz) {
  if (raiz == NULL) {
    return -1;
  }
  int alturaEsquerda = alturaArvore(raiz->esquerda) + 1;
  int alturaDireita = alturaArvore(raiz->direita) + 1;

  if (alturaEsquerda > alturaDireita) {
    return alturaEsquerda;
  } else {
    return alturaDireita;
  }
}

// -=-=-=-=-=- FUNÇÕES DO PROGRAMA -=-=-=-=-=-
// Função para criar um novo Nó
struct NoRB *criarNo(int valor) {
  struct NoRB *novoNo = (struct NoRB *)malloc(sizeof(struct NoRB));
  if (novoNo == NULL) // Verificando se a raiz é NULL
  {
    printf("Erro ao alocar o Nó\n\n");
    exit(-1);
  }
  novoNo->valor = valor;
  novoNo->direita = NULL;
  novoNo->esquerda = NULL;
  novoNo->pai = NULL;
  novoNo->cor = 0;
  return novoNo;
}

// Função para realizar a RSD (Rotação Simples Direita)
void rotacaoDireita(struct NoRB **raiz, struct NoRB *noA) {
  struct NoRB *noB = noA->esquerda;
  noA->esquerda = noB->direita;
  if (noB->direita != NULL) {
    noB->direita->pai = noA;
  }
  noB->pai = noA->pai;
  if (noA->pai == NULL) {
    *raiz = noB;
  } else if (noA == noA->pai->direita) {
    noA->pai->direita = noB;
  } else {
    noA->pai->esquerda = noB;
  }
  noB->direita = noA;
  noA->pai = noB;
}

// Função para realizar a RSD (Rotação Simples Esquerda)
void rotacaoEsquerda(struct NoRB **raiz, struct NoRB *noA) {
  struct NoRB *noB = noA->direita;
  noA->direita = noB->esquerda;
  if (noB->esquerda != NULL) {
    noB->esquerda->pai = noA;
  }
  noB->pai = noA->pai;
  if (noA->pai == NULL) {
    *raiz = noB;
  } else if (noA == noA->pai->esquerda) {
    noA->pai->esquerda = noB;
  } else {
    noA->pai->direita = noB;
  }
  noB->esquerda = noA;
  noA->pai = noB;
}

// Função para balancear a árvore após a inserção de um nó
void balancear(struct NoRB **raiz, struct NoRB *noA) {
  while (noA != *raiz && noA->pai->cor == 0) {
    if (noA->pai == noA->pai->pai->esquerda) {
      struct NoRB *noB = noA->pai->pai->direita;
      if (noB != NULL && noB->cor == 0) {
        noA->pai->cor = 1;
        noB->cor = 1;
        noA->pai->pai->cor = 0;
        noA = noA->pai->pai;
      } else {
        if (noA == noA->pai->direita) {
          noA = noA->pai;
          rotacaoEsquerda(raiz, noA);
        }
        noA->pai->cor = 1;
        noA->pai->pai->cor = 0;
        rotacaoDireita(raiz, noA->pai->pai);
      }
    } else {
      struct NoRB *noB = noA->pai->pai->esquerda;
      if (noB != NULL && noB->cor == 0) {
        noA->pai->cor = 1;
        noB->cor = 1;
        noA->pai->pai->cor = 0;
        noA = noA->pai->pai;
      } else {
        if (noA == noA->pai->esquerda) {
          noA = noA->pai;
          rotacaoDireita(raiz, noA);
        }
        noA->pai->cor = 1;
        noA->pai->pai->cor = 0;
        rotacaoEsquerda(raiz, noA->pai->pai);
      }
    }
  }
  (*raiz)->cor = 1;
}

// Função para inserir um novo Nó
void inserirNo(struct NoRB **raiz, int valor) {
  struct NoRB *noA = criarNo(valor);
  struct NoRB *noB = NULL;
  struct NoRB *noC = *raiz;

  while (noC != NULL) {
    noB = noC;
    if (noA->valor < noC->valor) {
      noC = noC->esquerda;
    } else {
      noC = noC->direita;
    }
  }
  noA->pai = noB;
  if (noB == NULL) {
    *raiz = noA;
  } else if (noA->valor < noB->valor) {
    noB->esquerda = noA;
  } else {
    noB->direita = noA;
  }

  balancear(raiz, noA);
}

// Função para procurar um Nó
void procurarNo(struct NoRB *raiz, int valor) {
  if (raiz == NULL) // Verificando se a raiz é NULL
  {
    printf("Elemento %d não encontrado.\n\n", valor);
    return;
  } else {
    if (valor == raiz->valor) {
      printf("O valor %d foi encontrado!\n\n", valor);
    } else if (valor < raiz->valor) {
      procurarNo(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
      procurarNo(raiz->direita, valor);
    }
    return;
  }
}

// Função para retornar a cor do nó procurado
void corNo(struct NoRB *raiz, int valor) {
  if (raiz == NULL) // Verificando se a raiz é NULL
  {
    printf("Elemento %d não encontrado.\n\n", valor);
    return;
  } else {
    if (valor == raiz->valor) {
      if (raiz->cor == 0){
        printf("A cor do nó %d é VERMELHA\n\n", valor);
      } else {
        printf("A cor do nó %d é PRETA\n\n", valor);
      }
    } else if (valor < raiz->valor) {
      corNo(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
      corNo(raiz->direita, valor);
    }
    return;
  }
}

// Função para imprimir a árvore de acordo com o formato esquerda-raiz-direita
void exibeArvoreRB(struct NoRB *raiz, int h) {
  if (raiz != NULL) {
    // Chama a função recursivamente para percorrer a subárvore direita
    exibeArvoreRB(raiz->direita, h + 1);

    // Imprime o valor do nó atual com um espaçamento proporcional à sua
    // profundidade
    for (int i = 0; i < h; i++)
      printf("       "); // espaços por nível
    if (raiz->cor == 0)
      printf("\033[31m%d\033[0m\n\n", raiz->valor);
    else
      printf("%d\n\n", raiz->valor);

    // Chama a função recursivamente para percorrer a subárvore esquerda
    exibeArvoreRB(raiz->esquerda, h + 1);
  }
}

// -=-=-=-=-=- PROGRAMA PRINCIPAL -=-=-=-=-=-
int main() {
  struct NoRB *raiz = NULL; // Alocando espaço para a raiz/árvore

  int opcao, valor;
  do {
    printf("\n-=-=-=-=-=- MENU -=-=-=-=-=-=-");
    printf("\n\n[1] Inserir um elemento na árvore");
    printf("\n[2] Procurar um elemento na árvore");
    printf("\n[3] Verificar qual a cor do Nó");
    printf("\n[4] Exibir a árvore");
    printf("\n[0] Sair do programa");
    printf("\n\nDigite a sua opção: ");

    opcao = verificaEntrada();

    switch (opcao) {
    case 1:
      printf("\n-=-=-=-=-=- INSERIR NÓ -=-=-=-=-=-");
      int n = 0;
      printf("\nDigite a quantidade de nós a serem adicionados: ");
      n = verificaEntrada();

      while (n > 0) {
        int num = 0;
        printf("\nDigite um valor: ");
        num = verificaEntrada();
        inserirNo(&raiz, num);
        n--;
      }
      break;

    case 2:
      printf("\n-=-=-=-=-=- PROCURAR NÓ -=-=-=-=-=-");
      printf("\nDigite um valor a ser procurado: ");
      scanf("%i", &valor);
      procurarNo(raiz, valor);
      break;

    case 3:
      printf("\n-=-=-=-=-=- COR DO NÓ -=-=-=-=-=-");
      printf("\nDigite um valor a ser procurado: ");
      scanf("%i", &valor);
      corNo(raiz, valor);
      break;

    case 4:
      printf("\n-=-=-=-=-=- EXIBIR ÁRVORE -=-=-=-=-=-\n");
      exibeArvoreRB(raiz, alturaArvore(raiz));
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
