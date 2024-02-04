#include "field.h"
#include "main.h"

//This file includes funtions that are related to field ( drawing the field, inserting ships, check (if unshooted place at) field)

// Initialisig field with empty ocean
struct Field* initlField(struct Field* pelikentta){
    
    // Allocating memory
    pelikentta= (struct Field*) calloc(12,sizeof(int));
    // Check if memory reservation was success
    if (pelikentta == NULL) {
        printf("\nMemory allocation error! (f,1)");
        exit(0); // exit program
    }

    // Initializing variables
    (*pelikentta).leveys=MAX_LENGTH;
    (*pelikentta).korkeus=MAX_HEIGHT;

    // Allocating memory
    (*pelikentta).rivit=calloc(10,10*sizeof(int));;
    // Check if memory reservation was success
    if ((*pelikentta).rivit == NULL) {
        printf("\n Memory allocation error! (f,2)");
        exit(0); // exit program
    }

    // Going throught lines
    for (int y=0;y<MAX_HEIGHT;y++){
        struct Rivi rivi;
        // Allocating memory
        rivi.lista=calloc(10,10*sizeof(int));
        // Check if memory reservation was success
        if (rivi.lista == NULL) {
            printf("\n Memory allocation error! (f,3)");
            exit(0); // exit program
        }
        //Going through row and setting spots to ocean
        for (int x=0;x<MAX_LENGTH;x++){
            rivi.lista[x]=ocean_line;
        }
        // Adding row to field structure
        (*pelikentta).rivit[y]=rivi;  
    }
    
    //returning field;
    return pelikentta;
}

// Printing field to screen
void drawField(struct Field* pelikentta1,int* osumat1, struct Field* pelikentta2,int* osumat2){
    int ship1=0,ship2=0;
    
    // Printing header fields
    printf("\n");
    printf("------------------------------------ SEA BATLE ----------------------------------- \n");
    printf("------------------------------------------ ----------------------------------------\n");
    printf("---------------- Own --------------------- -------------------- Enemy -------------\n");
    
    //Going throuh field spots
    for (int y=MAX_HEIGHT-1;y>=0;y--){
        
        // Printing start and line number of field 
        printf("| %d |", y);

        // Printing field
        for (int x=0;x<MAX_LENGTH;x++){
            // Empty ocean
            if (((*pelikentta1).rivit[y].lista[x]) == ocean_line){
                printf(" ~ ");
            // Near ship spot which is not found yet
            }else if (((*pelikentta1).rivit[y].lista[x]) == ocean_buffer){
                printf(" ~ ");
            // Missed shot
            }else if (((*pelikentta1).rivit[y].lista[x]) == shoot_miss){
                printf("   ");
            // Shot which hit near ship
            }else if (((*pelikentta1).rivit[y].lista[x]) == shoot_nearmiss){
                printf(" x ");
            // Shot which hit ship
            }else if (((*pelikentta1).rivit[y].lista[x]) == shoot_hit){
                printf(" O ");
            // Otherwise print ship
            }else{
                printf(" %d ",(*pelikentta1).rivit[y].lista[x]);
            }
        }
        // Printing field one end
        printf("| ");

        // Printing ships lines after field one
        if (ship1<boatAmount){
            // First line is for header
            if (y==MAX_LENGTH-1) {
                printf("Ships:    ");
            }
            // Next lines are for ships
            else if (y<(MAX_LENGTH-1) && (y>=(MAX_LENGTH-1-boatAmount))){
                for(int merkit=0;merkit<10;merkit++){
                    if ((merkit < boatSize[ship1]-osumat1[ship1])){
                        printf("X"); 
                    }else if(merkit<(boatSize[ship1]) && (merkit >= boatSize[ship1]-osumat1[ship1])){
                        printf("%d",(boatSize[ship1]));
                    }else{
                        printf(" ");
                    }
                }
                ship1++;
            }
        // If all ships are printed set rest of the rows empty
        }else{
            for(int merkit=0;merkit<10;merkit++){
                printf(" ");
            }
        }

        // Printing start and line number of field 2
        printf("| %d |", y);
        
        // Printing field 2
        for (int x=0;x<MAX_LENGTH;x++){
             // Empty ocean
            if (((*pelikentta2).rivit[y].lista[x]) == ocean_line){
                printf(" ~ ");
            // Near ship spot which is not found yet
            }else if (((*pelikentta2).rivit[y].lista[x]) == ocean_buffer){
                printf(" ~ ");
            // Missed shot
            }else if (((*pelikentta2).rivit[y].lista[x]) == shoot_miss){
                printf("   ");
            // Shot which hit near ship
            }else if (((*pelikentta2).rivit[y].lista[x]) == shoot_nearmiss){
                printf(" x ");
            // Shot which hit ship
            }else if (((*pelikentta2).rivit[y].lista[x]) == shoot_hit){
                printf(" O ");
            // Otherwise print ocean instead of ship
            }else{
                printf(" ~ ");
            }
        }
        printf("| ");

        // Printing ships lines after field two
        if (ship2<boatAmount){
            
            // First line is for header
            if (y==MAX_LENGTH-1) {
                printf("Ships:    ");
            }
            // Next lines are for ships
            else if (y<(MAX_LENGTH-1) && (y>=(MAX_LENGTH-1-boatAmount))){
                for(int merkit=0;merkit<10;merkit++){
                    if ((merkit < boatSize[ship2]-osumat2[ship2])){
                        printf("X"); 
                    }else if(merkit<(boatSize[ship2]) && (merkit >= boatSize[ship2]-osumat2[ship2])){
                        printf("%d",(boatSize[ship2]));
                    }else{
                        printf(" ");
                    }
                }
                ship2++;
            }
        // If all ships are printed set rest of the rows empty
        }else{
            for(int merkit=0;merkit<10;merkit++){
                printf(" ");
            }
        }

        printf("\n");
        
    }
    // Print footer fields
    printf("---------------------------------------------- ------------------------------------\n");
    printf("----- a  b  c  d  e  f  g  h  i  j ----------- ----- a  b  c  d  e  f  g  h  i  j -\n");
    printf("---------------------------------------------- ------------------------------------\n");
}
        
//Printing only own field when setting ships
void drawField_one(struct Field* pelikentta1){
    // Print Header fields
    printf("\n");
    printf("------------ SEA BATLE -------------\n");
    printf("------------------------------------\n");

    //Going throuh field spots
    for (int y=MAX_HEIGHT-1;y>=0;y--){
        
        //printing ilne number
        printf("| %d |", y);

        for (int x=0;x<MAX_LENGTH;x++){
            // Empty ocean
            if (((*pelikentta1).rivit[y].lista[x]) == ocean_line){
                printf(" ~ ");
            // Near ship spot which is not found yet
            }else if (((*pelikentta1).rivit[y].lista[x]) == ocean_buffer){
                printf(" ~ ");
            // Missed shot
            }else if (((*pelikentta1).rivit[y].lista[x]) == shoot_miss){
                printf("   ");
            // Shot which hit near ship
            }else if (((*pelikentta1).rivit[y].lista[x]) == shoot_nearmiss){
                printf(" x ");
            // Shot which hit ship
            }else if (((*pelikentta1).rivit[y].lista[x]) == shoot_hit){
                printf(" O ");
            // Otherwise print ship
            }else{
                printf(" %d ",(*pelikentta1).rivit[y].lista[x]);
            }
        }
        // Printing line end symbol
        printf("| \n");

    }

    // Print footer fields 
    printf("------------------------------------\n");
    printf("----- a  b  c  d  e  f  g  h  i  j -\n"); 
    printf("------------------------------------\n");
}

// Insert ships to field
void insertship(struct Field* pelikentta,int alkux,int alkuy,int suunta,int pituus){
    
    int ax,lx,ay,ly;
    //Direction down
    if (suunta==0){
        //Setting starting and end place for ship with nearmiss spots around
        ax=((alkux-1)<0) ? 0 : (alkux-1); //don't let it be under 0
        lx=((alkux+1)<MAX_LENGTH) ? alkux+1 : (alkux); //don't let it go out of the field
        ay=((alkuy-1)<0) ? 0 : (alkuy-1); //don't let it be under 0
        ly=((alkuy+pituus)<MAX_LENGTH) ? alkuy+pituus : (alkuy+pituus-1); //don't let it go out of the field
        
        // going throught to y and x spots and mark those to field
        for (int y=ay;y<=ly;y++){
            for(int x=ax;x<=lx;x++){
                // check if there is empty space before ship
                if (y==(alkuy-1)){
                    (*pelikentta).rivit[y].lista[x]=ocean_buffer;
                //last x index is empty space after ship 
                }else if ((y==ly) && (ly-pituus-alkuy==0)){
                    (*pelikentta).rivit[y].lista[x]=ocean_buffer;
                }else{
                    if (x==(alkux-1)){
                        (*pelikentta).rivit[y].lista[x]=ocean_buffer;
                    }else if ((x==lx) && (lx!=alkux)){
                        (*pelikentta).rivit[y].lista[x]=ocean_buffer;
                    }
                    else{
                        (*pelikentta).rivit[y].lista[x]=pituus; 
                    }
                }
            }
        }

    //Direction right
    }else{
        //Setting starting and end place for ship with nearmiss spots around
        ay=((alkuy-1)<0) ? 0 : (alkuy-1); //don't let it be under 0
        ly=((alkuy+1)<MAX_LENGTH) ? alkuy+1 : (alkuy); //don't let it go out of the field
        ax=((alkux-1)<0) ? 0 : (alkux-1); //don't let it be under 0
        lx=((alkux+pituus)<MAX_LENGTH) ? alkux+pituus : (alkux+pituus-1);//don't let it go out of the field

        // going throught to y and x spots and mark those to field
        for (int y=ay;y<=ly;y++){
            for(int x=ax;x<=lx;x++){
                //check if there is empty space before ship
                if (y==(alkuy-1)){
                    (*pelikentta).rivit[y].lista[x]=ocean_buffer;
                //last x index is empty space after ship 
                }else if ((y==ly) && (ly!=alkuy)){
                    (*pelikentta).rivit[y].lista[x]=ocean_buffer;
                }else{
                    if (x==(alkux-1)){
                        (*pelikentta).rivit[y].lista[x]=ocean_buffer;
                    }else if ((x==lx) && (lx-pituus-alkux==0)){
                        (*pelikentta).rivit[y].lista[x]=ocean_buffer;
                    }
                    else{
                        (*pelikentta).rivit[y].lista[x]=pituus; 
                    }
                }
            }
        }
    }

}

// Set ships automatically to field
struct Ships setShipsAuto(struct Field* pelikentta){
    struct Ships tempShips;
    // Reserving space from memory
    tempShips.pituudet=calloc(boatAmount,sizeof(int));
    tempShips.osumat=calloc(boatAmount,sizeof(int));

    // Looping through ships and inserting those with user commands
    for (int i=0;i<boatAmount; i++){
        tempShips.pituudet[i]=boatSize[i];
        tempShips.osumat[i]=boatSize[i];
        int direction=0,boat_x=0,boat_y=0;
        bool again=1;

        // Choosing direcion
        direction = rand() % 2;
        do{
            // if chosen downward ship
            if (direction==0){
                // Select random startingpoints
                boat_x = rand() % (MAX_LENGTH);
                boat_y = rand() % (MAX_HEIGHT-boatSize[i]+1);
               
            // if chosen right going ship
            }else{
                // Select random startingpoints
                boat_y = rand() % (MAX_LENGTH);
                boat_x = rand() % (MAX_LENGTH-boatSize[i]+1);
            }
            
            // Check if place of new ship is allready taken
            again=check_field(pelikentta,boat_x,boat_y,direction,boatSize[i]);
        }while (again==1);

        // Insert ship to field;
        insertship(pelikentta,boat_x,boat_y,direction,boatSize[i]);
    }
        
    return tempShips;
}

// Set ships manually to the field 
struct Ships setShips(struct Field* pelikentta){
    struct Ships tempShips;
    // Reserving space from memory
    tempShips.pituudet=( int* ) calloc(boatAmount,sizeof(int));
    tempShips.osumat=( int* ) calloc(boatAmount,sizeof(int));
    
    int alkux,alkuy,direction;
    char ax,d_ship;
    
    //Drawing field
    drawField_one(pelikentta);
    
    // Looping through ships and inserting those with user commands
    for (int i=0;i<boatAmount; i++){
        bool again=1;
        alkux=1,direction=0;
        tempShips.pituudet[i]=boatSize[i];
        tempShips.osumat[i]=boatSize[i];

        // Loop until empty spot for ship is found
        do{
            printf("\nInsert ship with giving starting spot and direction (right or down) \n");
            printf("Each ship must have buffer of 1 space to another ship \n");
            printf("Give starting point to ship which length is %d \n",boatSize[i]);
            printf("(correct syntax like a 1 or a1): ");
            scanf("%c %d", &ax,&alkuy);
            getchar();
            printf("\nGive direction to ship (d=down,r=right): ");
            scanf("%c", &d_ship);
            getchar();

            // Change user given char to correct index
            switch (ax) {
            case 'a': alkux=0; break;
            case 'b': alkux=1; break;
            case 'c': alkux=2; break;
            case 'd': alkux=3; break;
            case 'e': alkux=4; break;
            case 'f': alkux=5; break;
            case 'g': alkux=6; break;
            case 'h': alkux=7; break;
            case 'i': alkux=8; break;
            case 'j': alkux=9; break;
            default:  alkux=1; break;
            }
            // Change direction to integer
            switch (d_ship) {
            case 'd': direction=0; break;
            case 'r': direction=1; break;
            default:  direction=1; break;
            }

            // Setting correct starting place for downward ship
            if (direction==0){
                alkuy=(alkuy-(boatSize[i]-1));
            }
        
            // Check if place of new ship is allready taken
            again=check_field(pelikentta,alkux,alkuy,direction,boatSize[i]);

            // Error message to user
            if (again==1){
                drawField_one(pelikentta);
                printf("\n\n Given spot is taken choose another:\n\n");
            }

        }while (again==true);
        // Insert ship to field;
        insertship(pelikentta,alkux,alkuy,direction,boatSize[i]);

        // draw field for next ship insert
        drawField_one(pelikentta);
    }

    //Return inserted ships.
    return tempShips;
}

//Check if given space for ship is allready taken or not
bool check_field(struct Field* pelikentta,int alkux,int alkuy,int suunta,int pituus){
    // Direction down
    if(suunta==0){
        // Going through spots of ship if there is occupied place
        for (int y=alkuy; y < alkuy+pituus; y++){
            //if there is not empty spot return true = try again
            if ((*pelikentta).rivit[y].lista[alkux]!=ocean_line){
                return true; //not empty place found
            } 
        }
    // Direction right
    }else{
        // Going through spots of ship if there is occupied place
        for (int x=alkux; x < alkux+pituus; x++){
            //if there is not empty spot return true = try again
            if ((*pelikentta).rivit[alkuy].lista[x]!=ocean_line){
                return true; //not empty place found
            }
        }
    }
            
    return false; // Ships length of empty spots for ship found
}