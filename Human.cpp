#include "Human.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#define YEAR 31536000

Human* Human::createSettlers(int n)
{
	Human *settlers = new Human[n];
	return settlers;	
}

Human::Human(Human *father, Human *mother)
{
	// Przypiszmy rodziców
	this -> father = father;
	this -> mother = mother;

	// Wylosujmy płeć
	gender = rand() % 2 == 0 ? male : female;
	
	// Nadajmy imię
	name = Knowledge::name(gender);

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

string Human::getName()
{
	return name;
}

gender Human::getGender()
{
	return gender;
}	
