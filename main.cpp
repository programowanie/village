#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Human.h"
#include "Knowledge.h"

int main(int argc, char const *argv[])
{
	Knowledge::init();

	vector <Human> villagers = Human::createSettlers(10);	// Mieszkańcy
	vector <Human> graveyard;								// i nieboszczyki

	// Pętla kolejnych dni
	do
	{
		// Przywitajmy nowy dzień
		int time = Knowledge::currentTime();
		printf("\n# Mamy dziś: %02i / %02i / %02i\n",
			time % MONTH + 1,
			(time / MONTH) % 12 + 1,
			time / YEAR + 1);

		printf("  W wiosce żyje %i mieszkańców. Na cmentarzu mamy %i kwater.\n",
			(int) villagers.size(),
			(int) graveyard.size() );

		// Spójrzmy co u naszych mieszkańców
		for (int i = 0; i < villagers.size(); ++i)
		{
			// Kto dziś umrze?
			if (villagers[i].willDie())
			{
				// Odbierzmy Ci życie
				villagers[i].die();

				// Połóżmy Cię na cmentarz
				graveyard.push_back(villagers[i]);

				// Wydrukujmy nekrolog
				printf("! W wieku lat %i umiera dziś %s.\n",
					villagers[i].age(),
					villagers[i].name().c_str()
				);

				// I zapomnijmy, że byłeś
				villagers.erase(villagers.begin()+i);
			}
		}

		//printf("  Na cmentarzu: %i\n", (int) graveyard.size());
		//for (int i = 0; i < graveyard.size(); ++i)
		//	introduce(&graveyard[i]);

		Knowledge::tick();

		if (!villagers.size())
		{
			printf("\n\n- Po %i latach istnienia, nasza wioska wymarła. Trochę smutno.\n", time / YEAR + 1);
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
