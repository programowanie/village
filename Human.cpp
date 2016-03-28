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
	
	// Zerujemy
	amountOfChildren = 0;
	_child = NULL;
	_isPregnat = false;
	lastChild = 0;

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
	ss << "%. Lat ";
	ss << age();
	ss << ". Ur. w roku ";
	ss << birthdate / YEAR;
	ss << ". Dzieci ";
	ss << amountOfChildren;

	return ss.str();
}

void Human::thinkAboutDeath()
{
	float howMuchIWantToDie = rand() % 2000;
	float fate = rand() % 2000;
	_isAlive = howMuchIWantToDie != fate;
}

void Human::meet(Human *another)
{
	if (_gender != another -> _gender)
	{
		// Spójrzmy na różnicę wieku
		int ageDifference = abs(age() - another -> age());
		float ageFactor = ageDifference > 40 ? 0 : (40 - ageDifference) / 40.;

		// Wyliczmy iloczyn rozwiązłości oraz atrakcyjności, rozumianej jako zdrowie
		float factor = 
			lechery * another -> lechery * 
			vitality * another -> vitality *
			ageFactor;
		
		// Sprawdzamy pecha
		int badLuck = rand() % 1000;
		bool pregnacy = badLuck < factor * 100;

		// A może jednak aborcja?
		if(age() < 15 || another -> age() < 15 || age() > 55 || another -> age() > 55)
			pregnacy = false;

		if(Knowledge::currentTime() - lastChild < MONTH * 9)
			pregnacy = false;

		// Poronienie
		if(rand() % 100 < 90)
			pregnacy = false;

		if (pregnacy)
		{
			Human child(this,another);
			amountOfChildren++;
			another -> amountOfChildren++;

			_child = &child;
			_isPregnat = true;
		}
	}
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

bool Human::isPregnat()
{
	return _isPregnat;
}

Human Human::takeChild()
{
	Human childToGive = _child;
	_child = NULL;
	_isPregnat = false;
	lastChild = Knowledge::currentTime();
	return childToGive;
}
