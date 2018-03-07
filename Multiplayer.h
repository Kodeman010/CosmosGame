#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <vector>

void multiplayer_loop(ALLEGRO_EVENT_QUEUE *event_queue);

void faction_0_creation(int x, int y, int active_faction);
void faction_0_interface(int x, int y, ALLEGRO_FONT *font);
void faction_0_add_ship(int x, int y, int *player_points, int active_faction);
void view_ship_selection(int active_faction);
void remove_ship(int x, int y, int *player_points, int offset);
void place_down_ships(ALLEGRO_EVENT_QUEUE *event_queue, std::vector <ALLEGRO_BITMAP*> &ship_bitmap);
void place_ship(std::vector <ALLEGRO_BITMAP*> &ship_bitmap); // to many of the same, reduce to one function

#endif // MULTIPLAYER_H
