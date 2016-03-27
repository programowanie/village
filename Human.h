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
	Human *father, *mother;
public:
	static Human* createSettlers(int n);

	Human();
//	~Human();
	string getName();
	enum gender getGender();	

	
};