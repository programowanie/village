#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Human.h"
#include "Knowledge.h"

int main(int argc, char const *argv[])
{
	Knowledge::init();

	Human *settlers = Human::createSettlers(5);
	for (int i = 0; i < 5; ++i)
	{
		printf("Osadnik %i\t%s [%i lat]\n", 
			i, 
			settlers[i].getName().c_str(),
			settlers[i].age());
	}

	return 0;
}