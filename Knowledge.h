#pragma once
#include <vector>
#include <fstream>
#include <stdio.h>
#include <string>
#include "structs.h"

using namespace std;

class Knowledge
{
private:
	static std::vector <string> names[2];

public:
	static void init();
	static string name(gender);
};