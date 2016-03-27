#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Human.h"
#include "Knowledge.h"

void introduce(Human *);
void showTime();

int main(int argc, char const *argv[])
{
	Knowledge::init();

	vector <Human> villagers = Human::createSettlers(30);
	vector <Human> graveyard;

	// Zabijanie ludzi

	do
	{
		// Pokaż 
		showTime();

		// Życie mieszkańców
		printf("  Mieszkańcy (%i):\n", (int) villagers.size());
		for (int i = 0; i < villagers.size(); ++i)
		{
			introduce(&villagers[i]);
			if (villagers[i].willDie())
			{
				printf("\t  pora umierać\n");
				// Połóżmy Cię na cmentarz
				graveyard.push_back(villagers[i]);
				// I zapomnijmy, że byłeś
				villagers.erase(villagers.begin()+i);
			}
		}

		printf("  Na cmentarzu: %i\n", (int) graveyard.size());
		for (int i = 0; i < graveyard.size(); ++i)
			introduce(&graveyard[i]);

		Knowledge::tick();
	} while (Knowledge::currentTime() < 360 * 50);

	return 0;
}

void introduce(Human *human)
{
	printf("\t%s, %i lat\n",
			human -> name().c_str(),
			human -> age());
}

void showTime()
{
	int time = Knowledge::currentTime();
	printf("\n# Mamy dziś: %02i / %02i / %02i\n",
			time % MONTH + 1,
			(time / MONTH) % 12 + 1,
			time / YEAR + 1);
}
