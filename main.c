#include "field.h"
#include "shoot.h"
#include "main.h"
const int boatSize[boatAmount] = {5,4,3,3,2,1};
struct Field* pelikentta1=NULL;
struct Field* pelikentta2=NULL;
struct Ships* ships1=NULL;
struct Ships* ships2=NULL;

//This file includes main funtion and functions that are related to main.

 
// Checks if game winner is found or not
bool game_on(struct Ships* laivat,int pelaaja){
    int sinked =0;
    
    // Going through ships to find which ships are allready sunk
    for (int i=0;i<boatAmount; i++){
        //If ships don't have places to hit anymore
        if ((*laivat).osumat[i]==0){
            sinked += 1;
        }
    }
    // If amount of sinked ships is same than amount of ships
    if (sinked==boatAmount){
        printf("\n\n");
        printf("--------------------------------------------------------------------------\n");
        printf(" Game ended\n");
       
        // Print winner
        if (pelaaja==0){
            printf(" Gongratulations you won!\n\n");
        }else{
            printf(" Unfortunately computer won this time!\n\n");
        }
        printf("--------------------------------------------------------------------------\n");
        return false;
       
    // All the ships have not been sinked yet
    }else{
        return true;
    }
}

// Ask if player wants to play another game
bool continue_game(){
    char cont='y';
    
    printf("Do you want a new game: (y/n)");
    scanf("%c", &cont);
    getchar();
    
    // Returning result from user choice 
    switch (cont) {
        case 'y': return true;
        default: return false;
    }
}

// Asking if player wants to choose place of ships or give computer to choose
bool set_own_ships(){
    char choice='y';
    
    printf("Do you want choose your own ship locations: (y/n)");
    scanf("%c", &choice);
    getchar();
    
    // Returning result from user choice
    switch (choice) {
        case 'y': return true;
        default:  return false;
    }
}

int main(){
    struct Ships tempShips1;
    bool new_game=1,game_going=1;

    // Initializing fields 
    pelikentta1=initlField(pelikentta1); 
    pelikentta2=initlField(pelikentta2);

    // Allocating memory for ships
    ships1=calloc(boatAmount,sizeof(int));
    ships2=calloc(boatAmount,sizeof(int));
    if ((ships2 == NULL) || (ships2 == NULL)) {
        printf("\n Memory allocation error! (f,3)");
        exit(0); // exit program
    }

    time_t t;
    srand((unsigned) time(&t));
    
    // Printing header
    printf("\n");
    printf("--------------------------------------------------------------------------\n");
    printf("Welcome to the SEA BATTLE Game \n");
    printf("Game purpose is to sink opponents ships before opponent does sink yours \n");
    printf("--------------------------------------------------------------------------\n");

    // Whole Game session loop
    do{
        //Choise if player wants to choose ship places
        if (set_own_ships()==true){
            // Setting ships manually
            tempShips1=setShips(pelikentta1);
        }else{
            // Setting ships automatically
            tempShips1=setShipsAuto(pelikentta1);
        }
        // Inserting chosen ships
        (*ships1)=tempShips1;

        // Setting enemy ships automatically
        (*ships2)=setShipsAuto(pelikentta2);

        // Loop for one game
        do{
            // Draw field
            drawField(pelikentta1,ships1->osumat,pelikentta2,ships2->osumat);
            // player 1 shoot
            
            //shoot_pc(pelikentta2,ships2);
            shoot(pelikentta2,ships2);
            
            //check laivat array if there is still boats left
            if (game_on(ships2,0) == false){ game_going=false; }
            
            if (game_going==false){
                // player 2 shoot
                shoot_pc2(pelikentta1,ships1);
                //check ship array if there is still boats left
                if (game_on(ships1,1) == false){ game_going=0; }
            }

        }while (game_going==true);
        
        // Ask if palyer wants another game
        new_game=continue_game();

    }while (new_game==true);

    return 0;
}