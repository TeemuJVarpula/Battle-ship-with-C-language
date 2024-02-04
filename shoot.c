#include "shoot.h"

//This file includes function related to shooting ships.

// Manual shot function
void shoot(struct Field* pelikentta,struct Ships* laivat){
    int osumax=0,osumay=0,again=0;
    char tempx='a';

    // Loop to find unshot spot from the field
    do{
        again=0;  // initilsing loop check
        
        printf("\nGive spot to shoot");
        printf("\n(Correct form is like a1): ");
        scanf("%c %d", &tempx,&osumay);
        getchar();

        // Changing x to integer
        switch (tempx) {
            case 'a': osumax=0; break;
            case 'b': osumax=1; break;
            case 'c': osumax=2; break;
            case 'd': osumax=3; break;
            case 'e': osumax=4; break;
            case 'f': osumax=5; break;
            case 'g': osumax=6; break;
            case 'h': osumax=7; break;
            case 'i': osumax=8; break;
            case 'j': osumax=9; break;
            default:  osumax=1; break;
        }

        //check if target is spot where is allready shot
        if (check_target(pelikentta,osumax,osumay)==true){
            again=1; 
            printf("That place is allready shot");
        }
    }while (again==1); //again==1);

    // set shot to field
    mark_target(pelikentta,laivat,osumax,osumay);
}

// Automatically shot function
void shoot_pc(struct Field* pelikentta,struct Ships* laivat){
    int osumax=0,osumay=0,again=0;
        
    // Loop to find unshot spot from the field
    do{
        again=0;  // initilsing loop check
        srand (time(NULL));
        osumay = rand() % (MAX_HEIGHT);
        osumax = rand() % (MAX_LENGTH);
        //printf(" new move %d %d ",line,column);

        //check if target can be taken
        if (check_target(pelikentta,osumax,osumay)==true){
            again=1; 
            //printf("Anna ampumaton kohta");
        }
         
    }while (again==1); //again==1);

    // set shot to field
    mark_target(pelikentta,laivat,osumax,osumay);
}
// Version 2 of automatical shot function ( little harder enemy )
void shoot_pc2(struct Field* pelikentta,struct Ships* laivat){
    int osumax=0,osumay=0,again=0,laskuri=0,index=0,valinta=0;
    int x_val[10]={0,0,0,0,0,0,0,0,0,0};
    int y_val[10]={0,0,0,0,0,0,0,0,0,0};
    
    // Loop to find unshot spot from the field
    for (int y=0;y<MAX_HEIGHT;y++){
        for(int x=0;x<MAX_LENGTH;x++){
            //one hit found
            if((*pelikentta).rivit[y].lista[x]==shoot_hit){
                //around hit is "sea"
                
                if((x-1 >= 0) &&((*pelikentta).rivit[y].lista[x-1]<shoot_hit)){
                    if ((laskuri<10)){
                        x_val[laskuri]=x-1;
                        y_val[laskuri]=y;
                        laskuri++;
                    }      
                }
                if((x+1 < MAX_LENGTH) && ((*pelikentta).rivit[y].lista[x+1]<shoot_hit)){
                    if ((laskuri<10)){
                        x_val[laskuri]=x+1;
                        y_val[laskuri]=y;
                        laskuri++;
                    }     
                }
                if( (y-1 >= 0) && ((*pelikentta).rivit[y-1].lista[x]<shoot_hit)){
                    if ((laskuri<10)){
                        x_val[laskuri]=x;
                        y_val[laskuri]=y-1;
                        laskuri++;
                    }
                }
                if((y+1 < MAX_HEIGHT) && ((*pelikentta).rivit[y+1].lista[x]<shoot_hit)){
                    if ((laskuri<10)){
                        x_val[laskuri]=x;
                        y_val[laskuri]=y+1;
                        laskuri++;
                    }     
                }
                
                //two hits in row and empty after
                if((x+2<MAX_LENGTH) && ((*pelikentta).rivit[y].lista[x+1]==shoot_hit) && ((*pelikentta).rivit[y].lista[x+2]<shoot_hit)){
                    if (laskuri<10){
                        x_val[laskuri]=x+1;
                        y_val[laskuri]=y;
                        laskuri++;
                    }
                }
                if((y+2<MAX_HEIGHT) && ((*pelikentta).rivit[y+1].lista[x]==shoot_hit) && ((*pelikentta).rivit[y+2].lista[x]<shoot_hit)){
                    if (laskuri<10){
                        x_val[laskuri]=x;
                        y_val[laskuri]=y+1;
                        laskuri++;
                    }     
                }
                
                //one space between two hits
                if((x+2<MAX_LENGTH) && ((*pelikentta).rivit[y].lista[x+2]==shoot_hit) && ((*pelikentta).rivit[y].lista[x+1]<shoot_hit)){
                    if (laskuri<10){
                        x_val[laskuri]=x+1;
                        y_val[laskuri]=y;
                        laskuri++;
                    }
                }
                if((x-2>0) && ((*pelikentta).rivit[y].lista[x-2]==shoot_hit) && ((*pelikentta).rivit[y].lista[x-1]<shoot_hit)){
                    if (laskuri<10){
                        x_val[laskuri]=x-1;
                        y_val[laskuri]=y;
                        laskuri++;
                    }
                }
                if((y+2<MAX_HEIGHT) && ((*pelikentta).rivit[y+2].lista[x]==shoot_hit) && ((*pelikentta).rivit[y+2].lista[x]<shoot_hit)){
                    if (laskuri<10){
                        x_val[laskuri]=x;
                        y_val[laskuri]=y+1;
                        laskuri++;
                    }     
                }
                if((y-2>0) && ((*pelikentta).rivit[y-2].lista[x]==shoot_hit) && ((*pelikentta).rivit[y-1].lista[x]<shoot_hit)){
                    if (laskuri<10){
                        x_val[laskuri]=x;
                        y_val[laskuri]=y-1;
                        laskuri++;
                    }
                }
                printf("\n");
            //Near miss found
            }
            if((*pelikentta).rivit[y].lista[x]==shoot_nearmiss){
                //around near hit is "sea"
                
                if( ( x-1 >= 0) && ((*pelikentta).rivit[y].lista[x-1]<shoot_hit)){
                    if (laskuri<10){
                        x_val[laskuri]=x-1;
                        y_val[laskuri]=y;
                        laskuri++;
                    }      
                }
                if( (x+1 < MAX_HEIGHT) && ((*pelikentta).rivit[y].lista[x+1]<shoot_hit)){
                    if (laskuri<10){
                        x_val[laskuri]=x+1;
                        y_val[laskuri]=y;
                        laskuri++;
                    }     
                }
                if( (y-1 >= 0) && ((*pelikentta).rivit[y-1].lista[x]<shoot_hit)){
                    if (laskuri<10){
                        x_val[laskuri]=x;
                        y_val[laskuri]=y-1;
                        laskuri++;
                    }      
                }
                if( (y+1 < MAX_HEIGHT) &&((*pelikentta).rivit[y+1].lista[x]<shoot_hit)){
                    if (laskuri<10){
                        x_val[laskuri]=x;
                        y_val[laskuri]=y+1;
                        laskuri++;
                    }     
                }
                printf("\n");
            }
            
            //Checking if amount of "better" options is full
            if (laskuri==10){
                break;
            }
        }
    }
    
    printf("\n");

    // Loop to find unshot spot from the field
    do{
        again=0;  // initilsing loop check
        
        // Checking if using "better" options list or random chose
        if ((index  < pc_level) && (index < laskuri)){
            valinta=rand() % (laskuri);
            osumax = x_val[valinta];
            osumay = y_val[valinta]; 
            //printf(" new move1 valinta:%d x:%d y:%d ",valinta,osumax,osumay);
            index++;
        }else{
            osumay = rand() % (MAX_HEIGHT);
            osumax = rand() % (MAX_LENGTH);
            //printf(" new move2 x:%d y:%d ",osumax,osumay);
        }
        //check if target can be taken
        if (check_target(pelikentta,osumax,osumay)==true){
            again=1; 
            //printf("Anna ampumaton kohta");
        }
    }while (again==1); //again==1);

    // set shot to field
    mark_target(pelikentta,laivat,osumax,osumay);
}

// Checking if chosen target spot can be taken
bool check_target(struct Field* pelikentta,int osumax,int osumay){
    
    //check what is now at the chosen spot
    if (((*pelikentta).rivit[osumay].lista[osumax]==shoot_hit)||
        ((*pelikentta).rivit[osumay].lista[osumax]==shoot_miss)||
        ((*pelikentta).rivit[osumay].lista[osumax]==shoot_nearmiss)){
        return true; 
    //If chosen spot is not shot before
    }else{
        return false;
    }
}

// Setting chosen target spot to field
void mark_target(struct Field* pelikentta,struct Ships* laivat,int osumax,int osumay){
    
    // If empty ( ~ ) spot
    if ((*pelikentta).rivit[osumay].lista[osumax]==ocean_line){
        // mark space with empty slot
        (*pelikentta).rivit[osumay].lista[osumax]=shoot_miss;
        printf(" Miss \n");
    // If near ship spot
    }else if((*pelikentta).rivit[osumay].lista[osumax]==ocean_buffer){
        // mark space with near miss slot
        (*pelikentta).rivit[osumay].lista[osumax]=shoot_nearmiss;
        printf(" Near miss \n");
    // If shot wass sccess
    }else{
        
        // Check if that was the last possible shot before ship is sinking
        for (int i=0; i<boatAmount; i++){
            if ((*laivat).pituudet[i] == (*pelikentta).rivit[osumay].lista[osumax]){
                
                if ((*laivat).osumat[i]>0){ 
                    (*laivat).osumat[i]-=1;
                    printf(" Hit\n");

                    // Target ship has all possible damages taken and is sinking
                    if ((*laivat).osumat[i]==0){
                        printf(" Boat sinkerd \n");
                    }
                    break;
                }                
            }
        }
        // Setting field as shot success
        (*pelikentta).rivit[osumay].lista[osumax]=shoot_hit;
    }
}


