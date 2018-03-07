#include "Range.h"
#include "Ships.h"

#define BlockSize 30
#define Range 270
#define Range_big 380 // 0 90 180 and 270 have 1 side longer


void range_collision(int rotation)
{

    if (rotation == 0) range_collision_0();
    else if (rotation == 45) range_collision_45();
    else if (rotation == 90) range_collision_90();
    else if (rotation == 135) range_collision_135();
    else if (rotation == 180) range_collision_180();
    else if (rotation == 225) range_collision_225();
    else if (rotation == 270) range_collision_270();
    else if (rotation == 315) range_collision_315();
}

void range_logic(int x1, int y1, int x2, int y2, ALLEGRO_BITMAP *range)
{
    ALLEGRO_COLOR color;
    al_lock_bitmap(range, al_get_bitmap_format(range), ALLEGRO_LOCK_READONLY);

    for (int i = 0; i < ships_vector.size(); ++i)
        ships_vector[i].set_in_range(false);

    for (int i = x1; i < x2; ++i)
        for (int j = y1; j < y2; ++j)
        {
            color = al_get_pixel(range, i - x1, j - y1);


            if (color.a != 0)
                for (int k = 0; k < ships_vector.size(); ++k)
                {
                    if (&ships_vector[k] != active_ship && !ships_vector[k].get_in_range())
                        if (ships_vector[k].get_ship_x() <= i && ships_vector[k].get_ship_x() + BlockSize >= i
                        && ships_vector[k].get_ship_y() <= j && ships_vector[k].get_ship_y() + BlockSize >= j)
                        {
                            ships_vector[k].set_in_range(true);
                            std::cout << "\nZnalazlem!  " << k << " - " << ships_vector[k].get_type() << std::endl;
                            break;
                        }
                }
        }
    al_unlock_bitmap(range);
}

void range_collision_0()
{
    int x1 = active_ship->get_ship_x() - Range_big/2 + BlockSize/2 +1;
    int x2 = active_ship->get_ship_x() + Range_big/2 + BlockSize/2 +1;

    int y1 = active_ship->get_ship_y() - Range;
    int y2 = active_ship->get_ship_y() +1;

    ALLEGRO_BITMAP *range = al_load_bitmap("range\\range_0.png");
    al_draw_bitmap(range, active_ship->get_ship_x() - Range_big/2 + BlockSize/2, active_ship->get_ship_y() - Range, 0);

    range_logic(x1, y1, x2, y2, range);
}

void range_collision_45()
{
    ALLEGRO_BITMAP *range = al_load_bitmap("range\\range_45.png");
    al_draw_bitmap(range, active_ship->get_ship_x() + BlockSize - 4, active_ship->get_ship_y() - Range + 4, 0); //git

    int x1 = active_ship->get_ship_x() + BlockSize - 3;
    int x2 = active_ship->get_ship_x() + Range + BlockSize - 3;

    int y1 = active_ship->get_ship_y() - Range + 5;
    int y2 = active_ship->get_ship_y() + 5;

    range_logic(x1, y1, x2, y2, range);
}


void range_collision_90()
{
    int x1 = active_ship->get_ship_x() + BlockSize + 1;
    int x2 = active_ship->get_ship_x() + Range + BlockSize;

    int y1 = active_ship->get_ship_y() - Range_big/2 + BlockSize/2 + 1;
    int y2 = active_ship->get_ship_y() + Range_big/2 + BlockSize/2;

    ALLEGRO_BITMAP *range = al_load_bitmap("range\\range_90.png");
    al_draw_bitmap(range, active_ship->get_ship_x() + BlockSize, active_ship->get_ship_y() - Range_big/2 + BlockSize/2, 0);

    range_logic(x1, y1, x2, y2, range);
}

void range_collision_135()
{
    int x1 = active_ship->get_ship_x() + BlockSize - 3;
    int x2 = active_ship->get_ship_x() + Range + BlockSize - 3;

    int y1 = active_ship->get_ship_y() + BlockSize - 3;
    int y2 = active_ship->get_ship_y() + Range + BlockSize - 3;

    ALLEGRO_BITMAP *range = al_load_bitmap("range\\range_135.png");
    al_draw_bitmap(range, active_ship->get_ship_x() + BlockSize - 4, active_ship->get_ship_y() + BlockSize - 4, 0);

    range_logic(x1, y1, x2, y2, range);
}

void range_collision_180()
{
    int x1 = active_ship->get_ship_x() - Range_big/2 + BlockSize/2;
    int x2 = active_ship->get_ship_x() + Range_big/2 + BlockSize/2;

    int y1 = active_ship->get_ship_y() + BlockSize;
    int y2 = active_ship->get_ship_y() + Range + BlockSize*2;

    ALLEGRO_BITMAP *range = al_load_bitmap("range\\range_180.png");
    al_draw_bitmap(range, active_ship->get_ship_x() - Range_big/2 + BlockSize/2, active_ship->get_ship_y() + BlockSize, 0);

    range_logic(x1, y1, x2, y2, range);
}

void range_collision_225()
{
    int x1 = active_ship->get_ship_x() - Range + 4;
    int x2 = active_ship->get_ship_x() + BlockSize + 4;

    int y1 = active_ship->get_ship_y() + BlockSize - 3;
    int y2 = active_ship->get_ship_y() + Range + BlockSize - 4;

    ALLEGRO_BITMAP *range = al_load_bitmap("range\\range_225.png");
    al_draw_bitmap(range, active_ship->get_ship_x() - Range + 4, active_ship->get_ship_y() + BlockSize - 4, 0);

    range_logic(x1, y1, x2, y2, range);
}

void range_collision_270()
{
    int x1 = active_ship->get_ship_x() - Range;
    int x2 = active_ship->get_ship_x();

    int y1 = active_ship->get_ship_y() - Range_big/2 + BlockSize/2;
    int y2 = active_ship->get_ship_y() + Range_big/2 + BlockSize/2;

    ALLEGRO_BITMAP *range = al_load_bitmap("range\\range_270.png");
    al_draw_bitmap(range, active_ship->get_ship_x() - Range, active_ship->get_ship_y() - Range_big/2 + BlockSize/2, 0);

    range_logic(x1, y1, x2, y2, range);
}

void range_collision_315()
{
    int x1 = active_ship->get_ship_x() - Range + 5;
    int x2 = active_ship->get_ship_x() + 4;

    int y1 = active_ship->get_ship_y() - Range + 5;
    int y2 = active_ship->get_ship_y() + 4;

    ALLEGRO_BITMAP *range = al_load_bitmap("range\\range_315.png");
    al_draw_bitmap(range, active_ship->get_ship_x() - Range + 4, active_ship->get_ship_y() - Range + 4, 0);

    range_logic(x1, y1, x2, y2, range);
}






