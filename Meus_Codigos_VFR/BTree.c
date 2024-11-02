/*
Aluno: Vinícius Frigulha Ribeiro
CC6N - Estrutura de Dados II
GitHub:
https://github.com/vinifrigulha/Estrutura_Dados_II/blob/main/Meus_Codigos_VFR/BTree.c
*/

// -=-=-=-=-=- BIBLIOTECAS -=-=-=-=-=- //
#include <stdio.h>
#include <stdlib.h>

// -=-=-=-=-=- DEFINIÇÕES DE CONSTANTES -=-=-=-=-=- //
// Ordem da Árvore
#define ORDEM 3

// -=-=-=-=-=- ESTRUTURAS -=-=-=-=-=- //
// Estrutura do nó da árvore B
struct NoB {
  int numChaves;
  int chaves[2 * ORDEM - 1];
  struct NoB *filhos[2 * ORDEM];
  int folha;
};

// -=-=-=-=-=- FUNÇÕES AUXILIARES -=-=-=-=-=- //

// Função para verificar se o valor de entrada é inteiro
int verificaEntrada() {
  int ehValido, valor;
  while (1) {
    ehValido = scanf("%i", &valor);
    if (ehValido == 1) {
      if (valor < 0) {
        printf("\nValor inválido.\nTente novamente: ");
        while (getchar() != '\n')
          ;
      } else {
        break;
      }
    } else {
      printf("\nValor inválido.\nTente novamente: ");
      while (getchar() != '\n')
        ;
    }
  }
  return valor;
}

// -=-=-=-=-=- FUNÇÕES DO PROGRAMA -=-=-=-=-=- //

// Cria um novo nó
struct NoB *criarNo(int folha) {
  struct NoB *novoNo = (struct NoB *)malloc(sizeof(struct NoB));
  novoNo->folha = folha;
  novoNo->numChaves = 0;
  return novoNo;
}

// Divide o filho de um nó
void dividirFilho(struct NoB *no, int i, struct NoB *filho) {
  struct NoB *novoNo = criarNo(filho->folha);
  novoNo->numChaves = ORDEM - 1;

  for (int j = 0; j < ORDEM - 1; j++)
    novoNo->chaves[j] = filho->chaves[j + ORDEM];

  if (!filho->folha) {
    for (int j = 0; j < ORDEM; j++)
      novoNo->filhos[j] = filho->filhos[j + ORDEM];
  }

  filho->numChaves = ORDEM - 1;

  for (int j = no->numChaves; j >= i + 1; j--)
    no->filhos[j + 1] = no->filhos[j];

  no->filhos[i + 1] = novoNo;

  for (int j = no->numChaves - 1; j >= i; j--)
    no->chaves[j + 1] = no->chaves[j];

  no->chaves[i] = filho->chaves[ORDEM - 1];
  no->numChaves++;
}

// Insere uma chave no nó
void inserirNo(struct NoB *no, int chave) {
  int i = no->numChaves - 1;

  if (no->folha) {
    while (i >= 0 && chave < no->chaves[i]) {
      no->chaves[i + 1] = no->chaves[i];
      i--;
    }
    no->chaves[i + 1] = chave;
    no->numChaves++;
  } else {
    while (i >= 0 && chave < no->chaves[i])
      i--;

    if (no->filhos[i + 1]->numChaves == 2 * ORDEM - 1) {
      dividirFilho(no, i + 1, no->filhos[i + 1]);
      if (chave > no->chaves[i + 1])
        i++;
    }
    inserirNo(no->filhos[i + 1], chave);
  }
}

// Insere uma chave na árvore B
struct NoB *inserir(struct NoB *raiz, int chave) {
  if (raiz->numChaves == 2 * ORDEM - 1) {
    struct NoB *novoNo = criarNo(0);
    novoNo->filhos[0] = raiz;
    dividirFilho(novoNo, 0, raiz);
    inserirNo(novoNo, chave);
    return novoNo;
  } else {
    inserirNo(raiz, chave);
    return raiz;
  }
}

// Função para obter o predecessor de uma chave
int obterPredecessor(struct NoB *no) {
  while (!no->folha)
    no = no->filhos[no->numChaves];
  return no->chaves[no->numChaves - 1];
}

// Preenche o nó filho com uma chave
void preencher(struct NoB *no, int idx) {
  struct NoB *filho = no->filhos[idx];
  struct NoB *filhoAnterior = no->filhos[idx - 1];

  // Move uma chave do nó pai para baixo
  for (int j = filho->numChaves - 1; j >= 0; j--)
    filho->chaves[j + 1] = filho->chaves[j];

  if (!filho->folha) {
    for (int j = filho->numChaves; j >= 0; j--)
      filho->filhos[j + 1] = filho->filhos[j];
  }

  filho->chaves[0] = no->chaves[idx - 1];
  if (!filho->folha)
    filho->filhos[0] = filhoAnterior->filhos[filhoAnterior->numChaves];

  no->chaves[idx - 1] = filhoAnterior->chaves[filhoAnterior->numChaves - 1];
  filhoAnterior->numChaves--;

  filho->numChaves++;
}

// Une dois nós filhos
void unir(struct NoB *no, int idx) {
  struct NoB *filho = no->filhos[idx];
  struct NoB *filhoAnterior = no->filhos[idx - 1];

  filhoAnterior->chaves[filhoAnterior->numChaves] = no->chaves[idx - 1];

  for (int j = 0; j < filho->numChaves; j++)
    filhoAnterior->chaves[j + 1] = filho->chaves[j];

  if (!filho->folha) {
    for (int j = 0; j <= filho->numChaves; j++)
      filhoAnterior->filhos[j + filhoAnterior->numChaves + 1] =
          filho->filhos[j];
  }

  filhoAnterior->numChaves += filho->numChaves + 1;
  for (int j = idx; j < no->numChaves; j++)
    no->chaves[j - 1] = no->chaves[j];

  for (int j = idx + 1; j <= no->numChaves; j++)
    no->filhos[j - 1] = no->filhos[j];

  no->numChaves--;
}

// Exclui uma chave da árvore B
struct NoB *excluir(struct NoB *raiz, int chave) {
  if (!raiz) {
    printf("Elemento %d não encontrado.\n\n", chave);
    return NULL;
  }

  int index = 0;
  while (index < raiz->numChaves && chave > raiz->chaves[index])
    index++;

  // Se a chave está presente neste nó
  if (index < raiz->numChaves && chave == raiz->chaves[index]) {
    // Se é uma folha, removemos a chave
    if (raiz->folha) {
      for (int j = index + 1; j < raiz->numChaves; j++)
        raiz->chaves[j - 1] = raiz->chaves[j];
      raiz->numChaves--;
    } else {
      // Se não é uma folha, encontramos o predecessor
      int chavePredecessor = obterPredecessor(raiz->filhos[index]);
      raiz->chaves[index] = chavePredecessor;
      raiz->filhos[index] = excluir(raiz->filhos[index], chavePredecessor);
    }
  } else {
    // Se não é uma folha
    if (raiz->folha) {
      printf("Elemento %d não encontrado.\n\n", chave);
      return NULL;
    }

    // Se o nó filho tem menos chaves que a ORDEM, ele prenche
    if (raiz->filhos[index]->numChaves < ORDEM) {
      if (index != 0 && raiz->filhos[index - 1]->numChaves >= ORDEM)
        preencher(raiz, index);
      else if (index != raiz->numChaves &&
               raiz->filhos[index + 1]->numChaves >= ORDEM)
        preencher(raiz, index + 1);
      else {
        if (index != raiz->numChaves)
          unir(raiz, index);
        else
          unir(raiz, index - 1);
      }
    }

    raiz->filhos[index] = excluir(raiz->filhos[index], chave);
  }

  return raiz;
}

// Função para imprimir cada nível da árvore B
void imprimeNivel(struct NoB *no, int nivel) {
  if (no == NULL)
    return;

  for (int i = 0; i < nivel; i++)
    printf("  "); // Indentação para cada nível
  for (int i = 0; i < no->numChaves; i++)
    printf("%d ", no->chaves[i]);
  printf("\n");

  if (!no->folha) {
    for (int i = 0; i <= no->numChaves; i++) {
      imprimeNivel(no->filhos[i], nivel + 1);
    }
  }
}

// Função para exibir a árvore completa em diferentes níveis
void imprime(struct NoB *raiz) { imprimeNivel(raiz, 0); }

// -=-=-=-=-=- PROGRAMA PRINCIPAL -=-=-=-=-=-
int main() {
  struct NoB *raiz = criarNo(1); // Inicializa a árvore B

  int opcao, valor;
  do {
    printf("\n-=-=-=-=-=- MENU -=-=-=-=-=-=-");
    printf("\n\n[1] Inserir um elemento na árvore");
    printf("\n[2] Exibir a árvore");
    printf("\n[3] Excluir um elemento da árvore");
    printf("\n[0] Sair do programa");
    printf("\n\nDigite a sua opção: ");

    opcao = verificaEntrada();

    switch (opcao) {
    case 1:
      printf("\n-=-=-=-=-=- INSERIR ELEMENTO -=-=-=-=-=-");
      printf("\nDigite a quantidade de elementos a serem adicionados: ");
      int n = verificaEntrada();

      while (n > 0) {
        printf("\nDigite um valor: ");
        valor = verificaEntrada();
        raiz = inserir(raiz, valor);
        n--;
      }
      break;

    case 2:
      printf("\n-=-=-=-=-=- EXIBIR ÁRVORE -=-=-=-=-=-\n");
      imprime(raiz); // Exibe a árvore usando a função imprime
      printf("\n");
      break;

    case 3:
      printf("\nDigite um valor para excluir: ");
      valor = verificaEntrada();
      raiz = excluir(raiz, valor);
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
