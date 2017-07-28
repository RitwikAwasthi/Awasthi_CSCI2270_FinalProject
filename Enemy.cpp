#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Enemy.h"
#include "Score.h"
using namespace std;

Enemy::Enemy(){
	int temp = rand() % count;
	Enemy::name = names[temp];
	Enemy::setDamage();
	for(int i = temp; i < count;i++){
		names[i] = names[i+1];
	}
	count = count - 1;
};

string Enemy::getName(){
		return name;
};

int Enemy::getHealth(){
	return health;
};

void Enemy::setDamage(){
	damage = rand() % 20 + 10;
};

int Enemy::getDamage(){
	return damage;
};

void Enemy::Attack(int attack){
	health = health - attack;
};

bool Enemy::isDead(){
	if(health <= 0){
		return true;
	}else{
		return false;
	}
};

int Enemy::doMove(){
	int enemyMove = rand() % 3 + 1;
	move++;
	if(enemyMove == 1){
		int atk = rand() % 25 + 1;
		cout << "You were attacked by " << name << " for " << atk << " damage!" << endl;
		return atk;
	}else if(enemyMove == 2){
		cout << name << " healed for 10!" << endl;
		return -10;
	}else if(enemyMove == 3){
		cout << name << " got confused and hurt himself!" << endl;
		return 0;
	}
};

void Enemy::heal(){
	health = health + 10;
};

int Enemy::getMoves(){
	return move;
};

