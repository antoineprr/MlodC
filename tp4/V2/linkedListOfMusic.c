#include "linkedListOfMusic.h"
#include <stdlib.h>
#include <stdio.h>

MusicList createMusic(char* name, char* artist, char* album, char* genre, int disc_number, int track_number, int year) {
    MusicList newMusic = malloc(sizeof(Music));
    newMusic->name = strdup(name);
    newMusic->artist = strdup(artist);
    newMusic->album = strdup(album);
    newMusic->genre = strdup(genre);
    newMusic->disc_number = disc_number;
    newMusic->track_number = track_number;
    newMusic->year = year;
    newMusic->nextMusic = NULL;
    return newMusic;
}

MusicList addMusic(MusicList liste, MusicList nouvelleMusique) {
    nouvelleMusique->nextMusic = liste;
    return nouvelleMusique;
}

void diplayMusicList(MusicList liste) {
    MusicList currentList = liste;
    while (currentList != NULL) {
        printf("%s,%s,%s,%s,%d,%d,%d\n", 
               currentList->name, currentList->artist, currentList->album, currentList->genre, 
               currentList->disc_number, currentList->track_number, currentList->year);
        currentList = currentList->nextMusic;
    }
}

void destroyMusicList(MusicList liste) {
    if(liste != NULL){
        destroyMusicList(liste->nextMusic);
        free(liste->name);
        free(liste->artist);
        free(liste->album);
        free(liste->genre);
        free(liste);
    }
}

MusicList sortMusicsByYear(MusicList liste) {
    if (liste == NULL || liste->nextMusic == NULL) {
        return liste; 
    }

    bool change;
    MusicList currentList;
    Music tempMusic;

    do {
        change = false;
        currentList = liste;

        while (currentList->nextMusic != NULL) {
            if (currentList->year > currentList->nextMusic->year) {
                // Swap contents, not pointers
                tempMusic = *currentList;
                *currentList = *(currentList->nextMusic);
                *(currentList->nextMusic) = tempMusic;

                // Fix the next pointers after swap
                tempMusic.nextMusic = currentList->nextMusic->nextMusic;
                currentList->nextMusic->nextMusic = currentList->nextMusic;
                currentList->nextMusic = tempMusic.nextMusic;

                change = true;
            }
            currentList = currentList->nextMusic;
        }
    } while (change);

    return liste;
}