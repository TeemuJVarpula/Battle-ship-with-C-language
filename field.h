#ifndef FIELD_H_
#define FIELD_H_

/* Includes. */
#include "main.h"

/* Structs. */
struct Rivi{
    int* lista;    
};
struct Field {
    int leveys;
    int korkeus;

    struct Rivi *rivit;
};

/* Prototypes. */
struct Field* initlField(struct Field*);
void drawField(struct Field*, int*, struct Field*, int*);
void drawField_one(struct Field*);

void insertship(struct Field*, int, int, int, int);
struct Ships setShipsAuto(struct Field*);
struct Ships setShips(struct Field*);

bool check_field(struct Field*, int, int, int, int);

#endif // FIELD_H_