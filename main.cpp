#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include "Ships.h"
#include "Range.h"
#include "Battle.h"
#include "Multiplayer.h"
//#include "Allegro.hpp"

#define ScreenWidth 1200
#define ScreenHeight 800
#define BlockSize 30

int main()
{
    if (!al_init())
    {
        al_show_native_message_box(NULL, NULL, NULL, "Could not initialize Allegro5", NULL, NULL);
        return -1;
    }
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    //al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

    ALLEGRO_DISPLAY *display = al_create_display(ScreenWidth, ScreenHeight);
    //ALLEGRO_KEYBOARD_STATE keyState;
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    if(!display)
    {
        al_show_native_message_box(NULL, NULL, NULL, "Could not initialize Display window", NULL, NULL);
        return -1;
    }

    //add_ship();
    //save_ships();
    //read_ships();
    //show_ships();

    bool draw = true;

    multiplayer_loop(event_queue);
    battle_loop(event_queue);


    al_destroy_display(display);

    return 0;
}

