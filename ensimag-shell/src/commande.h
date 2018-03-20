#ifndef COMMANDE_H
#define COMMANDE_H

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

struct cmdBgList{
    int taille;
    struct cmdBg* cmd;
};

struct cmdBg{
    int numero;
    pid_t pid;
};

void execcmd (struct cmdline *cmd, struct cmdBgList *pidList);


struct cmdBg* createCmdBg(pid_t pid, int num);
void addPid(struct cmdBgList* pidList, pid_t pid);
struct cmdBgList* createCmdBgList();
#endif
