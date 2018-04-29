#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <pthread.h>

#include "stream_common.h"
#include "oggstream.h"


int main(int argc, char *argv[]) {
    int res;

    if (argc != 2) {
	fprintf(stderr, "Usage: %s FILE", argv[0]);
	exit(EXIT_FAILURE);
    }
    assert(argc == 2);


    // Initialisation de la SDL
    res = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS);
    atexit(SDL_Quit);
    assert(res == 0);
    
    // start the two stream readers
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, theoraStreamReader, argv[1]);
    pthread_create(&tid2, NULL, vorbisStreamReader, argv[1]);
    // wait audio thread
    if (pthread_join(tid2, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
    }
    // 1 seconde de garde pour le son,
    sleep(1);
    pthread_cancel(tid1);
    pthread_join(tid1,NULL);
    // tuer les deux threads videos si ils sont bloqués

    // attendre les 2 threads videos

    
    exit(EXIT_SUCCESS);    
}
