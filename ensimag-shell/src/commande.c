#include "commande.h"

void execcmd(struct cmdline *cmd, struct cmdBgList *cmdList){
        pid_t pid ;
        switch (pid=fork()){
            case -1:
                perror("fork");
            case 0:
                execvp(*cmd->seq[0],*cmd->seq);
                assert(0);
            default:
                if(cmd->bg == 0){
                   waitpid(pid,NULL,0);
                }
                else{
                    struct cmdBgCell* actualCell=cmdList->debut;
                    struct cmdBgCell* actualCellCopy=actualCell;
                    while(actualCell!=NULL){
                        actualCellCopy=actualCell->next;
                        if(waitpid(actualCell->cmd.pid,NULL,WNOHANG)==
                                actualCell->cmd.pid){
                            rmCmdBg(cmdList,actualCell);
                        }
                        actualCell=actualCellCopy;
                    }
                    addPid(cmdList,pid); 
                    printf("[%d] %d\n",cmdList->fin->cmd.numero, pid);
                }

                break;
        }

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
    int flag=0;
    if(cmdList->fin == cmdCell){
        cmdList->fin=NULL;
        flag=1;
    }
    if(cmdList->debut == cmdCell){
       cmdList->debut=NULL;
       flag=1;
    }
    if(!flag){
        cmdCell->prev->next=cmdCell->next;
        cmdCell->next->prev=cmdCell->prev;
        free(cmdCell);
    }
    else{
        free(cmdCell);
    }
       

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

