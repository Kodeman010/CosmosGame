#ifndef BATTLE_H
#define BATTLE_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <random>
#include "Ships.h"

void battle_loop(ALLEGRO_EVENT_QUEUE *event_queue);
void place_ships();
void click_on_ship(int x, int y);
void draw_moveset();
void moveset_logic(int x, int y);
void reload_map(int x, int y, ALLEGRO_BITMAP *background, int active_player, int phase);

void attack_ship(int x, int y);
void Roll_dice(Ships *&attacker, Ships &defender, int i);
#endif // BATTLE_H
