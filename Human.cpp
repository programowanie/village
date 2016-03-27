#include "Human.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

#pragma mark [ Metody klasy ]

vector <Human> Human::createSettlers(int n)
{
	vector <Human> settlers;
	Human *_settlers = new Human[n];
	copy(&_settlers[0], &_settlers[n], back_inserter(settlers));
	return settlers;	
}


#pragma mark [ Metody obiektu ]

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
		: Knowledge::currentTime() - rand() % 30 * YEAR;
	deathdate = NULL;

	// Przyznajemy cechy
	lechery = rand() % 100 / 100.;
	vitality = rand() % 100 / 100.;
	aggresivity = rand() % 100 / 100.;

	// Ożywiamy
	_isAlive = true;
}

int Human::age()
{
	long long int time = (_isAlive ? Knowledge::currentTime() : deathdate ) - birthdate;
	return time / YEAR;
}

bool Human::willDie()
{
	float chanceToDie = Knowledge::chanceToDie(_gender,age());
	float fate = (rand() % 1000000) / 1000000.;
	return !_isAlive || fate < chanceToDie;
}

void Human::die()
{
	deathdate = Knowledge::currentTime();
	_isAlive = false;
}

string Human::story()
{
	ostringstream ss;
	ss << _name;
	if (!_gender)
		ss << ". Mężczyzna.";
	else
		ss << ". Kobieta.";
	ss << " Rozwiązłość ";
	ss << lechery*100;
	ss << "%. Żywotność ";
	ss << vitality*100;
	ss << "%. Agresywność ";
	ss << aggresivity*100;
	ss << "%.";

	return ss.str();
}

void Human::thinkAboutDeath()
{
	float howMuchIWantToDie = rand() % 2000;
	float fate = rand() % 2000;
	_isAlive = howMuchIWantToDie != fate;
}

#pragma mark [ Akcesory ]

string Human::name()
{
	return _name;
}

gender Human::gender()
{
	return _gender;
}	

bool Human::isAlive()
{
	return _isAlive;
}
