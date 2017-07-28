#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Score.h"

using namespace std;

class Enemy{
	private:
		int health = 100;
		int damage;
		string name;
		int move;
		int count = 19;
		string names[20] = {"Xander", "Heinrick", "Keiran", "Zindo", "Karayan", "Nightshade", "Elissa", "Raura", "Keina", "Skinner", "Violet", "Moldark", "Weiss", "Aimez", "Wood", "Gnash", "Cane", "Mortem", "Morgan", "Lina"};
	public:
		Enemy();
		void setDamage();
		int getHealth();
		void Attack(int attack);
		string getName();
		int doMove();
		int getMoves();
		int getDamage();
		bool isDead();
		void heal();
};

#endif
