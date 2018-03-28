#ifndef COMMANDE_H
#define COMMANDE_H

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

struct cmdBg{
    int numero;
    pid_t pid;
};

struct cmdBgCell{
    struct cmdBgCell* prev;
    struct cmdBg cmd;
    struct cmdBgCell* next;
};


struct cmdBgList{
    struct cmdBgCell* debut;
    struct cmdBgCell* fin;
};

void execcmd (struct cmdline *cmd, struct cmdBgList *pidList);

void switchPipe(struct cmdline *cmd);
void pipeCmd(struct cmdline *cmd);
struct cmdBgCell* createCmdBgCell(struct cmdBg cmd, struct cmdBgCell* previous);
struct cmdBg* createCmdBg(pid_t pid, int num);
void addPid(struct cmdBgList* pidList, pid_t pid);
struct cmdBgList* createCmdBgList();
void rmCmdBg(struct cmdBgList* cmdList, struct cmdBgCell* cmdCell);
#endif
