#include "Human.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

Human* Human::createSettlers(int n)
{
	Human *settlers = new Human[n];
	return settlers;	
}

Human::Human()
{
	gender = rand() % 2 ? male : female;
	name = Knowledge::name(gender);
}

string Human::getName()
{
	return name;
}

gender Human::getGender()
{
	return gender;
}	
