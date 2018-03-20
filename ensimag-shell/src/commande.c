#include "commande.h"

void execcmd(struct cmdline *cmd, struct cmdBgList *pidList){
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
                    addPid(pidList,pid); 
                    printf("[%d] %d\n",pidList->taille, pid);
                }
                //for(i=0;i<pidList->taille;i++){

                break;
        }

}

struct cmdBg* createCmdBg(pid_t pid, int num){
    struct cmdBg* pidList = (struct cmdBg*)malloc(sizeof(struct cmdBg));
    pidList->numero=num;
    pidList->pid=pid;
    return pidList;
}

void addPid(struct cmdBgList* pidList, pid_t pid){
    pidList->taille++;
    struct cmdBg* newCmd = createCmdBg(pid,pidList->taille);
    pidList->cmd= (struct cmdBg*)realloc(pidList->cmd, sizeof(struct cmdBg)*pidList->taille);
    pidList->cmd[pidList->taille-1]=*newCmd;
}


struct cmdBgList* createCmdBgList(){
    struct cmdBgList* list = (struct cmdBgList*)malloc(sizeof(struct cmdBgList));
    list->taille=0;
    list->cmd=NULL;
    return list;
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

