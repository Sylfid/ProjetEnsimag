#include "commande.h"

void execcmd(struct cmdline *cmd){
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
                break;
        }

}


