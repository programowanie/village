#include "Knowledge.h"

using namespace std;

vector <string> Knowledge::names[2];
long long int Knowledge::_currentTime = 0;

void Knowledge::init()
{
	srand(time(NULL));
	ifstream file;

	// Imiona męskie
	file.open("data/names_men.csv");
	copy(istream_iterator<string>(file),
         istream_iterator<string>(),
         back_inserter(names[male]));
	file.close();

	// Imiona kobiece
	file.open("data/names_women.csv");
	copy(istream_iterator<string>(file),
         istream_iterator<string>(),
         back_inserter(names[female]));
	file.close();
}

string Knowledge::name(gender gender)
{
	return names[gender][rand() % names[gender].size()];
}

float Knowledge::chanceToDie(gender gender, int age)
{
	if(age < 5) 		return .002;
	else if(age < 25)	return .0002;
	else if(age < 40)	return .00002;
	else if(age < 55)	return .0002;
	else				return .002;
}