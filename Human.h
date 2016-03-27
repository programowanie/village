#pragma once
#include <string>
#include "Knowledge.h"
#include "structs.h"

using namespace std;

class Human
{
private:
	// Metryka
	string _name;
	gender _gender;
	long int birthdate, deathdate;
	bool alive;

	// Rodzice
	Human *father, *mother;

	// Cechy
	float lechery, vitality, aggresivity;

public:
//	Metody klasy
	static vector <Human> createSettlers(int n);

//	Metody obiektu
	Human(Human *father = NULL, Human *mother = NULL);
	int age();
	bool willDie();
	void die();

//	Akcesory	
	string name();
	enum gender gender();
};