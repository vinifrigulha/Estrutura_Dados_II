/*
Aluno: Vinícius Frigulha Ribeiro
CC6N - Estrutura de Dados II
GitHub:
https://github.com/vinifrigulha/Estrutura_Dados_II/blob/main/Meus_Codigos_VFR/AVL.c
*/

// -=-=-=-=-=- BIBLIOTECAS -=-=-=-=-=-
#include <stdio.h>
#include <stdlib.h>

// -=-=-=-=-=- ESTRUTURAS -=-=-=-=-=-
struct NoAVL {
  int valor;
  struct NoAVL *esquerda;
  struct NoAVL *direita;
  int altura;
};

// -=-=-=-=-=- FUNÇÕES AUXILIARES -=-=-=-=-=-
// Função auxiliar para encontrar o valor mínimo entre os nós de uma raiz
struct NoAVL *encontrarMinimo(struct NoAVL *raiz) {
  struct NoAVL *atual = raiz;
  while (atual->esquerda != NULL) {
    atual = atual->esquerda;
  }
  return atual;
}

// Função auxiliar para encontrar o valor máximo do nó mais à direita do lado
// equerdo
struct NoAVL *encontrarMaximo(struct NoAVL *raiz) {
  struct NoAVL *atual = raiz;
  while (atual->direita != NULL) {
    atual = atual->direita;
  }
  return atual;
}

// Função auxiliar para exibir a árvore PRE-ORDER:
void preOrder(struct NoAVL *raiz) {
  if (raiz != NULL) {
    printf("%i ", raiz->valor);
    preOrder(raiz->esquerda);
    preOrder(raiz->direita);
  }
}

// Função auxiliar para exibir a árvore IN-ORDER:
void inOrder(struct NoAVL *raiz) {
  if (raiz != NULL) {
    inOrder(raiz->esquerda);
    printf("%i ", raiz->valor);
    inOrder(raiz->direita);
  }
}

// Função auxiliar para exibir a árvore POS-ORDER:
void posOrder(struct NoAVL *raiz) {
  if (raiz != NULL) {
    posOrder(raiz->esquerda);
    posOrder(raiz->direita);
    printf("%i ", raiz->valor);
  }
}

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

// Função para indicar o fator de balanceamento
int fatorBalanceamento(struct NoAVL *no) {
  if (no == NULL) {
    return 0;
  }
  return no->esquerda->altura - no->direita->altura;
}

// -=-=-=-=-=- FUNÇÕES DO PROGRAMA -=-=-=-=-=-
// Função para criar um novo Nó
struct NoAVL *criarNo(int valor) {
  struct NoAVL *novoNo = (struct NoAVL *)malloc(sizeof(struct NoAVL));
  if (novoNo == NULL) // Verificando se a raiz é NULL
  {
    printf("Erro ao alocar o Nó\n\n");
    exit(-1);
  }
  novoNo->valor = valor;
  novoNo->direita = NULL;
  novoNo->esquerda = NULL;
  novoNo->altura = 0;
  return novoNo;
}

// Função para realizar a RSD (Rotação Simples Direita)
struct NoAVL *rotacaoDireita(struct NoAVL *no) {
  struct NoAVL *novaRaiz = no->esquerda;
  struct NoAVL *subArvore = novaRaiz->direita;

  // Faz a RSD
  novaRaiz->direita = no;
  no->esquerda = subArvore;

  // Atualiza as alturas
  if (no->esquerda->altura > no->direita->altura) {
    no->altura = no->esquerda->altura + 1;
  } else {
    no->altura = no->direita->altura + 1;
  }

  if (novaRaiz->esquerda->altura > novaRaiz->direita->altura) {
    novaRaiz->altura = novaRaiz->esquerda->altura + 1;
  } else {
    novaRaiz->altura = novaRaiz->direita->altura + 1;
  }

  return novaRaiz;
}

// Função para realizar a RSE (Rotação Simples Esquerda)
struct NoAVL *rotacaoEsquerda(struct NoAVL *no) {
  struct NoAVL *novaRaiz = no->direita;
  struct NoAVL *subArvore = novaRaiz->esquerda;

  // Faz a RSE
  novaRaiz->esquerda = no;
  no->direita = subArvore;

  // Atualiza as alturas
  if (no->esquerda->altura > no->direita->altura) {
    no->altura = no->esquerda->altura + 1;
  } else {
    no->altura = no->direita->altura + 1;
  }

  if (novaRaiz->esquerda->altura > novaRaiz->direita->altura) {
    novaRaiz->altura = novaRaiz->esquerda->altura + 1;
  } else {
    novaRaiz->altura = novaRaiz->direita->altura + 1;
  }

  return novaRaiz;
}

// Função para balancear a árvore
struct NoAVL *balancearArvore(struct NoAVL *raiz, int dado) {
  // Atualiza a altura do nó atual
  if (raiz == NULL) {
    return raiz;
  }
  if (raiz->esquerda->altura > raiz->direita->altura) {
    raiz->altura = raiz->esquerda->altura + 1;
  } else {
    raiz->altura = raiz->direita->altura + 1;
  }

  // Calcula o fator de balanceamento deste nó para verificar se ele se tornou
  // desbalanceado
  int balanceamento = fatorBalanceamento(raiz);

  // Caso de desbalanceamento à esquerda-esquerda
  if (balanceamento > 1 && dado < raiz->esquerda->valor) {
    return rotacaoDireita(raiz);
  }

  // Caso de desbalanceamento à direita-direita
  if (balanceamento < -1 && dado > raiz->direita->valor) {
    return rotacaoEsquerda(raiz);
  }

  // Caso de desbalanceamento à esquerda-direita
  if (balanceamento > 1 && dado > raiz->esquerda->valor) {
    raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
    return rotacaoDireita(raiz);
  }

  // Caso de desbalanceamento à direita-esquerda
  if (balanceamento < -1 && dado < raiz->direita->valor) {
    raiz->direita = rotacaoDireita(raiz->direita);
    return rotacaoEsquerda(raiz);
  }

  return raiz;
}

// Função para inserir um novo Nó
struct NoAVL *inserirNo(struct NoAVL *raiz, int valor) {
  if (raiz == NULL) // Verificando se a raiz é NULL
  {
    return criarNo(valor);
  } else {
    if (valor < raiz->valor) {
      raiz->esquerda = inserirNo(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
      raiz->direita = inserirNo(raiz->direita, valor);
    } else {
      return raiz; // Não podem ter entradas iguais na árvore
    }
  }
  return balancearArvore(raiz, valor);
}

// Função para procurar um Nó
void procurarNo(struct NoAVL *raiz, int valor) {
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
struct NoAVL *excluirNo(struct NoAVL *raiz, int valor) {
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
      struct NoAVL *temp = raiz->direita;
      printf("Elemento %d excluído\n\n", valor);
      return temp;
    } else if (raiz->direita == NULL) {
      struct NoAVL *temp = raiz->esquerda;
      printf("Elemento %d excluído\n\n", valor);
      return temp;
    }

    // 2º Caso: Nó com dois filhos
    if (raiz->esquerda->altura >= raiz->direita->altura) {
      struct NoAVL *temp = encontrarMinimo(raiz->direita);
      raiz->valor = temp->valor;
      raiz->esquerda = excluirNo(raiz->esquerda, temp->valor);
    } else {
      struct NoAVL *temp = encontrarMinimo(raiz->esquerda);
      raiz->valor = temp->valor;
      raiz->direita = excluirNo(raiz->direita, temp->valor);
    }
  }
  return balancearArvore(raiz, valor);
}

// Função para calcular a altura da árvore
int alturaArvore(struct NoAVL *raiz) {
  if (raiz == NULL) {
    return -1;
  }

  int alturaEsquerda = alturaArvore(raiz->esquerda) + 1;
  int alturaDireita = alturaArvore(raiz->direita) + 1;

  if (alturaDireita < alturaEsquerda) {
    return alturaEsquerda;
  } else {
    return alturaDireita;
  }
}

// -=-=-=-=-=- PROGRAMA PRINCIPAL -=-=-=-=-=-
int main() {
  struct NoAVL *raiz = NULL; // Alocando espaço para a raiz/árvore

  int opcao, valor;
  do {
    printf("\n-=-=-=-=-=- MENU -=-=-=-=-=-=-");
    printf("\n\n[1] Inserir um elemento na árvore");
    printf("\n[2] Procurar um elemento na árvore");
    printf("\n[3] Excluir um elemento da árvore");
    printf("\n[4] Calcular a altura da árvore");
    printf("\n[5] Exibir a árvore");
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
        raiz = inserirNo(raiz, num);
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
      printf("\n-=-=-=-=-=- EXCLUIR NÓ -=-=-=-=-=-");
      printf("\nDigite um valor a ser excluído: ");
      scanf("%i", &valor);
      raiz = excluirNo(raiz, valor);
      break;

    case 4:
      printf("\n-=-=-=-=-=- ALTURA DA ÁRVORE -=-=-=-=-=-");
      int altura = alturaArvore(raiz);
      printf("\nA altura da árvore é: %i", altura);
      break;

    case 5:
      printf("\n-=-=-=-=-=- EXIBIR ÁRVORE -=-=-=-=-=-\n");
      printf("\nPRE-ORDER: ");
      preOrder(raiz);

      printf("\nIN-ORDER: ");
      inOrder(raiz);

      printf("\nPOS-ORDER: ");
      posOrder(raiz);
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
