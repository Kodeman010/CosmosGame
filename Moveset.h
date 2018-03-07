#ifndef MOVESET_H
#define MOVESET_H
#include "Ships.h"

void movement(int x, int y, int active_player, int phase);
void move_ship(double speed);
void ship_collision();
void moving_ships();

void forward_1(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);
void lean_1_left(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);
void lean_1_right(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);
void hard_1_left(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);
void hard_1_right(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);

void forward_2(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);
void lean_2_left(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);
void lean_2_right(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);
void hard_2_left(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);
void hard_2_right(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);

void forward_3(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);
void lean_3_left(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);
void lean_3_right(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);
void hard_3_left(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);
void hard_3_right(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);

void forward_4(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y);

#endif // MOVESET_H
