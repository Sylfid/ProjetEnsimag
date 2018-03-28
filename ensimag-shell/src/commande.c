#include "commande.h"
#include "fcntl.h"
void execcmd(struct cmdline *cmd, struct cmdBgList *cmdList){
        struct cmdBgCell* actualCell=cmdList->debut;
        struct cmdBgCell* actualCellCopy=actualCell;
        pid_t pid ;
        int j=0;
        switch (pid=fork()){
            case -1:
                perror("fork");
            case 0:
                switchPipe(cmd);
                assert(0);
            default:
                while(actualCell!=NULL){
                    actualCellCopy=actualCell->next;
                    if(waitpid(actualCell->cmd.pid,NULL,WNOHANG)==
                            actualCell->cmd.pid){
                        printf("[%d] %d Done\n",actualCell->cmd.numero, actualCell->cmd.pid);
                        rmCmdBg(cmdList,actualCell);
                    }
                    actualCell=actualCellCopy;
                }
                if(!strncmp(*cmd->seq[0], "jobs", 4)){
                    actualCell=cmdList->debut;
                    while(actualCell!=NULL){
                        printf("[%d] ", actualCell->cmd.numero);
                        for (j=0; actualCell->cmd.name[j]!=0; j++) {
                                printf("%c", actualCell->cmd.name[j]);
                        }
                        printf("\n");
                        actualCell=actualCell->next;
                    }
                }
                if(cmd->bg == 0){
                   waitpid(pid,NULL,0);
                }
                else{
                    addPid(cmdList,pid,*cmd->seq[0]); 
                    printf("[%d] %d\n",cmdList->fin->cmd.numero, pid);
                }
                break;
        }
}

void switchPipe(struct cmdline *cmd){
    int ifile, ofile;
    if(cmd->in != NULL){
        ifile = open(cmd->in, O_RDONLY);
        dup2(ifile, 0);
        close(ifile);
    }
    if(cmd->out != NULL){
        ofile = open(cmd->out, O_WRONLY);
        dup2(ofile, 1);
        close(ofile);
    }
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
        close(daPipe[1]);
        close(daPipe[0]);
        execvp(*cmd->seq[1], cmd->seq[1]);
    }
    dup2(daPipe[1], 1);
    close(daPipe[0]);
    close(daPipe[1]);
    execvp(*cmd->seq[0], cmd->seq[0]);
}

struct cmdBg* createCmdBg(pid_t pid, int num, char* name){
    struct cmdBg* pidList = (struct cmdBg*)malloc(sizeof(struct cmdBg));
    pidList->numero=num;
    pidList->pid=pid;
    char actualChar='a';
    int i=0,j=0;
    while(actualChar != '\0'){
        actualChar=name[i];
        i++;
    }
    printf("%d",i);
    pidList->name=(char*)malloc(i*sizeof(char));
    for(j=0;j<i;j++){
        pidList->name[i]=name[i];
    }
    return pidList;
}

struct cmdBgCell* createCmdBgCell(struct cmdBg cmd, struct cmdBgCell* previous){
    struct cmdBgCell* cell=(struct cmdBgCell*)malloc(sizeof(struct cmdBgCell));
    cell->prev=previous;
    cell->next=NULL;
    cell->cmd=cmd;
    return cell;
}


void addPid(struct cmdBgList* pidList, pid_t pid, char* name){
    int numero = 1;
    if(pidList->debut != NULL){
        numero=pidList->fin->cmd.numero+1;
    }
    struct cmdBgCell* newCell = createCmdBgCell(
            *createCmdBg(pid,numero,name),pidList->fin);
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
       cmdList->debut->prev=NULL;
    }
    else if(cmdList->fin == cmdCell){
       cmdList->fin= cmdList->fin->prev;
       cmdList->fin->next=NULL;
    }
    else{
        cmdCell->prev->next=cmdCell->next;
        cmdCell->next->prev=cmdCell->prev;
    }
    free(cmdCell);
}

void execcmdln(struct cmdline *cmd){ 
        pid_t pid ;
        switch (pid=fork()){
            case -1:
                perror("fork");
            case 0:
                switchPipe(cmd);
                assert(0);
            default:
                if(cmd->bg == 0){
                   waitpid(pid,NULL,0);
                }
                break;
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

