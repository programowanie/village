#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Human.h"
#include "Knowledge.h"

int main(int argc, char const *argv[])
{
	Knowledge::init();

	int years_of_simulation = 10000;
	int amount_of_settlers = 100;

	vector <Human> villagers = Human::createSettlers(amount_of_settlers);	// Mieszkańcy
	vector <Human> graveyard;												// i dziady

	int born = 0, died = 0; // Statystyki

	// Pętla kolejnych dni
	do
	{
		int time = Knowledge::currentTime();
		char timestamp[128];
		sprintf(timestamp, "[%02i/%02i/%04i]",
			time % MONTH + 1,
			(time / MONTH) % 12 + 1,
			time / YEAR + 1);

		// Nowy mamy rok?
		if (time % YEAR == 0)
		{
			float avg_lifetime = 0;
			for (int i = 0; i < villagers.size(); ++i)
				avg_lifetime += villagers[i].age();
			avg_lifetime /= villagers.size();
			printf("  %s %5i villagers [+%3i, -%3i], avg. age %.0f yrs. \t%5.0f\n",
				timestamp,
				(int) villagers.size(),
				born,
				died,
				avg_lifetime,
				((float) born-died) / (float) villagers.size()*1000);
			born = 0;
			died = 0;
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
						//printf("\t%s postanawia umrzeć.\n", villagers[i].name().c_str());
					}
				}
				else
				{
					villagers[i].meet(&villagers[whom]);
					if (villagers[i].isPregnat())
					{
						Human newHuman = villagers[i].takeChild();
						/*printf("\t%s [%i l] i %s [%i l] mają dziecko imieniem %s\n",
							villagers[i].name().c_str(),
							villagers[i].age(),
							villagers[whom].name().c_str(),
							villagers[whom].age(),
							newHuman.name().c_str());*/

						villagers.push_back(newHuman);
						born++;
					}
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
				died++;

				// Połóżmy Cię na cmentarz
				graveyard.push_back(villagers[i]);

				// Wydrukujmy nekrolog
				//printf("\tW wieku lat %i umiera %s\n",
				//	villagers[i].age(),
				//	villagers[i].story().c_str()
				//);

				// I zapomnijmy, że byłeś
				villagers.erase(villagers.begin()+i);
			}
		}

		// Zacznijmy nowy dzień
		if (villagers.size()) Knowledge::tick();
		else
		{
			printf("  %s Po %i latach istnienia, nasza wioska wymarła.\n\n", timestamp, time / YEAR + 1);
			break;
		}
	} 
	while (Knowledge::currentTime() < YEAR * years_of_simulation);

	// Statystyki na koniec
	float avg_lifetime = 0;
	for (int i = 0; i < graveyard.size(); ++i)
		avg_lifetime += graveyard[i].age();
	avg_lifetime /= graveyard.size();
	Human lastPerson = graveyard.back();

	printf("Garść statystyk:\n");
	printf("- Średnia długość życia wyniosła %.0f lat\n", avg_lifetime);
	printf("- Na cmentarzu leży %i osób\n", (int) graveyard.size());
	printf("- Ostatni mieszkaniec to %s\n", lastPerson.story().c_str());

	return 0;
}
