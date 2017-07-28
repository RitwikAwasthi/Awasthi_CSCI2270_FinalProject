#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Score.h"

using namespace std;

class Player{
	private:
		int health = 100;
		int attack = 20;
	public:
		int getHealth();
		int getAttack();
		Score* first;
		bool isDead();
		void heal();
		int special();
		void damage(int attack1);
};

#endif
