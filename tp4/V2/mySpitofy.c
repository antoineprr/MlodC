// gcc -W -Wall linkedListOfMusic.c mySpitofy.c -o mySpitofy
// gcc -W -Wall -Wno-unused-parameter linkedListOfMusic.c mySpitofy.c -o mySpitofy

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListOfMusic.h"

Music* parseMusic(char* line) {
    Music* music = (Music*)malloc(sizeof(Music));

    music->name = strdup(strsep(&line, ","));
    music->artist = strdup(strsep(&line, ","));
    music->album = strdup(strsep(&line, ","));
    music->genre = strdup(strsep(&line, ","));
    music->disc_number = atoi(strsep(&line, ","));
    music->track_number = atoi(strsep(&line, ","));
    music->year = atoi(strsep(&line, ","));

    return music;
}


int main() {
    FILE* file = fopen("music.csv", "r");

    MusicList liste = NULL;

    char line[1024];
    fgets(line, sizeof(line), file); // pour ignorer la premiere ligne


    while (fgets(line, sizeof(line), file)) {
        Music* music = parseMusic(line);
        if (music) {
            liste = addMusic(liste, music);
        }
    }

    fclose(file);

    printf("Liste des musiques avant tri:\n");
    diplayMusicList(liste);

    sortMusicsByYear(&liste);

    printf("\nListe des musiques après tri par année:\n");
    diplayMusicList(liste);
    

    destroyMusicList(liste);

    return 0;
}