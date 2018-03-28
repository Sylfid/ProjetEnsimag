#include "commande.h"

void execcmd(struct cmdline *cmd, struct cmdBgList *cmdList){
        struct cmdBgCell* actualCell=cmdList->debut;
        struct cmdBgCell* actualCellCopy=actualCell;
        pid_t pid ;
        switch (pid=fork()){
            case -1:
                perror("fork");
            case 0:
                switchPipe(cmd);
                if(strncmp(*cmd->seq[0], "jobs", 4)){
                    assert(0);
                }
                assert(0);
            default:
                while(actualCell!=NULL){
                    actualCellCopy=actualCell->next;
                    if(waitpid(actualCell->cmd.pid,NULL,WNOHANG)==
                            actualCell->cmd.pid){
                        printf("[%d] %d Done\n",cmdList->fin->cmd.numero, actualCell->cmd.pid);
                        rmCmdBg(cmdList,actualCell);
                    }
                    actualCell=actualCellCopy;
                }
                if(cmd->bg == 0){
                   waitpid(pid,NULL,0);
                }
                else{
                    addPid(cmdList,pid); 
                    printf("[%d] %d\n",cmdList->fin->cmd.numero, pid);
                }
                break;
        }
}

void switchPipe(struct cmdline *cmd){
    if(cmd->seq[1] == NULL){
        execvp(*cmd->seq[0], cmd->seq[0]);
    }
    else{
        pipeCmd(cmd);
    }
}

void pipeCmd(struct cmdline *cmd){
    pid_t pid;
    int daPipe[2];
    pipe(daPipe);
    pid=fork();
    if(pid == 0){
        dup2(daPipe[0], 0);
        close(daPipe[0]);
        close(daPipe[1]);
        execvp(*cmd->seq[0], cmd->seq[0]);
    }
    dup2(daPipe[1], 1);
    close(daPipe[0]);
    close(daPipe[1]);
    execvp(*cmd->seq[1], cmd->seq[1]);
}

struct cmdBg* createCmdBg(pid_t pid, int num){
    struct cmdBg* pidList = (struct cmdBg*)malloc(sizeof(struct cmdBg));
    pidList->numero=num;
    pidList->pid=pid;
    return pidList;
}

struct cmdBgCell* createCmdBgCell(struct cmdBg cmd, struct cmdBgCell* previous){
    struct cmdBgCell* cell=(struct cmdBgCell*)malloc(sizeof(struct cmdBgCell));
    cell->prev=previous;
    cell->next=NULL;
    cell->cmd=cmd;
    return cell;
}


void addPid(struct cmdBgList* pidList, pid_t pid){
    int numero = 1;
    if(pidList->debut != NULL){
        numero=pidList->fin->cmd.numero+1;
    }
    struct cmdBgCell* newCell = createCmdBgCell(
            *createCmdBg(pid,numero),pidList->fin);
    if(pidList->debut == NULL){
        pidList->debut=newCell;
        pidList->fin=newCell;
    }
    else{
        pidList->fin->next=newCell;
        pidList->fin=newCell;
    }
}


struct cmdBgList* createCmdBgList(){
    struct cmdBgList* list = (struct cmdBgList*)
        malloc(sizeof(struct cmdBgList));
    list->debut=NULL;
    list->fin=NULL;
    return list;
}

void rmCmdBg(struct cmdBgList* cmdList, struct cmdBgCell* cmdCell){
    if(cmdList->fin == cmdCell && cmdList->debut == cmdCell){
        cmdList->fin=NULL;
        cmdList->debut=NULL;
    }
    else if(cmdList->debut == cmdCell){
       cmdList->debut= cmdList->debut->next;
    }
    else if(cmdList->fin == cmdCell){
       cmdList->fin= cmdList->fin->prev;
    }
    else{
        cmdCell->prev->next=cmdCell->next;
        cmdCell->next->prev=cmdCell->prev;
    }
    free(cmdCell);
}


/*
void execcmdbg(struct cmdline *cmd){
        pid_t pid ;
        switch (pid=fork()){
            case -1:
                perror("fork");
            case 0:
                execvp(*cmd->seq[0],*cmd->seq);
                assert(0);
            default:
                if(cmd->bg == 0){
                   waitpid(0,NULL,0);
                }
                cmd->bg=0;
                break;
        }

*/

