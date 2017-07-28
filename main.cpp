#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Enemy.h"
#include "Score.h"
#include "Player.h"

using namespace std;

struct cities{ //Struct used to store 5 random cities
	string city1 = "";
	string city2 = "";
	string city3 = "";
	string city4 = "";
	string city5 = "";
};

struct Graph{ //Graph node
	string vertex;
	Graph* edge1;
	Graph* edge2;
	Graph* edge3;
	Graph* edge4;
	string enviro;
	bool dead = false;
	Enemy CityEnemy;
	bool gameOver = false;
};

void createMap(Graph* a, Graph* b, Graph* c, Graph* d, Graph* e, string city1, string city2, string city3, string city4, string city5);
void complete(Graph* current);
bool checkIfAllDead(Graph* a);
Score* addScore(Score* head, int Emoves, string cName, string eName);
void printScore(Score* head);
cities* randomCities(string arr[]);

int main(){ //Driver function
	string cities1[20] = {"London", "Toronto", "Atlanta", "Chicago", "Mumbai", "Shanghai", "Delhi", "Rotterdam", "Munich", "Geneva" , "Tehran", "Istanbul", "Orlando", "Denver", "Sydney", "Paris", "Keiv", "Moscow", "Seoul", "Juneau"};
	Score* head = nullptr;
	bool gameOver = false;
	system("clear");
	Player player1;
	Graph* a = new Graph;
	Graph* b = new Graph;
	Graph* c = new Graph;
	Graph* d = new Graph;
	Graph* e = new Graph;
	cities* citylist = randomCities(cities1);
	createMap(a,b,c,d,e, citylist->city1, citylist->city2, citylist->city3, citylist->city4, citylist->city5); //Created the map
	Graph* current = a;
	while(!current->dead){ //While enemy is not dead
		string space;
		string userinput;
		cout << "////////////////////" << endl;
		cout << current->vertex << endl;
		cout << "////////////////////" << endl;
		cout << "Enemy: " << current->CityEnemy.getName() << endl;
		cout << "Health: " << current->CityEnemy.getHealth() << endl;
		cout << "Attack: " << current->CityEnemy.getDamage() << endl;
		cout << "////////////////////" << endl;
		cout << "Your health: " << player1.getHealth() << endl;
		cout << "Your attack: " << player1.getAttack() << endl;
		cout << "////////////////////" << endl << endl;
		cout << "Make a move! Press 1 to Attack, 2 to Heal, 3 for Special" << endl;
		cin >> userinput;
		cin.ignore();
		if(stoi(userinput) == 1){ //Getting input and decideing what to do
			system("clear");
			cout << "You Attacked for 20 damage!" << endl;
			current->CityEnemy.Attack(player1.getAttack());
			int eMove = current->CityEnemy.doMove(); //Enemy move
			if(eMove > 0){
				player1.damage(eMove);
			}else if(eMove < 0){
				current->CityEnemy.heal();
			}else if(eMove == 0){
				current->CityEnemy.Attack(15);
			}
			cout << "Press any key and enter to continue" << endl;
			cin >> space;
		}else if(stoi(userinput) == 2){ //Same as above
			system("clear");
			player1.heal();
			cout << "You healed for 10 HP!" << endl;
			int eMove = current->CityEnemy.doMove();
			if(eMove > 0){
				player1.damage(eMove);
			}else if(eMove < 0){
				current->CityEnemy.heal();
			}else if(eMove == 0){
				current->CityEnemy.Attack(15);
			}
			cout << " Press any key and enter to continue" << endl;
			cin >> space;
		}else if(stoi(userinput) == 3){
			system("clear");
			int spell = player1.special();
			current->CityEnemy.Attack(spell);
			cout << "You used your special attack for " << spell << " damage!" << endl;
			int eMove = current->CityEnemy.doMove();
			if(eMove > 0){
				player1.damage(eMove);
			}else if(eMove < 0){
				current->CityEnemy.heal();
			}else if(eMove == 0){
				current->CityEnemy.Attack(15);
			}
			cout << " Press any key and enter to continue" << endl;
			cin >> space;
		}else{
			cout << "Invalid Character" << endl;
		}
		if(checkIfAllDead(current)){ //Checks if you have won the game yet
			printScore(head);
			cout << "YOU WIN! Thanks for playing!" << endl;
			cout << "Goodbye!" << endl;
			return 1;
		}
		if((!player1.isDead()) && current->CityEnemy.isDead()){ //If yoou kill the enemy
				head = addScore(head, current->CityEnemy.getMoves(), current->vertex, current->CityEnemy.getName());
				complete(current);
				cout << "Choose a City to go to: " << endl;
				cout << "1. " << current->edge1->vertex << endl;
				cout << "2. " << current->edge2->vertex << endl;
				cout << "3. " << current->edge3->vertex << endl;
				cout << "4. " << current->edge4->vertex << endl;
				string changeMove;
				cin >> changeMove;
				int moveNum = stoi(changeMove);
				bool invalid = false;
				while(!invalid){
					if(moveNum == 1){
						current = current->edge1;
						break;
					}else if(moveNum == 2){
						current = current->edge2;
						break;
					}else if(moveNum == 3){
						current = current->edge3;
						break;
					}else if(moveNum == 4){
						current = current->edge4;
						break;
					}else{
						cout << "Invalid Move" << endl;
						invalid = true;
					}
				}
		}else if(player1.isDead() && (!current->CityEnemy.isDead())){ //If you die
			printScore(head);
			cout << "You Died!" << endl;
			cout << "Game Over" << endl;
			gameOver = true;
			break;
		}else if(player1.isDead() && current->CityEnemy.isDead()){ //If both die in same turn
			printScore(head);
			cout << "Draw" << endl;
			gameOver = true;
			break;
		}
		system("clear");
	}

	if(gameOver){
		cout << "GoodBye!" << endl;
	}
};

void createMap(Graph* a, Graph* b, Graph* c, Graph* d, Graph* e, string city1, string city2, string city3, string city4, string city5){ //Creates graph of the cities and links them together, also assigns them names
	a->edge1 = b;
	a->edge2 = c;
	a->edge3 = d;
	a->edge4 = e;
	b->edge1 = a;
	b->edge2 = c;
	b->edge3 = d;
	b->edge4 = e;
	c->edge1 = a;
	c->edge2 = b;
	c->edge3 = d;
	c->edge4 = e;
	d->edge1 = a;
	d->edge2 = b;
	d->edge3 = c;
	d->edge4 = e;
	e->edge1 = a;
	e->edge2 = b;
	e->edge3 = c;
	e->edge4 = d;
	a->vertex = city1;
	b->vertex = city2;
	c->vertex = city3;
	d->vertex = city4;
	e->vertex = city5;
};

void complete(Graph* current){ //Appends a complete tag to the end of the city
	string temp = current->vertex;
	current->vertex = temp + " (Completed)";
};

bool checkIfAllDead(Graph* a){ //Checks if you killed all the enemies
	bool one;
	bool two;
	bool three;
	bool four;
	bool five;
	if(a->CityEnemy.isDead()){
		one = true;
	}
	if(a->edge1->CityEnemy.isDead()){
		two = true;
	}
	if(a->edge2->CityEnemy.isDead()){
		three = true;
	}
	if(a->edge3->CityEnemy.isDead()){
		four = true;
	}
	if(a->edge4->CityEnemy.isDead()){
		five = true;
	}

	if(one && two && three && four && five){
		return true;
	}else{
		return false;
	}
};

Score* addScore(Score* head, int Emoves, string cName, string eName){ //Adds the score to the Linked List, returns the head.
	if(head == nullptr){
		Score* newScore = new Score;
		newScore->next = nullptr;
		newScore->moves = Emoves;
		newScore->enemyName = eName;
		newScore->city = cName;
		head = newScore;
	}else{
		Score* temp = head;
		while (temp->next != nullptr){
			temp = temp->next;
		}
		Score* newScore = new Score;
		temp->next = newScore;
		newScore->next = nullptr;
		newScore->moves = Emoves;
		newScore->enemyName = eName;
		newScore->city = cName;
	}

	return head;
};

void printScore(Score* head){ //Prints all the scores
	Score* temp = head;
	if(temp == nullptr){
		cout << "No scores stored on record!" << endl;
	}else{
		while(temp != nullptr){
			 cout << "#####DEFEATED#######" << endl;
			 cout << "City: " << temp->city << endl;
			 cout << "Enemy: " << temp->enemyName << endl;
			 cout << "In " << temp->moves << " moves" << endl;
			 temp = temp->next;
		}
		cout << "########END#########" << endl;
	}
};

cities* randomCities(string arr[]){ //returns 5 random cities for the game to use
	string* cityarray = arr;
	int count = 19;
	cities* newCity = new cities;
	int temp = rand() % count;
	newCity->city1 = cityarray[temp];
	for(int i = temp; i < count; i++){
		cityarray[i] = cityarray[i+1];
	}
	count = count-1;
	temp = rand() % count;
	newCity->city2 = cityarray[temp];
	for(int i = temp; i < count; i++){
		cityarray[i] = cityarray[i+1];
	}
	count = count-1;
	temp = rand() % count;
	newCity->city3 = cityarray[temp];
	for(int i = temp; i < count; i++){
		cityarray[i] = cityarray[i+1];
	}
	count = count-1;
	temp = rand() % count;
	newCity->city4 = cityarray[temp];
	for(int i = temp; i < count; i++){
		cityarray[i] = cityarray[i+1];
	}
	count = count-1;
	temp = rand() % count;
	newCity->city5 = cityarray[temp];
	for(int i = temp; i < count; i++){
		cityarray[i] = cityarray[i+1];
	}
	count = count-1;
	return newCity;
};
