#include <iostream>
#include <conio.h>
#include "Ships.h"
#include "Game.hpp"
#include "Moveset.h"
#define BlockSize 30

std::vector <Ships> ships_vector;

Ships *active_ship;
ALLEGRO_BITMAP *range;
/*
void add_ship()
{
    Ships ships(2, 2, 3, 0, 1, "Frigate", "name1", 100, 550, 0, 0); // 500 700
    for (int i = 0; i < 20; ++i)
        ships.movement[i] = 0;
    ships.movement[0] = 2;
    ships.movement[1] = 5;
    ships.movement[2] = 62;
    ships.movement[3] = 92;
    ships.movement[4] = 8;
    ships.movement[5] = 32;
    ships.movement[6] = 11;
    ships.movement[7] = 14;

    Ships ships2(3, 3, 2, 1, 1, "Cruiser", "name2", 135, 400, 315, 0); // 300 700
    for (int i = 0; i < 20; ++i)
        ships2.movement[i] = 0;
    ships2.movement[0] = 35;
    ships2.movement[1] = 38;
    ships2.movement[2] = 41;
    ships2.movement[3] = 44;
    ships2.movement[4] = 32;

    Ships ships3(3, 3, 2, 1, 1, "Cruiser", "name3", 490, 450, 180, 0); // 400 200
    for (int i = 0; i < 20; ++i)
        ships3.movement[i] = 0;
    ships3.movement[0] = 62;
    ships3.movement[1] = 65;
    ships3.movement[2] = 68;
    ships3.movement[3] = 71;
    ships3.movement[4] = 74;

    Ships ships4(3, 3, 2, 1, 1, "Cruiser", "name4", 400, 320, 270, 0); // 400 200
    for (int i = 0; i < 20; ++i)
        ships4.movement[i] = 0;

    Ships ships5(3, 3, 2, 1, 1, "Cruiser", "name5", 350, 320, 0, 0); // 400 200
    for (int i = 0; i < 20; ++i)
        ships5.movement[i] = 0;

    ships_vector.push_back(ships);
    ships_vector.push_back(ships2);
    ships_vector.push_back(ships3);
    ships_vector.push_back(ships4);
    ships_vector.push_back(ships5);
}
*/
void save_ships()
{
    std::fstream file;
    file.open("ships/active_ships.txt", std::ios::out);
    if (file.good() == false)
    {
        std::cout << "ships/active_ships.txt was not found";
        exit(0);
    }
    std::vector <Ships>::iterator j = ships_vector.begin();
    int i = 0;
    while (1)
    {
        file << ships_vector[i].get_max_attack() << std::endl;
        file << ships_vector[i].get_max_evade() << std::endl;
        file << ships_vector[i].get_max_hull() << std::endl;
        file << ships_vector[i].get_max_shield()<< std::endl;
        file << ships_vector[i].get_faction() << std::endl;
        file << ships_vector[i].get_type() << std::endl;
        file << ships_vector[i].get_name() << std::endl;
        file << ships_vector[i].get_ship_x() << std::endl;
        file << ships_vector[i].get_ship_y() << std::endl;
        file << ships_vector[i].get_ship_rotation() << std::endl;
        file << ships_vector[i].get_in_range() << std::endl;

        for (int k = 0; k < 10; ++k)
            file << std::endl;

        if ((j != ships_vector.end()) && (next(j) == ships_vector.end()))
            break;

        ++i;
        ++j;
    }
    file.close();
    file.clear();
    save_ships_movement();
}

void save_ships_movement()
{
    std::fstream file;
    file.open("ships/active_ships_movement.txt", std::ios::out);
    if (file.good() == false)
    {
        std::cout << "ships/active_ships_movement.txt was not found";
        exit(0);
    }
    std::vector <Ships>::iterator j = ships_vector.begin();
    int i = 0;

    while (1)
    {
        for (int k = 0; k < 20; ++k)
            file << ships_vector[i].movement[k] << std::endl;

        if ((j != ships_vector.end()) && (next(j) == ships_vector.end()))
            break;

        ++i;
        ++j;
    }
    file.close();
    file.clear();
}

void read_ships()
{
    ships_vector.clear();
    if (ships_vector.empty() == false) // error handling
    {
        std::cout << "Error has occured in ships_vector in void read_ships()\n\n";
        exit(0);
    }

    std::fstream file;
    file.open("ships/active_ships.txt", std::ios::in);
    if (file.good() == false)
    {
        std::cout << "ships/active_ships.txt was not found";
        exit(0);
    }
    std::string line;
    int line_number = 1;
    int i = 0;

    unsigned int max_attack = 0, max_evade = 0, max_hull = 0, max_shield = 0;
    int faction = 0;
    std::string type = "", name = "";
    int ship_x = 0, ship_y = 0, ship_rotation = 0;
    bool in_range = false;

    while(getline(file, line))
    {
        switch(line_number)
        {
            case 1: max_attack = atoi(line.c_str()); break;
            case 2: max_evade = atoi(line.c_str()); break;
            case 3: max_hull = atoi(line.c_str()); break;
            case 4: max_shield = atoi(line.c_str()); break;
            case 5: faction = atoi(line.c_str()); break;
            case 6: type = line; break;
            case 7: name = line; break;
            case 8: ship_x = atoi(line.c_str()); break;
            case 9: ship_y = atoi(line.c_str()); break;
            case 10: ship_rotation = atoi(line.c_str()); break;
            case 11: in_range = atoi(line.c_str()); break;
        }

        line_number ++;
        if (line_number % 21 == 0)
        {
            line_number = 0;

            Ships ships(max_attack, max_evade, max_hull, max_shield, faction, type, name, ship_x, ship_y, ship_rotation, in_range);
            read_movement(ships, i);
            ships_vector.push_back(ships);
            ++i;
        }
    }
    file.close();
    file.clear();
}

void read_movement(Ships &ships, int i)
{
    std::fstream file2;
    file2.open("ships/active_ships_movement.txt", std::ios::in);
    if (file2.good() == false)
    {
        std::cout << "ships/active_ships_movement.txt was not found";
        exit(0);
    }
    std::string line;
    int line_number = 1;
    int j = 0;

    int movement[20];
    while(getline(file2, line) && line_number <= i*20+20)
    {
        if(line_number >= i*20+1)
        {
            ships.movement[j] = atoi(line.c_str());
            ++j;
        }
        ++line_number;
    }
    file2.close();
    file2.clear();
}


void show_ships()
{
    system("cls");
    using namespace std;
    cout << "Available ships:   Attack    Evade    Hull    Shield";
    for (int i = 0; i < ships_vector.size(); ++i)
    {
        gotoxy(1, i*4 + 5);
        cout << ships_vector[i].get_type() << " " << ships_vector[i].get_name();
        gotoxy(21, i*4+5);
        SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 12);
        cout << ships_vector[i].get_max_attack() << "       ";
        gotoxy(30, i*4+5);
        SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 10);
        cout << ships_vector[i].get_max_evade() <<  "         ";
        gotoxy(39, i*4+5);
        SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 14);
        cout << ships_vector[i].get_max_hull() <<   "        ";
        gotoxy(48, i*4+5);
        SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 11);
        cout << ships_vector[i].get_max_shield();
        SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 7);
    }
}

void load_ship_bitmap(Ships ships, ALLEGRO_BITMAP *&ship_bitmap)
{
    if (ships.get_type() == "Frigate")
    {
        if (ships.get_faction() == 0)
            ship_bitmap = al_load_bitmap("ships/frigate_blue.png");
        else if (ships.get_faction() == 1)
            ship_bitmap = al_load_bitmap("ships/frigate_red.png");
    }
    else if (ships.get_type() == "Cruiser")
    {
        if (ships.get_faction() == 0)
            ship_bitmap = al_load_bitmap("ships/cruiser_blue.png");
        else if (ships.get_faction() == 1)
            ship_bitmap = al_load_bitmap("ships/cruiser_red.png");
    }
}

