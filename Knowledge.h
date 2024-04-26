#pragma once

#include <vector>
#include <fstream>
#include <stdio.h>
#include <string>
#include "structs.h"

#define YEAR 360
#define MONTH 30
#define DAY 1

using namespace std;

class Knowledge
{
private:
	static std::vector <string> names[2];
	static long long int _currentTime;

public:
	static void init();
	static void tick() { _currentTime++; }

	//	Generatory
	static string name(gender);
	static float chanceToDie(gender gender, int age);

	//	Akcesory	
	static long long int currentTime() { return _currentTime; }
};