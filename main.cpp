#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Human.h"
#include "Knowledge.h"

int main(int argc, char const *argv[])
{
	Knowledge::init();

	vector <Human> villagers = Human::createSettlers(100);	// Mieszkańcy
	vector <Human> graveyard;								// i nieboszczyki

	// Pętla kolejnych dni
	do
	{
		int time = Knowledge::currentTime();
		char timestamp[128];
		sprintf(timestamp, "[%02i/%02i/%02i]",
			time % MONTH + 1,
			(time / MONTH) % 12 + 1,
			time / YEAR + 1);

		// Nowy rok?
		if (time % YEAR == 0)
		{
			printf("  %s Świętujemy Nowy Rok. Rok %i. W wiosce żyje %i mieszkańców.\n",
				timestamp,
				time / YEAR + 1,
				(int) villagers.size());
		}

		// Spójrzmy co u naszych mieszkańców
		for (int i = 0; i < villagers.size(); ++i)
		{
			// Spotkanie. Każdy raz dziennie kogoś spotyka.
			if (villagers.size())
			{
				int whom = rand() % villagers.size();
				// Co jeśli spotkam siebie?
				if (whom == i)
				{
					// Pomyślę o śmierci
					villagers[i].thinkAboutDeath();
					// I może postanowię umrzeć.
					if (!villagers[i].isAlive())
					{
						printf("\t%s postanawia umrzeć.\n", villagers[i].name().c_str());
					}
				}
				else
				{
					//printf("\t%s spotyka %s\n", 
					//	villagers[i].name().c_str(),
					//	villagers[whom].name().c_str());
				}
			}


			// Kto dziś umrze?
			if (villagers[i].willDie())
			{
				// Odbierzmy Ci życie
				villagers[i].die();

				// Połóżmy Cię na cmentarz
				graveyard.push_back(villagers[i]);

				// Wydrukujmy nekrolog
				printf("\tW wieku lat %i umiera %s\n",
					villagers[i].age(),
					villagers[i].story().c_str()
				);

				// I zapomnijmy, że byłeś
				villagers.erase(villagers.begin()+i);
			}

			
			/* code */
			//}
		}

		// Zacznijmy nowy dzień
		if (villagers.size()) Knowledge::tick();
		else
		{
			printf("  %s Po %i latach istnienia, nasza wioska wymarła. Garść statystyk:\n\n", timestamp, time / YEAR + 1);
			break;
		}
	} while (Knowledge::currentTime() < 360 * 100);

	// Statystyki na koniec
	float avg_lifetime = 0;
	for (int i = 0; i < graveyard.size(); ++i)
		avg_lifetime += graveyard[i].age();
	avg_lifetime /= graveyard.size();
	printf("- Średnia długość życia wyniosła %.0f lat\n", avg_lifetime);

	return 0;
}
