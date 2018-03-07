#include "Moveset.h"
#include "Ships.h"

void ship_collision()
{
    ALLEGRO_BITMAP *ship;
    ALLEGRO_COLOR color;
    int x1, y1, x2, y2;
    for (int i = 0; i < ships_vector.size(); ++i)
    {
        if (active_ship == &ships_vector[i])
            continue;

        if (ships_vector[i].get_ship_rotation() == 45 || ships_vector[i].get_ship_rotation() == 135
         || ships_vector[i].get_ship_rotation() == 225 || ships_vector[i].get_ship_rotation() == 315)
        {
            ship = al_load_bitmap("rotated_ship_template.png");
            x1 = ships_vector[i].get_ship_x() - 6;
            x2 = ships_vector[i].get_ship_x() + 36;
            y1 = ships_vector[i].get_ship_y() - 6;
            y2 = ships_vector[i].get_ship_y() + 40;
        }

        else
        {
            ship = al_load_bitmap("ship_template.png");
            x1 = ships_vector[i].get_ship_x();
            x2 = ships_vector[i].get_ship_x() + 30;
            y1 = ships_vector[i].get_ship_y();
            y2 = ships_vector[i].get_ship_y() + 30;
        }
        al_lock_bitmap(ship, al_get_bitmap_format(ship), ALLEGRO_LOCK_READONLY);
        for (int j = x1; j < x2; ++j)
        {
            for (int k = y1; k < y2; ++k)
            {
                for (int q = active_ship->get_ship_x(); q < active_ship->get_ship_x() + 30; ++q)
                    for (int w = active_ship->get_ship_y(); w < active_ship->get_ship_y() + 30; ++w)
                    {
                        if (q == j && w == k)
                        {
                            color = al_get_pixel(ship, j - x1, k - y1);
                            if (color.a != 0)
                            {
                                active_ship->set_ship_rotation(active_ship->get_ship_rotation() + 180);
                                move_ship(0.1);
                                active_ship->set_ship_rotation(active_ship->get_ship_rotation() + 180);
                                ship_collision();
                                return;
                            }
                        }
                    }
            }
        }
        al_unlock_bitmap(ship);
    }
}

void move_ship(double speed) // 2 w prawo to 2 do przodu i 2 w prawo i obrot
{
    switch (active_ship->get_ship_rotation())
    {
    case 0:
        active_ship->set_ship_y(active_ship->get_ship_y() - 30*speed); break;
    case 45:
        active_ship->set_ship_x(active_ship->get_ship_x() + 22*speed);
        active_ship->set_ship_y(active_ship->get_ship_y() - 22*speed); break;  // 22 because sqrt2 * 15 (so its not faster or slower when rotated(I hope))
    case 90:
        active_ship->set_ship_x(active_ship->get_ship_x() + 30*speed); break;
    case 135:
        active_ship->set_ship_x(active_ship->get_ship_x() + 22*speed);
        active_ship->set_ship_y(active_ship->get_ship_y() + 22*speed); break;
    case 180:
        active_ship->set_ship_y(active_ship->get_ship_y() + 30*speed); break;
    case 225:
        active_ship->set_ship_x(active_ship->get_ship_x() - 22*speed);
        active_ship->set_ship_y(active_ship->get_ship_y() + 22*speed); break;
    case 270:
        active_ship->set_ship_x(active_ship->get_ship_x() - 30*speed); break;
    case 315:
        active_ship->set_ship_x(active_ship->get_ship_x() - 22*speed);
        active_ship->set_ship_y(active_ship->get_ship_y() - 22*speed); break;
    default:
         std::cout << "Blad w poruszaniu sie, skrypt move_ship(int speed)\n";
         exit(-1);
         break;
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////// 1
void forward_1(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\forward_1.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(2);
    }
}

void lean_1_left(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\lean_1_left.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(5);
    }
}

void lean_1_right(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\lean_1_right.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(8);
    }
}

void hard_1_left(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\hard_1_left.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(11);
    }
}

void hard_1_right(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\hard_1_right.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(14);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////// 2
void forward_2(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\forward_2.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(32);
    }

}

void lean_2_left(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\lean_2_left.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(35);
    }
}

void lean_2_right(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\lean_2_right.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(38);
    }
}

void hard_2_left(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\hard_2_left.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(41);
    }
}

void hard_2_right(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\hard_2_right.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(44);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////// 3
void forward_3(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\forward_3.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(62);
    }

}

void lean_3_left(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\lean_3_left.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(65);
    }
}

void lean_3_right(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\lean_3_right.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(68);
    }
}

void hard_3_left(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\hard_3_left.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(71);
    }
}

void hard_3_right(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\hard_3_right.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50)
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(74);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////// 4
void forward_4(ALLEGRO_BITMAP *move_template, int template_x, int template_y, int x, int y)
{
    move_template = al_load_bitmap("movement templates\\forward_4.png");
    al_draw_bitmap(move_template, template_x, template_y, 0);

    if (x > template_x && x < template_x + 50 && y > template_y && y < template_y + 50) // zamien tu juz na 90 stopni, a potem jeszcze raz move ship()
    {
        active_ship->set_done(true);
        active_ship->set_active_movement(92);
    }
}

void moving_ships()
{
/////////////////////////////////////////////////////// speed 1:
    if (active_ship->get_active_movement() == 2)
    {
        move_ship(2);
        ship_collision();
    }
    if (active_ship->get_active_movement() == 5)
    {
        move_ship(2);
        active_ship->set_ship_rotation(active_ship->get_ship_rotation() - 45);
        move_ship(1);
        ship_collision();
    }
    if (active_ship->get_active_movement() == 8)
    {
        move_ship(2);
        active_ship->set_ship_rotation(active_ship->get_ship_rotation() + 45);
        move_ship(1);
        ship_collision();
    }
    if (active_ship->get_active_movement() == 11)
    {
        move_ship(2);
        active_ship->set_ship_rotation(active_ship->get_ship_rotation() - 90);
        move_ship(2);
        ship_collision();
    }
    if (active_ship->get_active_movement() == 14)
    {
        move_ship(2);
        active_ship->set_ship_rotation(active_ship->get_ship_rotation() + 90);
        move_ship(2);
        ship_collision();
    }
/////////////////////////////////////////////////////// speed 2:
    if (active_ship->get_active_movement() == 32)
    {
        move_ship(3);
        ship_collision();
    }
    if (active_ship->get_active_movement() == 35)
    {
        move_ship(3);
        active_ship->set_ship_rotation(active_ship->get_ship_rotation() - 45);
        move_ship(2);
        ship_collision();
    }
    if (active_ship->get_active_movement() == 38)
    {
        move_ship(3);
        active_ship->set_ship_rotation(active_ship->get_ship_rotation() + 45);
        move_ship(2);
        ship_collision();
    }
    if (active_ship->get_active_movement() == 41)
    {
        move_ship(3);
        active_ship->set_ship_rotation(active_ship->get_ship_rotation() - 90);
        move_ship(3);
        ship_collision();
    }
    if (active_ship->get_active_movement() == 44)
    {
        move_ship(3);
        active_ship->set_ship_rotation(active_ship->get_ship_rotation() + 90);
        move_ship(3);
        ship_collision();
    }
/////////////////////////////////////////////////////// speed 3:
    if (active_ship->get_active_movement() == 62)
    {
        move_ship(4);
        ship_collision();
    }
    if (active_ship->get_active_movement() == 65)
    {
        move_ship(4);
        active_ship->set_ship_rotation(active_ship->get_ship_rotation() - 45);
        move_ship(3);
        ship_collision();
    }
    if (active_ship->get_active_movement() == 68)
    {
        move_ship(4);
        active_ship->set_ship_rotation(active_ship->get_ship_rotation() + 45);
        move_ship(3);
        ship_collision();
    }
    if (active_ship->get_active_movement() == 71)
    {
        move_ship(4);
        active_ship->set_ship_rotation(active_ship->get_ship_rotation() - 90);
        move_ship(4);
        ship_collision();
    }
    if (active_ship->get_active_movement() == 74)
    {
        move_ship(4);
        active_ship->set_ship_rotation(active_ship->get_ship_rotation() + 90);
        move_ship(4);
        ship_collision();
    }
/////////////////////////////////////////////////////// speed 4:
    if (active_ship->get_active_movement() == 92)
    {
        move_ship(5);
        ship_collision();
    }
    if (active_ship->get_ship_x() < 0 || active_ship->get_ship_x() > 1250 ||
        active_ship->get_ship_y() < 0 || active_ship->get_ship_y() > 770)
    {
        for(int i = 0; i < ships_vector.size(); ++i)
        {
            if (active_ship == &ships_vector[i])
            {
                ships_vector.erase(ships_vector.begin() + i);
                break;
            }
        }
    }
}

void movement(int x, int y, int active_player, int phase)
{
    ALLEGRO_BITMAP *move_template;

    int template_x = 1050;
    int template_y = 100;
    int temp_y = 0;

    if (active_ship != NULL && active_ship->get_faction() == active_player && phase != 2)
        for (int i = 0; i < 20; ++i)
        {
            switch(active_ship->movement[i])
            {
            case 2:
                forward_1(move_template, template_x, template_y, x, y);
                break;
            case 5:
                lean_1_left(move_template, template_x, template_y, x, y);
                break;
            case 8:
                lean_1_right(move_template, template_x, template_y, x, y);
                break;
            case 11:
                hard_1_left(move_template, template_x, template_y, x, y);
                break;
            case 14:
                hard_1_right(move_template, template_x, template_y, x, y);
                break;


            case 32:
                forward_2(move_template, template_x, template_y, x, y);
                break;
            case 35:
                lean_2_left(move_template, template_x, template_y, x, y);
                break;
            case 38:
                lean_2_right(move_template, template_x, template_y, x, y);
                break;
            case 41:
                hard_2_left(move_template, template_x, template_y, x, y);
                break;
            case 44:
                hard_2_right(move_template, template_x, template_y, x, y);
                break;


            case 62:
                forward_3(move_template, template_x, template_y, x, y);
                break;
            case 65:
                lean_3_left(move_template, template_x, template_y, x, y);
                break;
            case 68:
                lean_3_right(move_template, template_x, template_y, x, y);
                break;
            case 71:
                hard_3_left(move_template, template_x, template_y, x, y);
                break;
            case 74:
                hard_3_right(move_template, template_x, template_y, x, y);
                break;


            case 92:
                forward_4(move_template, template_x, template_y, x, y);
                break;
            }
            template_x += 50;
            ++temp_y;
            if (temp_y == 3)
            {
                temp_y = 0;
                template_y += 50;
                template_x = 1050;
            }
        }
}

/*
1 - forward 1 green
2 - forward 1 white
3 - forward 1 red
4 - lean 1 left green
5 - lean 1 left white
6 - lean 1 left red
7 - lean 1 right green
8 - lean 1 right white
9 - lean 1 right red
10 - hard 1 left green
11 - hard 1 left white
12 - hard 1 left red
13 - hard 1 right green
14 - hard 1 right white
15 - hard 1 right red
16 - turn 1 green
17 - turn 1 white
18 - turn 1 red
// do 30, bo moze turn przy skretach
*/
