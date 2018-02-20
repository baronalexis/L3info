#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "audio.h"



int main (int argc, char *argv[]) {

    char * filename = NULL;

    int sample_size;

    int sample_rate;
    int channels;
    
    int descread;
    int descwrite;

    

    if(argc == 2) {
        filename = argv[1];
    } 
    else {
        printf("Veuillez entrer un et un seul nom de fichier audio en argument\n");
        exit(1);
    }

    if ((descread = aud_readinit(filename, &sample_rate, &sample_size, &channels)) < 0) {
        printf("Erreur readinit\n");
    }

    if ((descwrite = aud_writeinit(sample_rate, sample_size, channels)) < 0) {
        printf("Erreur writeinit\n");
    }

    int * buffer_audio[sample_size];

    ssize_t audio_read = sample_size;
    ssize_t audio_write = sample_size;



    while(audio_write == sample_size && audio_read == sample_size) {

        audio_read = read(descread, buffer_audio, sample_size);
        audio_write = write(descwrite, buffer_audio, sample_size);
    }


    if (close(descread) < 0) { perror("Erreur close descread");}
    if (close(descwrite) < 0) { perror("Erreur close descwrite");}
    

    return 0;
}