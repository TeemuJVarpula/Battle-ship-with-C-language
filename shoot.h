#ifndef SHOOT_H_
#define SHOOT_H_

/* Includes. */
#include "main.h"
#include "field.h"

/* Prototypes. */
void shoot(struct Field*, struct Ships*);
void shoot_pc(struct Field*, struct Ships*);
void shoot_pc2(struct Field*, struct Ships*);

bool check_target(struct Field* ,int ,int );
void mark_target(struct Field* ,struct Ships* ,int ,int );

#endif // SHOOT_H_