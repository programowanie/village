#include "Human.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

vector <Human> Human::createSettlers(int n)
{
	vector <Human> settlers;
	Human *_settlers = new Human[n];
	copy(&_settlers[0], &_settlers[n], back_inserter(settlers));
	return settlers;	
}

Human::Human(Human *father, Human *mother)
{
	// Przypiszmy rodziców
	this -> father = father;
	this -> mother = mother;

	// Wylosujmy płeć
	_gender = rand() % 2 == 0 ? male : female;
	
	// Nadajmy imię
	_name = Knowledge::name(_gender);

	// Ustalamy wiek
	birthdate = mother != NULL
		? Knowledge::currentTime()
		: Knowledge::currentTime() - 15 * YEAR - rand() % 15 * YEAR;
}

int Human::age()
{
	long long int time = Knowledge::currentTime() - birthdate;
	return time / YEAR;
}

bool Human::willDie()
{
	float chanceToDie = Knowledge::chanceToDie(_gender,age());
	float fate = (rand() % 1000000) / 1000000.;
	return fate < chanceToDie;
}

string Human::name()
{
	return _name;
}

gender Human::gender()
{
	return _gender;
}	
