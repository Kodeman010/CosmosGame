#include "Multiplayer.h"
#include "Ships.h"

void multiplayer_loop(ALLEGRO_EVENT_QUEUE *event_queue)
{
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_BITMAP *background = al_load_bitmap("images/multiplayer_background.jpg");
    ALLEGRO_FONT *font = al_load_font("fonts/LiberationSerif-Regular.ttf", 25, NULL);

    ALLEGRO_BITMAP *ready_button = al_load_bitmap("misc/button_ready.png");

    std::vector <ALLEGRO_BITMAP*> ship_bitmap;

    int player_0_points = 100;
    int player_1_points = 100;
    int active_faction = 0;
    int *player_points = &player_0_points;
    int offset = 0;

    int x, y; // mouse coordinates
    bool done = false;
    while(!done)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        if (events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(events.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            }
        }
        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;

        if (events.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            x = events.mouse.x;
            y = events.mouse.y;
        }
        if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            x = events.mouse.x;
            y = events.mouse.y;
            al_draw_bitmap(background, 0, 0, NULL);
            faction_0_creation(x, y, active_faction);

            if (events.mouse.button & 1)
            {
                if (x >= 1000 && x <= 1108 && y >= 700 && y <= 740) // Ready button clicked
                {
                    if (ships_vector.size() <= 0)
                        continue;

                    ++ active_faction;
                    player_points = &player_1_points;
                    offset = ships_vector.size();

                    if (active_faction > 1)
                    {
                        place_down_ships(event_queue, ship_bitmap);
                        return;
                    }
                    faction_0_creation(x, y, active_faction);
                }
                view_ship_selection(active_faction);
                faction_0_interface(x, y, font);
            }
            else if (events.mouse.button & 2)
            {
                faction_0_add_ship(x, y, player_points, active_faction);
                remove_ship(x, y, player_points, offset);
                view_ship_selection(active_faction);
            }
            al_draw_textf(font, al_map_rgb(255,255,255), 5, 5, 0, "Points left: %d", *player_points);
            std::string faction = "";
            if (active_faction == 0)
                faction = "Union of Constellations";
            else if (active_faction == 1)
                faction = "Space Pirates";
            al_draw_textf(font, al_map_rgb(255,255,255), 800, 5, 0, "%s", faction.c_str());

            al_draw_bitmap(ready_button, 1000, 700, 0);
            al_flip_display();
        }

    }
    al_destroy_bitmap(background);
    al_destroy_event_queue(event_queue);
    exit(0);
}

void place_ship(std::vector <ALLEGRO_BITMAP*> &ship_bitmap)
{
    for (int i = 0; i < ship_bitmap.size(); ++i)
    {
        al_draw_rotated_bitmap(ship_bitmap[i], 15, 15, ships_vector[i].get_ship_x()+15, ships_vector[i].get_ship_y()+15, ships_vector[i].get_ship_rotation() * 3.1415/ 180, NULL);
        //al_draw_bitmap(ship_bitmap[i], ships_vector[i].get_ship_x(), ships_vector[i].get_ship_y(), 0);
    }
}

void place_down_ships(ALLEGRO_EVENT_QUEUE *event_queue, std::vector <ALLEGRO_BITMAP*> &ship_bitmap)
{
    ALLEGRO_BITMAP *background = al_load_bitmap("images/battle_background.png");
    ALLEGRO_BITMAP *active_ship_bitmap;
    load_ship_bitmap(ships_vector[ship_bitmap.size()], active_ship_bitmap);

    for (int i = 0; i < ships_vector.size(); ++i)
        if (ships_vector[i].get_faction() == 1)
            ships_vector[i].set_ship_rotation(180);

    int ship_amount = ships_vector.size();
    int x, y;
    int x1 = 0, y1 = 720, x2 = 1280, y2 = 800; // faction rectangle // 0 0 1200 80 // 0 720 1200 800

    al_draw_bitmap(background, 0, 0, 0);

    while (ship_bitmap.size() < ship_amount)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        if (events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(events.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                exit(0);
                break;
            }
        }
        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit(0);

        if (events.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            x = events.mouse.x;
            y = events.mouse.y;
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(255,255,0), 2);
            al_draw_rotated_bitmap(active_ship_bitmap, 15, 15, x+15, y+15, ships_vector[ship_bitmap.size()].get_ship_rotation() * 3.1415/ 180, NULL);

            place_ship(ship_bitmap);
            al_flip_display();
        }
        if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(255,255,0), 2);
            if (events.mouse.button & 1)
            {
                if (x >= x1 && x <= x2 && y >= y1 && y <= y2-30) // y2-30, bo dlugosc statku
                {
                    bool collision = false;
                    for (int i = 0; i < ships_vector.size(); ++i)
                    {
                        if (x + 30 >= ships_vector[i].get_ship_x() && x - 30 <= ships_vector[i].get_ship_x()
                         && y + 30 >= ships_vector[i].get_ship_y() && y - 30 <= ships_vector[i].get_ship_y())
                        {
                            collision = true;
                            break;
                        }
                    }
                    if (collision == false)
                    {
                        ships_vector[ship_bitmap.size()].set_ship_x(x);
                        ships_vector[ship_bitmap.size()].set_ship_y(y);

                        ship_bitmap.push_back(active_ship_bitmap);

                        if (ship_bitmap.size() == ships_vector.size())
                            return;
                        load_ship_bitmap(ships_vector[ship_bitmap.size()], active_ship_bitmap);

                        if (ships_vector[ship_bitmap.size()].get_faction() == 1)
                        {
                            x1 = 0; x2 = 1280;
                            y1 = 0; y2 = 80;
                        }
                    }

                }
                place_ship(ship_bitmap);
            }
            al_flip_display();
        }
    }
}



void view_ship_selection(int active_faction)
{
    ALLEGRO_BITMAP *ship_bitmap;
    int x1 = 100;
    int y1 = 100;
    int temp = 0;
    for (int i = 0; i < ships_vector.size(); ++i)
    {
        if (active_faction == ships_vector[i].get_faction())
        {
            load_ship_bitmap(ships_vector[i], ship_bitmap);
            al_draw_bitmap(ship_bitmap, x1, y1, 0);
            x1 += 50;
        }
    }
}

void remove_ship(int x, int y, int *player_points, int offset)
{
    int a = ships_vector.size();
    for (int i = offset; i < ships_vector.size(); ++i)
    {
        if (x >= 100 + 50*(i-offset) && x <= 130 + 50*(i-offset) && y >= 100 && y <= 130)
        {
            std::cout << ships_vector.size() << "    " << i << "     " << i+offset << "\n";
            if (ships_vector[i].get_type() == "Frigate")
                *player_points += 20;
            else if (ships_vector[i].get_type() == "Cruiser")
                *player_points += 30;

            ships_vector.erase(ships_vector.begin() + i);
        }
    }
}

void faction_0_add_ship(int x, int y, int *player_points, int active_faction)
{
    int Attack, Evade, Hull, Shield;
    int faction;
    std::string type, name;
    if (x >= 100 && x <= 130 && y >= 700 && y <= 730 && *player_points >= 20)
    {
        Attack = 2; Evade = 2; Hull = 3; Shield = 0;
        faction = active_faction;
        type = "Frigate"; name = "name1";
        *player_points -= 20;
    }
    else if (x >= 150 && x <= 180 && y >= 700 && y <= 730 && *player_points >= 30)
    {
        Attack = 3; Evade = 3; Hull = 2; Shield = 1;
        faction = active_faction;
        type = "Cruiser"; name = "name2";
        *player_points -= 30;
    }
    else
        return;

    Ships ships(Attack, Evade, Hull, Shield, faction, type, name, 0, 0, 0, 0);
    for (int i = 0; i < 20; ++i)
        ships.movement[i] = 0;

    if (ships.get_type() == "Frigate")
    {
        ships.movement[0] = 2;
        ships.movement[1] = 5;
        ships.movement[2] = 8;
        ships.movement[3] = 32;
        ships.movement[4] = 35;
        ships.movement[5] = 38;
        ships.movement[6] = 41;
        ships.movement[7] = 44;
        ships.movement[8] = 62;
        ships.movement[9] = 92;
    }
    else if (ships.get_type() == "Cruiser")
    {
        ships.movement[0] = 2;
        ships.movement[1] = 5;
        ships.movement[2] = 8;
        ships.movement[3] = 11;
        ships.movement[4] = 14;
        ships.movement[5] = 32;
        ships.movement[6] = 35;
        ships.movement[7] = 38;
        ships.movement[8] = 41;
        ships.movement[9] = 44;
        ships.movement[10] = 65;
        ships.movement[11] = 68;
    }

    ships_vector.push_back(ships);
    ALLEGRO_FONT *font = al_load_font("fonts/LiberationSerif-Regular.ttf", 25, NULL);
    al_draw_textf(font, al_map_rgb(255,255,255),   5, 5, 0, "Points left: %d", *player_points);
}

void faction_0_creation(int x, int y, int active_faction)
{
    ALLEGRO_BITMAP *ship;

    if (active_faction == 0)
    {
        ship = al_load_bitmap("ships/frigate_blue.png");
        al_draw_bitmap(ship, 100, 700, 0);
        ship = al_load_bitmap("ships/cruiser_blue.png");
        al_draw_bitmap(ship, 150, 700, 0);
    }
    else if (active_faction == 1)
    {
        ship = al_load_bitmap("ships/frigate_red.png");
        al_draw_bitmap(ship, 100, 700, 0);
        ship = al_load_bitmap("ships/cruiser_red.png");
        al_draw_bitmap(ship, 150, 700, 0);
    }
}

void faction_0_interface(int x, int y, ALLEGRO_FONT *font)
{
    if (x >= 100 && x <= 130 && y >= 700 && y <= 730)
    {
        al_draw_text(font, al_map_rgb(255,255,255),   x-60, y-190, 0, "Frigate");

        al_draw_text(font, al_map_rgb(255,0,0),   x-60, y-160, 0, "Attack:");
        al_draw_text(font, al_map_rgb(255,0,0),   x+30, y-160, 0, "2");

        al_draw_text(font, al_map_rgb(0,255,0),   x-60, y-130, 0, "Evade:");
        al_draw_text(font, al_map_rgb(0,255,0),   x+30, y-130, 0, "2");

        al_draw_text(font, al_map_rgb(255,255,0), x-60, y-100, 0, "Hull:");
        al_draw_text(font, al_map_rgb(255,255,0), x+30, y-100, 0, "3");

        al_draw_text(font, al_map_rgb(0,255,255), x-60, y-70, 0,  "Shield:");
        al_draw_text(font, al_map_rgb(0,255,255), x+30, y-70, 0, "0");

        al_draw_text(font, al_map_rgb(255,255,255), x-60, y-40, 0, "Cost: 20 P");
    }
    else if (x >= 150 && x <= 180 && y >= 700 && y <= 730)
    {
        al_draw_text(font, al_map_rgb(255,255,255),   x-60, y-190, 0, "Cruiser");

        al_draw_text(font, al_map_rgb(255,0,0),   x-60, y-160, 0, "Attack:");
        al_draw_text(font, al_map_rgb(255,0,0),   x+30, y-160, 0, "3");

        al_draw_text(font, al_map_rgb(0,255,0),   x-60, y-130, 0, "Evade:");
        al_draw_text(font, al_map_rgb(0,255,0),   x+30, y-130, 0, "3");

        al_draw_text(font, al_map_rgb(255,255,0), x-60, y-100, 0, "Hull:");
        al_draw_text(font, al_map_rgb(255,255,0),   x+30, y-100, 0, "2");

        al_draw_text(font, al_map_rgb(0,255,255), x-60, y-70, 0,  "Shield:");
        al_draw_text(font, al_map_rgb(0,255,255),   x+30, y-70, 0, "1");

        al_draw_text(font, al_map_rgb(255,255,255), x-60, y-40, 0, "Cost: 30 P");
    }
}

