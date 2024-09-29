#pragma once

#include <stdbool.h>

struct Music{
    char* name;
    char* artist;
    char* album;
    char* genre;
    int disc_number;
    int track_number;
    int year;
    struct Music* nextMusic;
};

typedef struct Music Music;

typedef Music* MusicList;

// creates a new music list with 1 element
MusicList createMusic(char* name, char* artist, char* album, char* genre, int disc_number, int track_number, int year);

// adds a music to a music list
MusicList addMusic(MusicList liste, MusicList nouvelleMusique);

// displays the music list
void diplayMusicList(MusicList liste);

// destroys all the elements from the list
void destroyMusicList(MusicList liste);

// sorts all the music from the music list by year   
MusicList sortMusicsByYear(MusicList liste);
