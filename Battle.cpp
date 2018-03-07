#include "Battle.h"
#include "Ships.h"
#include "Moveset.h"
#include "Range.h"
#include "Game.hpp"

#define BlockSize 30

void reload_map(int x, int y, ALLEGRO_BITMAP *background, int active_player, int phase)
{
    click_on_ship(x, y);
    al_draw_bitmap(background, 0, 0, NULL);
    movement(x, y, active_player, phase);
    place_ships();
    al_flip_display();
}

void handle_phases(int &phase, bool &next_phase, int x, int y, ALLEGRO_BITMAP *background, ALLEGRO_FONT *font, int &active_player)
{
    next_phase = true;
    for (int i = 0; i < ships_vector.size(); ++i)
    {
        if (ships_vector[i].get_faction() == active_player)
            if (ships_vector[i].get_done() == false)
            {
                next_phase = false;
                break;
            }
    }
    if (active_player == 1 && next_phase == true && phase == 0)
    {
        phase = 1;
        active_player = 0;
    }
    else if (active_player == 0 && next_phase == true && phase != 2)
    {
        active_player = 1;
    }


    if (phase == 2)
    {
        al_draw_text(font, al_map_rgb(255,255,255), 1050, 750, 0, "Next Turn");
        if (x > 1050 && x < 1150 && y > 750 && y < 780)
        {
            for (int i = 0; i < ships_vector.size(); ++i)
            {
                ships_vector[i].set_done(false);
            }
            phase = 0;
            active_player = 0;

            reload_map(x ,y, background, active_player, phase);
        }
    }
}

void battle_loop(ALLEGRO_EVENT_QUEUE *event_queue)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    ALLEGRO_BITMAP *background = al_load_bitmap("images/battle_background.png");
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT *font = al_load_font("fonts/LiberationSerif-Regular.ttf", 25, NULL);

    for (int i = 0; i < ships_vector.size(); ++i)
    {
        ships_vector[i].set_done(false);
        ships_vector[i].set_active_movement(0);
    }

    int active_player = 0;
    int phase = 0; // 0 - chosing movement 1 - moving ships 2 - attacking
    int x, y; // mouse coordinates
    bool next_phase = false;
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

        if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            x = events.mouse.x;
            y = events.mouse.y;

            if (events.mouse.button & 1)
            {
                click_on_ship(x, y);
                al_draw_bitmap(background, 0, 0, NULL);
                movement(x, y, active_player, phase);
                place_ships();

                if (active_ship != NULL)
                    range_collision(active_ship->get_ship_rotation());

                handle_phases(phase, next_phase, x, y, background, font, active_player);

                if (phase != 2)
                {
                    al_draw_text(font, al_map_rgb(255,255,255), 10, 2, 0, "Turn");
                    if (active_player == 0)
                        al_draw_text(font, al_map_rgb(255,255,255), 10, 20, 0, "Union of Constellations");
                    else if (active_player == 1)
                        al_draw_text(font, al_map_rgb(255,255,255), 10, 20, 0, "Space Pirates");
                }
                else
                    al_draw_text(font, al_map_rgb(255,255,255), 10, 2, 0, "Fight");

                al_flip_display();
            }
            else if (events.mouse.button & 2)
            {
                if (active_ship != NULL && phase == 2)
                    attack_ship(x, y);
            }
        }
        if (phase == 1)
        {
            for (int i = 0; i < ships_vector.size(); ++i)
            {
                active_ship = &ships_vector[i];
                moving_ships();
                active_ship->set_done(false);
                active_ship->set_active_movement(0);
            }
            reload_map(x ,y, background, active_player, phase);
            for (int i = 0; i < ships_vector.size(); ++i)
                ships_vector[i].set_done(false);
            phase = 2;
            active_player = 0;
        }
        if(ships_vector.size() <= 0)
            break;
    }
    std::cout << "\n\n            GAME OVER\n\n";
    al_destroy_bitmap(background);
    al_destroy_event_queue(event_queue);
}

void place_ships()
{
    ALLEGRO_BITMAP *ships = NULL;
    ALLEGRO_BITMAP *sub;
    for (int i = 0; i < ships_vector.size(); ++i)
    {
        if (ships_vector[i].get_type() == "Frigate")
        {
            load_ship_bitmap(ships_vector[i], ships);
            sub = al_create_sub_bitmap(ships, 0, 0, 30, 30);
            al_draw_rotated_bitmap(sub, 15, 15, ships_vector[i].get_ship_x()+15, ships_vector[i].get_ship_y()+15, ships_vector[i].get_ship_rotation() * 3.1415/ 180, NULL);
        }
        else if (ships_vector[i].get_type() == "Cruiser")
        {
            load_ship_bitmap(ships_vector[i], ships);
            sub = al_create_sub_bitmap(ships, 0, 0, 30, 30);
            al_draw_rotated_bitmap(sub, 15, 15, ships_vector[i].get_ship_x()+15, ships_vector[i].get_ship_y()+15, ships_vector[i].get_ship_rotation() * 3.1415/ 180, NULL);
        }
        else
        {
            std::cout << "Error, some ship were not found" << std::endl;
            exit(0);
        }
    }
    al_destroy_bitmap(ships);
}

void click_on_ship(int x, int y)
{
    for (int i = 0; i < ships_vector.size(); ++i)
    {
        if (x >= ships_vector[i].get_ship_x() && x <= ships_vector[i].get_ship_x() + BlockSize
              && y >= ships_vector[i].get_ship_y() && y <= ships_vector[i].get_ship_y() + BlockSize)
        {
            std::cout << "\nYou clicked on " << ships_vector[i].get_type() << " " << ships_vector[i].get_name();
            active_ship = &ships_vector[i];
            return;
        }
    }
    if (x < 1050) // > are options
        active_ship = NULL; // if none was clicked, so no range is displayed etc.
}

void attack_ship(int x, int y)
{
    for (int i = 0; i < ships_vector.size(); ++i)
    {
        if (ships_vector[i].get_in_range())
            if (x >= ships_vector[i].get_ship_x() && x <= ships_vector[i].get_ship_x() + BlockSize
             && y >= ships_vector[i].get_ship_y() && y <= ships_vector[i].get_ship_y() + BlockSize)
            {
                if (ships_vector[i].get_faction() != active_ship->get_faction() && active_ship->get_done() == false)
                {
                    Roll_dice(active_ship, ships_vector[i], i); // ship attacked
                    active_ship->set_done(true);
                }
                 return;
            }
    }
}

void Roll_dice(Ships *&attacker, Ships &defender, int i)
{
    std::mt19937 randomGenerator(time(NULL));
    std::uniform_int_distribution<int> dice_rolling(0, 7); // od 0 do 7
    std::uniform_int_distribution<int> randomize_width(300, 900);
    std::uniform_int_distribution<int> randomize_height(200, 600);
    //std::vector <ALLEGRO_BITMAP*> attacker_dice;
    //std::vector <ALLEGRO_BITMAP*> defender_dice;
    ALLEGRO_BITMAP *dice;

    int hit = 0, miss = 0;
    int evade = 0, nothing = 0;

    for (int i = 0; i < attacker->get_max_attack(); ++i)
    {
        int roll = dice_rolling(randomGenerator);
        if (roll == 0 || roll == 1 || roll == 2 || roll == 3) // miss
        {
            ++miss;
            dice = al_load_bitmap("images/dice/red_dice_nothing.png");
        }
        else if (roll == 4 || roll == 5 || roll == 6 || roll == 7) // hit
        {
            ++hit;
            dice = al_load_bitmap("images/dice/red_dice_hit.png");
        }
        //attacker_dice.push_back(dice);
        int width = randomize_width(randomGenerator);
        int height = randomize_height(randomGenerator);
        al_draw_bitmap(dice, width, height, 0);
    }

    for (int i = 0; i < defender.get_max_evade(); ++i)
    {
        int roll = dice_rolling(randomGenerator);
        if (roll == 0 || roll == 1 || roll == 2 || roll == 3) // miss
        {
            ++nothing;
            dice = al_load_bitmap("images/dice/green_dice_nothing.png");
        }
        else if (roll == 4 || roll == 5 || roll == 6 || roll == 7) // hit
        {
            ++evade;
            dice = al_load_bitmap("images/dice/green_dice_evade.png");
        }
        //defender_dice.push_back(dice);
        int width = randomize_width(randomGenerator);
        int height = randomize_height(randomGenerator);
        al_draw_bitmap(dice, width, height, 0);
    }

    system("cls");
    gotoxy(5, 3);
    int damage = hit - evade;
    std::cout << defender.get_max_hull() << "  " << damage << std::endl;
    if (damage < 0)
    {
        damage = 0;
        std::cout << "You've missed the target";
    }
    else
        std::cout << "You've dealt: " << damage << " damage";
    while(defender.get_max_shield() >= 1 && damage >= 1)
    {
        defender.set_max_shield(defender.get_max_shield() - 1);
        --damage;
    }
    while(defender.get_max_hull() >= 1 && damage >= 1)
    {
        defender.set_max_hull(defender.get_max_hull() - 1);
        --damage;
    }
    std::cout << defender.get_max_hull() << "\n\n";
    if (defender.get_max_hull() <= 0)
    {
        std::cout << "SHIP DESTROYED";
        ships_vector.erase(ships_vector.begin() + i);
    }

    al_flip_display();
}



