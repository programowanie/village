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