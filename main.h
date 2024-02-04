// #pragma once /* More modern option to prevent defining multiple times. Replace MAIN_H defs. */
#ifndef MAIN_H_
    #define MAIN_H_

    /* Includes. */

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <time.h>

    /* Defines. */

    #define MAX_LENGTH 10
    #define MAX_HEIGHT 10

    #define ocean_line 10
    #define ocean_buffer 11
    #define shoot_hit 12
    #define shoot_miss 13
    #define shoot_nearmiss 14

    #define pc_level 9
    #define boatAmount 6
   
    /* Variabls */
    extern const int boatSize[boatAmount];
    
    /* Structs */
    struct Ships{
        int* pituudet;
        int* osumat;
    };
    struct ShotPlace{
        int x;
        int y;
    };

/* Prototypes. */
    bool game_on(struct Ships*,int pelaaja);
    bool continue_game();
    bool set_own_ships();

#endif // MAIN_H_