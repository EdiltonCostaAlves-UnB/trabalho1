#include <errno.h>
#include <signal.h>
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

#include "semaphore.h"

int main() {
  int shmKey = 0x706964;
  int shmId;
  int semaphoreKey = 0x73656d;
  int idsem;
  int execProcdPID;
  struct SharedMem {
    long lastPid;
    int execprocdID;
    int cancelProcID;  // REF#
  };
  struct SharedMem* shmPointer;
  struct KillMsg {
    long pid;
    int kill;
  };

  if ((idsem = semget(semaphoreKey, 1, 0x1ff)) < 0) {
    printf("erro na criacao do semaforo\n");
    exit(1);
  }

  if ((shmId = shmget(shmKey, sizeof(struct SharedMem), 0777)) < 0) {
    printf("execproc\n");
    printf("Error getting shared memory %d!\n", shmKey);
    return 1;
  }
  shmPointer = (struct SharedMem*)shmat(shmId, (char*)0, 0);
  if (shmPointer == (struct SharedMem*)-1) {
    printf("execproc\n");
    printf("Error in attach!\n");
    return 1;
  }
  p_sem(idsem);
  execProcdPID = shmPointer->execprocdID;
  v_sem(idsem);
  kill(execProcdPID, SIGUSR1);

  return 0;
}
