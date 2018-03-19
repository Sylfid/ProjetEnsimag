#include "commande.h"

void execcmd(struct cmdline *cmd){
        pid_t pid ;
        int status;
        switch (pid=fork()){
            case -1:
                perror("fork");
            case 0:
                execvp(*cmd->seq[0],*cmd->seq);
                if(strncmp(*cmd->seq[0],"jobs",4)){
                    assert(0);
                }
                //assert(0);
            default:
                if(cmd->bg == 0){
                    waitpid(0,&status,0);
                }
                break;
        }

}


