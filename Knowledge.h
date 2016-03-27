#pragma once
#include <vector>
#include <fstream>
#include <stdio.h>
#include <string>
#include "structs.h"
#include "Human.h"

using namespace std;

class Knowledge
{
private:
	static std::vector <string> names[2];
	static long long int _currentTime;

public:
	static void init();

//	Generatory
	static string name(gender);

//	Akcesory	
	static long long int currentTime() { return _currentTime; }
};