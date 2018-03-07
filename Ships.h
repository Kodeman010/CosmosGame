#ifndef SHIPS_H
#define SHIPS_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <vector>
#include <fstream>

class Ships
{
    public:
        Ships(unsigned int max_attack, unsigned int max_evade, unsigned int max_hull, unsigned int max_shield,
              int faction, std::string type, std::string name, int ship_x, int ship_y, int ship_rotation, bool in_range)
        {
            this -> max_attack = max_attack;
            this -> max_evade = max_evade;
            this -> max_hull = max_hull;
            this -> max_shield = max_shield;
            this -> faction = faction;
            this -> type = type;
            this -> name = name;
            this -> ship_x = ship_x;
            this -> ship_y = ship_y;
            this -> ship_rotation = ship_rotation;
            this -> in_range = in_range;
        }


        int get_max_attack(){return max_attack;}
        int get_max_evade(){return max_evade;}
        int get_max_hull(){return max_hull;}
        int get_max_shield(){return max_shield;}
        int get_faction(){return faction;}
        std::string get_type(){return type;}
        std::string get_name(){return name;}
        int get_ship_x(){return ship_x;}
        int get_ship_y(){return ship_y;}
        int get_ship_rotation(){return ship_rotation;}
        int get_in_range(){return in_range;}
        int get_done(){return done;}
        int get_active_movement(){return active_movement;}

        void set_ship_x(int ship_x){this -> ship_x = ship_x;}
        void set_ship_y(int ship_y){this -> ship_y = ship_y;}
        void set_max_hull(unsigned int max_hull){this->max_hull = max_hull;}
        void set_max_shield(unsigned int max_shield){this->max_shield = max_shield;}
        void set_done(bool done){this -> done = done;}
        void set_active_movement(int active_movement){this -> active_movement = active_movement;}
        //void set_ship_rotation(int ship_rotation){this -> ship_rotation = ship_rotation;}
        void set_ship_rotation(int ship_rotation)
        {
            this -> ship_rotation = ship_rotation;
            if (ship_rotation < 0)
                this -> ship_rotation = 360 + ship_rotation;
            if (ship_rotation >= 360)
                this -> ship_rotation = ship_rotation - 360;
        }

        void set_in_range(bool in_range){this -> in_range = in_range;}

        void action();
        void moveset();

        int movement[20];

    protected:

    private:
        unsigned int max_attack;
        unsigned int max_evade;
        unsigned int max_hull;
        unsigned int max_shield;
        std::string type;
        std::string name;
        int faction;
        int ship_x;
        int ship_y;
        int ship_rotation;
        bool in_range;
        bool done;
        int active_movement;
};

extern std::vector <Ships> ships_vector;
extern Ships *active_ship;

void add_ship();
void save_ships();
void save_ships_movement();
void read_ships();
void read_movement(Ships &ships, int i);
void show_ships();

void load_ship_bitmap(Ships ships, ALLEGRO_BITMAP *&ship_bitmap);

#endif // SHIPS_H
