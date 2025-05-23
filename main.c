#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// definindo contexto
typedef struct Data {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct Registro {
  char nome[50];
  int idade;
  char rg[50];
  Data *entrada;

} Registro;
// definindo Lista dinamica encadeada para cadastar
typedef struct Elista {
  Registro *dados;
  struct Elista *proximo;
} Elista;

typedef struct Lista {
  int qtde;
  Elista *inicio;
} Lista;

// definindo fila para atendimento
typedef struct Efila {
  Registro *dados;
  struct Efila *proximo;
} Efila;

typedef struct Fila {
  Efila *head;
  Efila *tail;
  int qtde;
} Fila;

// definindo struct árvore
typedef struct No {
    Registro *dados;
    struct No *esq;
    struct No *dir;
    struct No *pai;
} No;

typedef struct {
    No *raiz;
    int qtde;
} Arvore;


//definindo heap para atendimento prioritario

typedef struct heap{
Registro *dados[20];
int qtde;
} heap;

 // Definindo pilha

typedef struct Cell {
  struct Cell *anterior;
  struct Cell *proximo;
  Registro *dados;
  int acao;
} Cell;

typedef struct {
  Cell *top;
  int qtde;
} Stack;

// funcoes para lista dinamica encadeada para cadastro

Lista *inicializa_lista() {
  Lista *l = (Lista *)malloc(sizeof(Lista));
  l->inicio = NULL;
  l->qtde = 0;
  return l;
}

void inserir_lista(Lista *l, Registro *dados) {
  Elista *novo = (Elista *)malloc(sizeof(Elista));
  novo->dados = dados;
  novo->proximo = NULL;

  Elista *atual = l->inicio;
  Elista *anterior = NULL;

  // Encontra a posição correta para inserir o novo paciente
  // Ordenando por rg
  // obs : o strcmp verifica se o primeiro é menor que o segundo

  while (atual != NULL && strcmp(atual->dados->rg, dados->rg) < 0) {
    anterior = atual;
    atual = atual->proximo;
  }

  novo->proximo = atual;

  if (anterior == NULL) {
    l->inicio = novo;
  } else {
    anterior->proximo = novo;
  }

  l->qtde++;
  printf("Paciente cadastrado!\n");
}

void remover_paciente(Lista *l) {
  Elista *atual = l->inicio;
  Elista *anterior = NULL;
  char rg[50];
  printf("\nDigite o valor de rg: ");
  fgets(rg ,sizeof(rg), stdin);
  // obs : o strcmp verifica se o primeiro é igual o segundo( esta comparando o
  // rg)
  while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
    anterior = atual;
    atual = atual->proximo;
  }
  if (atual == NULL) {
    return;
  }
  if (anterior == NULL) {
    l->inicio = atual->proximo;
  } else {
    anterior->proximo = atual->proximo;
  }
  free(atual);
}

void mostrar_lista_completa(const Lista *l) {
  Elista *atual = l->inicio;
  printf("Lista completa de pacientes:\n");
  while (atual != NULL) {  
    printf("-------------------------\n");
    printf("RG=%s", atual->dados->rg);
    printf("Nome=%s", atual->dados->nome);
    printf("Idade=%d\n", atual->dados->idade);
    printf("Data de Entrada=%d/%d/%d\n", atual->dados->entrada->dia,
           atual->dados->entrada->mes, atual->dados->entrada->ano);
    atual = atual->proximo;
    printf("-------------------------\n");
  }
  printf("\n");
}

// a funcao vai criar um registro de dados e inserir na lista
void cadastrar_novo_paciente(Lista *l) {
  Registro *novo = (Registro *)malloc(sizeof(Registro));
  novo->entrada = (Data *)malloc(sizeof(Data));
  printf("Digite os valores abaixo para o cadastro do novo paciente: \n");
  printf("\nRG:");
  fgets(novo->rg, sizeof(novo->rg), stdin);
  printf("NOME:");
  fgets(novo->nome, sizeof(novo->nome), stdin);
  printf("IDADE:");
  scanf("%d", &novo->idade);
  printf("DIA DE ENTRADA:");
  scanf("%d", &novo->entrada->dia);
  printf("MÊS DE ENTRADA:");
  scanf("%d", &novo->entrada->mes);
  printf("ANO DE ENTRADA:");
  scanf("%d", &novo->entrada->ano);
  //no final tem que rodar esse fgets para limpar , porque o scanf deixa um \n
  char lixo [10];
  fgets(lixo, sizeof(lixo), stdin);
  // inserir na lista de todos os pacientes:
  inserir_lista(l, novo);
}

void consultar_paciente(Lista *l) {
  // vamos consultar um paciente pelo rg
  char rg[50];
  int encontrado =0;
  printf("Para consultar um paciente digite um valor de rg: \n");
  fgets(rg, sizeof(rg), stdin);
  Elista *atual = l->inicio;
  while (atual != NULL) {
    // comparando o rg do atual com o rg digitado
    if (strcmp(atual->dados->rg, rg) == 0) {
      encontrado =1;
      printf("Paciente encontrado:\n");
      printf("-------------------------\n");
      printf("RG=%s", atual->dados->rg);
      printf("Nome=%s", atual->dados->nome);
      printf("Idade=%d\n", atual->dados->idade);
      printf("Data de Entrada=%d/%d/%d\n", atual->dados->entrada->dia,
             atual->dados->entrada->mes, atual->dados->entrada->ano);
      printf("-------------------------\n");
    }
    if(encontrado==0){
      printf("Paciente não encontrado\n");
    }
    atual = atual->proximo;
  }
  printf("\n");
}

void atualizar_dados_paciente(Lista *l){
// para aatualizar os dados de um paciente vamos apagar e cadastrar de novo
//remover
  Elista *atual = l->inicio;
  Elista *anterior = NULL;
  char rg[50];
  printf("\nDigite o valor de rg: \n ");
  fgets(rg ,sizeof(rg), stdin);
  // obs : o strcmp verifica se o primeiro é igual o segundo(esta comprando o
  // rg)
  while (atual != NULL && strcmp(atual->dados->rg, rg) != 0) {
    anterior = atual;
    atual = atual->proximo;
  }
  if (atual == NULL) {
    return;
  }
  if (anterior == NULL) {
    l->inicio = atual->proximo;
  } else {
    anterior->proximo = atual->proximo;
  }
  free(atual);
//cadastrar de novo
  Registro *novo = (Registro *)malloc(sizeof(Registro));
  novo->entrada = (Data *)malloc(sizeof(Data));
  printf("Digite os valores abaixo para atualizar o cadastro paciente: \n");
  printf("\nRG:");
  fgets(novo->rg, sizeof(novo->rg), stdin);
  printf("NOME:");
  fgets(novo->nome, sizeof(novo->nome), stdin);
  printf("IDADE:");
  scanf("%d", &novo->idade);
  printf("DIA DE ENTRADA:");
  scanf("%d", &novo->entrada->dia);
  printf("MÊS DE ENTRADA:");
  scanf("%d", &novo->entrada->mes);
  printf("ANO DE ENTRADA:");
  scanf("%d", &novo->entrada->ano);
  printf("\n");
  //no final tem que rodar esse fgets para limpar , porque o scanf deixa um \n
  char lixo [10];
  fgets(lixo, sizeof(lixo), stdin);
  // inserir na lista de todos os pacientes:
  inserir_lista(l, novo);
}
//funcoes de pilha

Cell *start_cell(Registro *dados, int acao) {
  Cell *nova = malloc(sizeof(Cell));
  nova->anterior = NULL;
  nova->proximo = NULL;
  nova->dados = dados;
  nova->acao = acao;
  return nova;
}

Stack *start_stack() {
  Stack *stack = malloc(sizeof(Stack));
  stack->qtde = 0;
  stack->top = NULL;
  return stack;
}

void push(Stack *stack, Registro *dados , int acao) {
  Cell *nova = start_cell(dados,acao);
  if (stack->qtde != 0) {
    nova->proximo = stack->top;
    stack->top->anterior = nova;
  }
  stack->top = nova;
  stack->qtde++;
}

void imprimeStack(Stack *stack) {
    Cell *atual = stack->top;
    while (atual != NULL) {
        // Imprimir o RG e a ação
        printf("RG: %s ", atual->dados->rg);
        if (atual->acao == 0){
            printf("Desenfileirado\n");
        }
        if (atual->acao == 1){
            printf("Enfileirado\n");
        }
        atual = atual->proximo;
    }
}
//funcoes de fila

Efila *cria_Efila(char rg[50] , Lista *l){
  Efila *novo = malloc(sizeof(Efila));
  novo->proximo = NULL;
  // encontrar o paciente com esse rg e pegar o os dados dele 
  Elista *atual = l->inicio;
  while (atual != NULL) {
    // comparando o rg do atual com o rg digitado
    if (strcmp(atual->dados->rg, rg) == 0) {
      novo->dados= atual->dados;
    }
    atual = atual->proximo;
  }
  return novo;
}

void pop(Stack *stack , Fila *f, Lista *l) {
  if (stack->qtde > 0) {
    Cell *top = stack->top;
    //pegando os dados e acao para antes de remover
    Registro *dados = stack->top->dados;
    int acao = stack->top->acao;
    stack->top = stack->top->proximo;
    if (stack->top != NULL)
      stack->top->anterior = NULL;
    stack->qtde--;
    //caso a ultima acao seja 0 (desenfileirar) , temos que enfileirar de volta
    if(acao==0){
      //enfileirar:
      //criando Efila
      Efila *novo = malloc(sizeof(Efila));
      novo->proximo = NULL;
      // encontrar o paciente com esse rg e pegar o os dados dele 
      Elista *atual = l->inicio;
      while (atual != NULL) {
        // comparando o rg do atual com o rg da pilha
        if (strcmp(atual->dados->rg, dados->rg) == 0) {
          novo->dados= atual->dados;
        }
        atual = atual->proximo;
      }
      if(f->qtde == 0){
          f->head = novo;
      }
      else{
          f->tail->proximo = novo;
      }
      f->tail = novo;
      f->qtde++;
    }
    //caso a ultima acao seja 1 (enfileirar) , temos que desenfileirar de volta
    if (acao == 1){
      //desenfileirar
      if(f->qtde != 0){
        char temp[50] ;
        Efila *aux = cria_Efila(temp,l);
        Registro *dados = f->head->dados;
        aux = f->head;
        if(f->qtde == 1){
            f->head = NULL;
          f->tail = NULL;
          f->qtde--;
        }
        else{
            f->head = f->head->proximo;
          f->qtde--;
        }
        }
    }
    
  }
  else{
      printf("não há acoes anteriores para desfazer\n");
  }
}
//funcoes para fila de atendimento


Fila *cria_fila(){
  Fila *f = malloc(sizeof(Fila));
  f->head = NULL;
  f->tail = NULL;
  f->qtde = 0;

  return f;
}

//editando ainda

void enfileirar(Fila *f, Lista *l, Stack *stack){
  char rg[50];
  printf("Digite o rg do paciente que deseja enfileirar: ");
  fgets(rg, sizeof(rg), stdin);

  Efila *nova = cria_Efila(rg,l);
  if(f->qtde == 0){
      f->head = nova;
  }
  else{
      f->tail->proximo = nova;
  }
  f->tail = nova;
  f->qtde++;
  
  //adicionar a pilha:
  //encontrar registro com esse rg para colocar na pilha
  Elista *atual = l->inicio;
  while (atual != NULL) {
    // comparando o rg do atual com o rg digitado
    if (strcmp(atual->dados->rg, rg) == 0) {
      //adicionando a pilha
      push(stack, atual->dados, 1);
    }
    atual = atual->proximo;
  }

  
}

void desenfileirar(Fila *f, Lista *l, Stack *stack){
if(f->qtde != 0){
  char temp[50] ;
  Efila *aux = cria_Efila(temp,l);
  Registro *dados = f->head->dados;
  //adicionar a pilha:
  push(stack, dados, 0);
  aux = f->head;
  if(f->qtde == 1){
      f->head = NULL;
    f->tail = NULL;
    f->qtde--;
  }
  else{
      f->head = f->head->proximo;
    f->qtde--;
  }
  }
}

void mostrar_fila (Fila *f){
  Efila *atual = f->head;
    while(atual != NULL){
      printf("Fila de pacientes:\n");
      while (atual != NULL) {  
        printf("-------------------------\n");
        printf("RG=%s", atual->dados->rg);
        printf("Nome=%s", atual->dados->nome);
        printf("Idade=%d\n", atual->dados->idade);
        printf("Data de Entrada=%d/%d/%d\n", atual->dados->entrada->dia,
               atual->dados->entrada->mes, atual->dados->entrada->ano);
        atual = atual->proximo;
        printf("-------------------------\n");
      }
      printf("\n");
    }
  printf("\n");
}

// funcoes para heap de atendimento prioritario

int filho_esq(int pai) {
return 2*pai+1;
}

int filho_dir(int pai) {
return 2*pai+2;
}

int pai(int filho) {
return (filho-1)/2;
}

int ultimo_pai(heap *h) {
return (h->qtde-2)/2;

}

void peneirar(heap *h, int pai) {
int maior = pai;
int filho_esquerdo = filho_esq(pai);
int filho_direito = filho_dir(pai);
if (filho_esquerdo < h->qtde && h->dados[filho_esquerdo]->idade > h->dados[maior]->idade){
maior = filho_esquerdo;

}
if (filho_direito < h->qtde && h->dados[filho_direito]->idade > h->dados[maior]->idade){
maior = filho_direito;
}
if (maior != pai){
Registro *aux = h->dados[pai];
h->dados[pai]= h->dados[maior];
h->dados[maior] = aux;
peneirar(h, maior);
}
}

void mostrar(heap *h) {
  printf("Fila de pacientes preferenciais:\n");
  for (int i = 0; i < h->qtde; i++) {
    printf("-------------------------\n");
    printf("RG=%s", h->dados[i]->rg);
    printf("Nome=%s", h->dados[i]->nome);
    printf("Idade=%d\n", h->dados[i]->idade);
    printf("Data de Entrada=%d/%d/%d\n", h->dados[i]->entrada->dia,
      h->dados[i]->entrada->mes, h->dados[i]->entrada->ano);
    printf("-------------------------\n");
}
printf("\n");
}

void construir(heap *h) {
for (int i = ultimo_pai(h); i >= 0; i--){
peneirar(h, i);
}
}


void inserir(heap *h, Lista *l) {
  char rg[50];
  printf("\nDigite o rg do paciente preferencial: ");
  fgets(rg, sizeof(rg), stdin);
  Elista *atual = l->inicio;
  while (atual != NULL) {
    if (strcmp(atual->dados->rg, rg) == 0) {
      h->dados[h->qtde] = atual->dados;
      h->qtde++;
      peneirar(h, pai(h->qtde - 1));
    }
    atual = atual->proximo;
  }
}


void remover(heap *h) {
// implementar
h->dados[0] = h->dados[h->qtde-1];
h->qtde--;
construir(h);
return;
}

//salvando a lista em um txt
void salvar(Lista *l) {

    FILE *arquivo = fopen("lista.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }

// escrevendo um dado por linha de todos os membros da lista
  Elista *atual = l->inicio;
  while (atual != NULL) {
    fprintf(arquivo, "%s", atual->dados->nome); 
    fprintf(arquivo, "%d\n", atual->dados->idade);
    fprintf(arquivo, "%s", atual->dados->rg);
    fprintf(arquivo, "%d\n", atual->dados->entrada->dia);
    fprintf(arquivo, "%d\n", atual->dados->entrada->mes);
    fprintf(arquivo, "%d\n", atual->dados->entrada->ano);
    atual = atual->proximo;
  }
    fclose(arquivo);
    printf("Lista salva com sucesso!\n");

}

//função árvore binária de busca
No *cria_no(Registro *dados) {
  No *vertice = (No *)malloc(sizeof(No));
  vertice->dados = dados;
  vertice->esq = NULL;
  vertice->dir = NULL;
  vertice->pai = NULL;
  return vertice;
}

Arvore *cria_arvore() {
  Arvore *arvore = (Arvore *)malloc(sizeof(Arvore));
  arvore->raiz = NULL;
  arvore->qtde = 0;
  return arvore;
}

// função inserir por ano inicialmente
No *inserir_arvore(No *vertice, Registro *dados) {
    if (vertice == NULL) {
        return cria_no(dados);
    }
    if (dados->entrada->ano < vertice->dados->entrada->ano) {
      vertice->esq = inserir_arvore(vertice->esq, dados);
  } else {
      vertice->dir = inserir_arvore(vertice->dir, dados);
  }

    return vertice;
}

// função inserir por mes inicialmente
No *inserir_por_mes(No *vertice, Registro *dados) {
    if (vertice == NULL) {
        return cria_no(dados);
    }
    if (dados->entrada->mes < vertice->dados->entrada->mes) {
        vertice->esq = inserir_por_mes(vertice->esq, dados);
    } else {
        vertice->dir = inserir_por_mes(vertice->dir, dados);
    }
    return vertice;
}

// função inserir por dia inicialmente
No *inserir_por_dia(No *vertice, Registro *dados) {
    if (vertice == NULL) {
        return cria_no(dados);
    }
    if (dados->entrada->dia < vertice->dados->entrada->dia) {
        vertice->esq = inserir_por_dia(vertice->esq, dados);
    } else {
        vertice->dir = inserir_por_dia(vertice->dir, dados);
    }
    return vertice;
}

// função inserir por idade inicialmente
No *inserir_por_idade(No *vertice, Registro *dados) {
    if (vertice == NULL) {
        return cria_no(dados);
    }
    if (dados->idade < vertice->dados->idade) {
        vertice->esq = inserir_por_idade(vertice->esq, dados);
    } else {
        vertice->dir = inserir_por_idade(vertice->dir, dados);
    }
    return vertice;
}


// mostrar árvore em ordem
void in_order(No *raiz) {
  if (raiz != NULL) {
      in_order(raiz->esq);
      printf("-------------------------\n");
      printf("Paciente: %s", raiz->dados->nome);
      printf("Idade: %d\n", raiz->dados->idade);
      printf("Data de Entrada: %d/%d/%d\n", raiz->dados->entrada->dia, raiz->dados->entrada->mes, raiz->dados->entrada->ano);
      printf("-------------------------\n");
      in_order(raiz->dir);
  }
}

// funções para carregar a lista na árvore(ordenado)
void carregar_lista_na_arvore_por_ano(Lista *l, Arvore *a) {
  Elista *atual = l->inicio;
  while (atual != NULL) {
      a->raiz = inserir_arvore(a->raiz, atual->dados);
      atual = atual->proximo;
  }
}

void carregar_lista_na_arvore_por_mes(Lista *l, Arvore *a) {
  Elista *atual = l->inicio;
  while (atual != NULL) {
      a->raiz = inserir_por_mes(a->raiz, atual->dados);
      atual = atual->proximo;
  }
}

void carregar_lista_na_arvore_por_dia(Lista *l, Arvore *a) {
  Elista *atual = l->inicio;
  while (atual != NULL) {
      a->raiz = inserir_por_dia(a->raiz, atual->dados);
      atual = atual->proximo;
  }
}

void carregar_lista_na_arvore_por_idade(Lista *l, Arvore *a) {
  Elista *atual = l->inicio;
  while (atual != NULL) {
      a->raiz = inserir_por_idade(a->raiz, atual->dados);
      atual = atual->proximo;
  }
}




//função para carregar os arquivos
void carregar(Lista *l) {
  FILE *arquivo = fopen("lista.txt", "r");
  if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo para leitura.\n");
      return;
  }

  while (!feof(arquivo)) {
      Registro *novo = (Registro *)malloc(sizeof(Registro));
      novo->entrada = (Data *)malloc(sizeof(Data));

      if (fgets(novo->nome, sizeof(novo->nome), arquivo) == NULL) break;
      fscanf(arquivo, "%d\n", &novo->idade);
      if (fgets(novo->rg, sizeof(novo->rg), arquivo) == NULL) break;
      fscanf(arquivo, "%d\n", &novo->entrada->dia);
      fscanf(arquivo, "%d\n", &novo->entrada->mes);
      fscanf(arquivo, "%d\n", &novo->entrada->ano);

      inserir_lista(l, novo);
  }

  fclose(arquivo);
  printf("Lista carregada com sucesso!\n");
}


//main
int main(void) {
  setlocale(LC_ALL, "Portuguese_Brazil");
  Lista *l = inicializa_lista();
  Fila *f = cria_fila();
  heap *h = malloc(sizeof(heap));
  //criando pilha , a 1 é para o rg e a 2 é para a acao
  Stack *stack1 = start_stack();
  h->qtde = 0;
  while (1){
    printf("\n////////////////////////////////\n");
    printf("--------------MENU--------------\n");
    printf("1-Cadastrar\n2-Atendimento\n3-Atendimento prioritário\n4-Pesquisa\n6-Salvar\n7-Carregar\n8-Desfazer\n9-Sobre\n10-Sair\n////////////////////////////////\n\n");
    int menu;
    printf("Opção: ");
    scanf("%d",&menu);
    if(menu==1){
      int cadastrar;
      printf("\n////////////////////////////////\n");
      printf("------------CADASTRO------------\n");
      printf("1-Cadastrar novo paciente\n2-Consultar paciente cadastrado\n3-Mostrar lista completa\n4-Atualizar dados de paciente\n5-Remover paciente\n6-Voltar\n////////////////////////////////\n\n");
      printf("Opção: ");
      scanf("%d",&cadastrar);
      //tem que rodar esse fgets para limpar , porque o scanf deixa um \n
      char lixo [10];
      fgets(lixo, sizeof(lixo), stdin);

      if (cadastrar==1){cadastrar_novo_paciente(l);}
      else if (cadastrar == 2){consultar_paciente(l);}
      else if (cadastrar ==3){mostrar_lista_completa(l);}
      else if (cadastrar==4){atualizar_dados_paciente(l);}
      else if (cadastrar==5){remover_paciente(l);}
      else if (cadastrar==6){continue;}
    }
    if(menu==2){
      int atendimento;
      printf("\n////////////////////////////////\n");
      printf("----------ATENDIMENTO-----------\n");
      printf("1-Enfileirar paciente\n2-Desenfileirar paciente\n3-Mostrar fila\n4-Voltar\n////////////////////////////////\n\n");
      printf("Opção: ");
      scanf("%d",&atendimento);
      //tem que rodar esse fgets para limpar , porque o scanf deixa um \n
      char lixo [10];
      fgets(lixo, sizeof(lixo), stdin);

      if (atendimento==1){enfileirar(f,l,stack1);}
      else if (atendimento == 2){desenfileirar(f,l,stack1);}
      else if (atendimento ==3){mostrar_fila(f);}
      else if (atendimento==4){continue;}

    }
    if(menu==3){
      int atendimento_prioritario;
      printf("\n////////////////////////////////\n");
      printf("----ATENDIMENTO PRIORITÁRIO----\n");
      printf("1-Enfileirar paciente\n2-Desenfileirar paciente\n3-Mostrar fila\n4-Voltar\n////////////////////////////////\n\n");
      printf("Opção: ");
      scanf("%d",&atendimento_prioritario);
      //tem que rodar esse fgets para limpar , porque o scanf deixa um \n
      char lixo [10];
      fgets(lixo, sizeof(lixo), stdin);
      //variavel para salvar os dados do paciente que foi inserido ou retirado na fila

      if (atendimento_prioritario==1){inserir(h,l);}
      else if (atendimento_prioritario == 2){remover(h);}
      else if (atendimento_prioritario ==3){mostrar(h);}
      else if (atendimento_prioritario==4){continue;}

    }
    //pesquisa
    if (menu == 4) {
        int pesquisa;
        printf("\n////////////////////////////////\n");
        printf("------------PESQUISA------------\n");
        printf("1-Ordenar por ano\n2-Ordenar por mês\n3-Ordenar por dia\n4-Ordenar por idade\n5-Voltar\n////////////////////////////////\n\n");
        printf("Opção: ");
        scanf("%d", &pesquisa);
        // limpar buffer
        char lixo[10];
        fgets(lixo, sizeof(lixo), stdin);

        Arvore *a = cria_arvore();
        if (pesquisa == 1) {
            carregar_lista_na_arvore_por_ano(l, a);
            printf("\nPacientes ordenados por ano de entrada:\n");
        }
        else if (pesquisa == 2) {
            carregar_lista_na_arvore_por_mes(l, a);
            printf("\nPacientes ordenados por mês de entrada:\n");
        }
        else if (pesquisa == 3) {
            carregar_lista_na_arvore_por_dia(l, a);
            printf("\nPacientes ordenados por dia de entrada:\n");
        }
        else if (pesquisa == 4) {
            carregar_lista_na_arvore_por_idade(l, a);
            printf("\nPacientes ordenados por idade:\n");
        }
        else if (pesquisa == 5){
            continue;
        }
        in_order(a->raiz);
    }

    if(menu==6){salvar(l);}
    if(menu==7){carregar(l);}
    if(menu==8){
      imprimeStack(stack1);
      printf("\nDeseja desfazer a ultima operação?\n1-Sim\n2-Não\n\n");
      printf("Opção: ");
      int sn;
      scanf("%d", &sn);
      // limpar buffer
      char lixo[10];
      fgets(lixo, sizeof(lixo), stdin);
      if(sn==1)
      {
        pop(stack1,f,l);
      }

      
    }

    if(menu==9){
      printf("\n///////////////////////////////////////////\n");
      printf("-------------------SOBRE-------------------\n");
      printf("\nTrabalho de Estrutura de Dados\n");
      printf("\n-------------------ALUNOS------------------\n\n");
      printf("Henrique Ciola Marino\n");
      printf("Natália Kelch Monteiro\n");
      printf("\n------------CICLO-E-DISCIPLINA-------------\n\n");
      printf("Estrutura de Dados e Análise de Algoritimos\n");
      printf("Engenharia de Automação e Controle\n");
      printf("7º Ciclo\n");
      printf("\n09/05/2025\n");
      printf("///////////////////////////////////////////\n\n\n");
    }
    if(menu==10){break;}
  }
  return 0;
}