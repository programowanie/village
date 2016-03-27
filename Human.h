#pragma once
#include <string>
#include "Knowledge.h"
#include "structs.h"

using namespace std;

class Human
{
private:
	string _name;
	gender _gender;
	long int birthdate;
	Human *father, *mother;

public:
//	Metody klasy
	static vector <Human> createSettlers(int n);

//	Metody obiektu
	Human(Human *father = NULL, Human *mother = NULL);
	int age();
	bool willDie();

//	Akcesory	
	string name();
	enum gender gender();
};