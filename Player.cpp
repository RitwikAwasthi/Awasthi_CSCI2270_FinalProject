#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Enemy.h"
#include "Player.h"
#include "Score.h"
using namespace std;

int Player::getHealth(){
	return health;
};

int Player::getAttack(){
	return attack;
};

bool Player::isDead(){
	if(health <= 0){
		return true;
	}else{
		return false;
	}
};

void Player::heal(){
	if(health + 10 == 100){
		cout << "Cannot heal, close to full health!" << endl;
	}else{
		health = health + 10;
	}
	
};

void Player::damage(int attack1){
	health = health - attack1;
};

int Player::special(){
	int num = rand() % 30 + 1;
	return num;
};
