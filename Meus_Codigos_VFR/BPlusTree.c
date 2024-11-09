/*
Aluno: Vinícius Frigulha Ribeiro
CC6N - Estrutura de Dados II
GitHub:
https://github.com/vinifrigulha/Estrutura_Dados_II/blob/main/Meus_Codigos_VFR/BPlusTree.c
*/

// -=-=-=-=-=- BIBLIOTECAS -=-=-=-=-=- //
#include <stdio.h>
#include <stdlib.h>

// -=-=-=-=-=- DEFINIÇÕES DE CONSTANTES -=-=-=-=-=- //
// Ordem da Árvore
#define ORDEM 4

// -=-=-=-=-=- ESTRUTURAS -=-=-=-=-=- //
// Estrutura do nó da árvore B+
struct NoBPlus {
  int numChaves;
  int chaves[2 * ORDEM - 1];
  struct NoBPlus *filhos[2 * ORDEM];
  struct NoBPlus *prox; // Ponteiro para a próxima folha
  int folha;
};

// -=-=-=-=-=- FUNÇÕES AUXILIARES -=-=-=-=-=- //
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
// Função para criar o No
struct NoBPlus *criarNo(int folha) {
  struct NoBPlus *novoNo = (struct NoBPlus *)malloc(sizeof(struct NoBPlus));
  novoNo->folha = folha;
  novoNo->numChaves = 0;
  novoNo->prox = NULL;
  return novoNo;
}

// Função para dividir um nó que atingiu o limite de elementos
void dividirFilho(struct NoBPlus *no, int i, struct NoBPlus *filho) {
  struct NoBPlus *novoNo = criarNo(filho->folha);
  novoNo->numChaves = ORDEM - 1;

  for (int j = 0; j < ORDEM - 1; j++)
    novoNo->chaves[j] = filho->chaves[j + ORDEM];

  if (!filho->folha) {
    for (int j = 0; j < ORDEM; j++)
      novoNo->filhos[j] = filho->filhos[j + ORDEM];
  } else {
    novoNo->prox = filho->prox;
    filho->prox = novoNo;
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

// Função para inserir uma chave em um nó que não está cheio
void inserirNo(struct NoBPlus *no, int chave) {
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

// Inserir uma chave
struct NoBPlus *inserir(struct NoBPlus *raiz, int chave) {
  if (raiz->numChaves == 2 * ORDEM - 1) {
    struct NoBPlus *novoNo = criarNo(0);
    novoNo->filhos[0] = raiz;
    dividirFilho(novoNo, 0, raiz);
    inserirNo(novoNo, chave);
    return novoNo;
  } else {
    inserirNo(raiz, chave);
    return raiz;
  }
}

// Função para excluir um nó
void excluir(struct NoBPlus *raiz, int chave) {
  if (!raiz)
    return;

  int i = 0;
  while (i < raiz->numChaves && raiz->chaves[i] < chave)
    i++;

  if (raiz->folha) {
    if (i < raiz->numChaves && raiz->chaves[i] == chave) {
      printf("Elemento %d foi excluído.\n\n", chave);
      for (int j = i; j < raiz->numChaves - 1; j++)
        raiz->chaves[j] = raiz->chaves[j + 1];
      raiz->numChaves--;
    } else {
      printf("Elemento %d não encontrado.\n\n", chave);
    }
  } else {
    if (i < raiz->numChaves && raiz->chaves[i] == chave)
      i++;
    excluir(raiz->filhos[i], chave);
  }
}

// Função auxiliar para judar no processo de exibir a árvore
void imprimeNivel(struct NoBPlus *no, int nivel) {
  if (!no)
    return;

  for (int i = 0; i < nivel; i++)
    printf("  ");
  for (int i = 0; i < no->numChaves; i++)
    printf("%d ", no->chaves[i]);
  printf("\n");

  if (!no->folha) {
    for (int i = 0; i <= no->numChaves; i++)
      imprimeNivel(no->filhos[i], nivel + 1);
  }
}

// Função para imprimir a árvore
void imprime(struct NoBPlus *raiz) { imprimeNivel(raiz, 0); }

// -=-=-=-=-=- PROGRAMA PRINCIPAL -=-=-=-=-=-
int main() {
  struct NoBPlus *raiz = criarNo(1); // Inicializa a árvore B+

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
      printf("\n-=-=-=-=-=- INSERIR UM ELEMENTO -=-=-=-=-=-\n");
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
      imprime(raiz);
      printf("\n");
      break;

    case 3:
      printf("\n-=-=-=-=-=- EXCLUIR ELEMENTO -=-=-=-=-=-\n");
      printf("\nDigite um valor para excluir: ");
      valor = verificaEntrada();
      excluir(raiz, valor);
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
