#ifndef LIST_H
#define LIST_H

#include <time.h>

typedef struct Lista Lista;

typedef struct Item Item;

/**
 * Estrutura de lista. Dados do processo são transportados ara dentro
 * @param item Item dentro da lista
 * @param right Estrutura da lista do ítem a direita.
 * @param left Estrutura da lista do ítem a esquerda.
 */
struct Lista {
  Item* item;
  Lista* right;
  Lista* left;
};

/**
 * Lista encadeada dinamica.
 * @param length Quantidade de itens da lista.
 * @param first Primeiro item da lista.
 * @param last Último item da lista.
 */
typedef struct {
  unsigned length;
  Lista* first;
  Lista* last;
} ProcessoLista;

/**
 * Informações do processo dentro da lista.
 * @param parent Lista o pai do item.
 * @param nomePrograma Nome do programa.
 * @param pidVirtual Número de identificação virtual.
 * @param pidReal Número de identificação real.
 * @param priority Prioridade de agendamento.
 * @param qtdTime Quantidade de tempo.
 * @param tempoInicio Quantidade de tempo.
 * @param criteria Quantidade de tempo. 
 * @param params Parametros.
 */
struct Item {
  Lista* parent;
  char nomePrograma[30];
  long pidVirtual;
  long pidReal;
  int priority; 
  int qtdTime;  
  struct tm * tempoInicio;
  int criteria;  
  char** params;
};

/**
 * Criar lista dinamica dupla.
 * @return Empty dynamic double linked list of processes.
 */
ProcessoLista* criarListaDinamica();

/**
 * Criando estrutura com todas as informações do processo.
 * @param long Process id number.
 * @param int Priority in scheduler, the lower the faster.
 * @param char Process params vector.
 * @param nomePrograma Process params vector.
 * @param char Process params vector.
 * @return Struct containing info of a process.
 */
Item* createItem(long, int, char nomePrograma[30], char**);

/**
 * Obtem a estrutura do processo.
 * @param list Lista para obter item.
 * @param position Posição do item que se deseja tomar.
 * @return Item na posição da lista ou null se houver falha.
 */
Item* getItem(ProcessoLista*, unsigned);

/**
 * Localizar um item especifico.
 * @param list Lista a ser exibida.
 * @param pid Id de identificação do processo a ser exibido.
 * @return Item encontrado com id ou null se houver falhar.
 */
Item* findItem(ProcessoLista*, int);

/**
 * Coloca uma estrutura da lista para frente da lista.
 * @param list Lista para enviar item.
 * @param item Item a ser colocado na lista.
 */
void pushFront(ProcessoLista*, Item*);

/**
 * Coloca uma estrutura de processo em uma estrutura Lista e empurra para trás de uma lista.
 * @param list Lista para enviar item .
 * @param item Item a ser colocado na lista.
 */
void pushBack(ProcessoLista*, Item*);

/**
 * Puts a process struct into a Lista struct, pushes into a list's position.
 * @param list Lista para enviar item .
 * @param position Posição desejada para inserir item.
 * @param item Item a ser colocado na lista.
 * @return Zero se for sucesso, ou falha.
 */
int insertItem(ProcessoLista*, unsigned, Item*);

/**
 * Pega o primeiro item da lista.
 * @param list Lista a ser exibida.
 * @return Popped item.
 */
Item* popFront(ProcessoLista*);

/**
 * Takes last item from the list.
 * @param list Lista a ser exibida.
 * @return Popped item.
 */
Item* popBack(ProcessoLista*);

/**
 * Takes item in position from the list.
 * @param list Lista a ser exibida.
 * @param position Position of item to be popped.
 * @return Popped item.
 */
Item* popItem(ProcessoLista*, unsigned);

/**
 * Exclui o item da lista.
 * @param list Lista para excluir o item.
 * @param item Item a ser excluído.
 * @return Zero se for sucesso, ou falha.
 */
int deleteItem(ProcessoLista*, Item*);

/**
 * Libera toda a alocação de memória na lista - itens, listas de itens e a própria lista.
 * @param list List para ter seus mallocs liberados.
 */
void freeList(ProcessoLista*);

/**
 * Imprime todos os pids dos processos do primeiro ao último.
 * @param list Lista para ter todos os seus pids impressos.
 */
void printAll(ProcessoLista*);

#endif 
