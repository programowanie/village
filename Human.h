#pragma once
#include <string>
#include "Knowledge.h"
#include "structs.h"

using namespace std;

class Human
{
private:
	string name;
	gender gender;
	long int birthdate;
	Human *father, *mother;

public:
//	Metody klasy
	static Human* createSettlers(int n);

//	Metody obiektu
	Human(Human *father = NULL, Human *mother = NULL);
	int age();

//	Akcesory	
	string getName();
	enum gender getGender();
};