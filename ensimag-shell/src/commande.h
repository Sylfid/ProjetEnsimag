#ifndef COMMANDE_H
#define COMMANDE_H

#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

void execcmd (struct cmdline *cmd);


#endif
