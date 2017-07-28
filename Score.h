#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

struct Score{
	string enemyName;
	int moves;
	string city;
	Score* next;
};


#endif
