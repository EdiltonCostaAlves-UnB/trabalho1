#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "lista.h"
#include "semaphore.h"

int main(int argc, char *argv[]) {
  int pid;
  int idFila;
  int chaveSHM = 0x706964;
  int chaveFila = 0x70726F63;
  int IdSHM;
  int semaphoreKey = 0x73656d;
  int idsem;
  struct MemoriaCompartilhada {
    long ultimoID;
    int ProcessoExecutadodID;
    int ProcessoCanceladoID;
  };
  struct MemoriaCompartilhada *shmPointer;
  struct ConteudoMensagem {
    char nomePrograma[30];
    long pidVirtual;
    int priority;
  };
  struct Mensagem {
    long type;
    struct ConteudoMensagem conteudoMensagem;
  };
  struct Mensagem mensagem;

  if (argc < 3) {
    printf("Processo Executado\n");
    printf("Erro - argumentos menor que 3!\n");
    printf("O nome e prioridade são necessários:\n");
    printf("  ./Processo Executado <nomeProcesso> <prioridade> <arg1> <arg2>...\n");
    return 1;
  }

  if ((idsem = semget(semaphoreKey, 1, 0x1ff)) < 0) {
    printf("Erro de semaforo\n");
    exit(1);
  }

  if ((IdSHM = shmget(chaveSHM, sizeof(struct MemoriaCompartilhada), 0x1ff)) < 0) {
    printf("Processo Executado\n");
    printf("Erro ao obter memória compartilhada %d!\n", chaveSHM);
    return 1;
  }
  shmPointer = (struct MemoriaCompartilhada *)shmat(IdSHM, (char *)0, 0);
  if (shmPointer == (struct MemoriaCompartilhada *)-1) {
    printf("Processo Executado\n");
    printf("Erro ao anexar!\n");
    return 1;
  }

  p_sem(idsem);
  pid = shmPointer->lastPid;
  shmPointer->lastPid = pid + 1;
  v_sem(idsem);

  // Obter lista do processo
  if ((idFila = msgget(chaveFila, 0777)) < 0) {
    printf("Processo Executado:\n");
    printf("Erro ao obter fila %d!\n", chaveFila);
    return 1;
  }

  mensagem.type = 1;
  mensagem.conteudoMensagem.pidVirtual = pid;
  mensagem.conteudoMensagem.priority = atoi(argv[2]);
  strcpy(mensagem.conteudoMensagem.nomePrograma, argv[1]);

  // Enviar requisição
  if (msgsnd(idFila, &mensagem, sizeof(mensagem) - sizeof(long), 0) == -1)
    printf("Erro ao enviar");

  shmdt(shmPointer);

  return 0;
}
