#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*****************************************************************
#      Program Name : Luyten Lingering (working title)           # 
#            Author : Brandon M. {BMo} with additions by Ben     #
#   Current Version : 0.5 beta                                   #
#     Creation Date : 11/01/17                                   #
#     Last Revision : 11/19/17                                   #
#                                                                #
#           Purpose : Resource planning and strategy game based  #
#                     off Hamurabi written by Doug Dyment in     #
#                     1968.                                      # 
*****************************************************************/

/* Global Variables  */
int food, tempFood, foodReplant, population, happyness, popFoodInput, popFoodRatio; 
int year, endCondition;
int ErrChk;
char answer[1024];
char playerName[1024];
char colonyName[1024];

/* Create a pseudo random number  */
int rando(int MIN, int MAX)
{
    srand(time(0));
    return MIN + rand() % (MAX + 1 - MIN);
}

void checkAnswer(int section)
{
	if (section == 1)
	{
		ErrChk = 1;
		while(ErrChk == 1)
		{
			printf("How much food do you want to feed your population?: ");
			scanf("%d", &popFoodInput);
			if (food - popFoodInput >= 0)
			{
				printf("Feed population %i bushels of food?              Result: %i Bushels left. [Y/N]\n", popFoodInput, food - popFoodInput);
				scanf("%s", answer);
				if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0)
				{
					tempFood = food - popFoodInput;
					printf("How much food will you plant?: ");
					scanf("%d", &foodReplant);
					if (tempFood - foodReplant >=0)
					{
						printf("Replant %i bushels of food?              Result: %i Bushels left. [Y/N]\n", foodReplant, tempFood - foodReplant);
						scanf("%s", answer);
						if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0)
						{
							ErrChk = 0;
						}
					}
					else
					{
						printf("Can not Replant  %i bushels of food!              Result: %i Bushels left. Try Again.\n", foodReplant, tempFood - foodReplant);
						scanf("%s", answer);
					}
				}
			}
			else
			{
				printf("Can not feed population %i bushels of food!              Result: %i Bushels left. Try Again.", popFoodInput, food - popFoodInput);
				scanf("%s", answer);
			}
			  
		}
		
	}
	else if (section == 2)
	{
		ErrChk = 1;
		while(ErrChk == 1)
		{
			printf("%s", "Please enter your name:");
			scanf("%s", playerName);
			
			printf("%s", "What is the name of this new colony?:");
			scanf("%s", colonyName);
			system("clear");
			
			/* Error check for name and town name preformed by user */
			printf("Welcome mayor %s! You will be the mayor of %s, a budding colony with many challenges to face.\nAre you happy with your choices so far? [Y/N]:", playerName, colonyName);
			scanf("%s", answer);
			if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0)
			{	
				ErrChk = 0;
			}
			else
			{
			system("clear");
			}
		}
	}
}

int main(void)
{
    /* Starting Varbs  */
    food = 500;
    population = 150;
    happyness = 50;
    year = 2240;    
    endCondition = 0;

    /* Clear the screen for the game */
    system("clear");

	/* CheckAnswer:section 2. For asking user for initial settings */
	checkAnswer(2);
	
	/* Main Game Loop  */
    while (endCondition == 0) 
    {
		printf("\nCURRENT STATS\n");
		printf("-------------------------\n");
		printf("Year: %d\nMayor: %s\nColony: %s\n", year, playerName, colonyName);
		printf("Food: %d\nPopulation: %d\nHappyness: %d\n\n", food, population, happyness);
		
		checkAnswer(1);
		system("clear");
		popFoodRatio = popFoodInput / population;

        if (popFoodRatio >= 3)
        {
            population = population + (population * .1);
        }
        else if (popFoodRatio == 2)
        {
            population = population + (population * .03);
        }
        else if (popFoodRatio == 1)
        {
            population = population - (population * .03);
            happyness = happyness - 5;
        }
        else
        {
            population = population - (population * .1);
            happyness = happyness - 10;
        }
    
        /* endCondition meanings | 1 = victory | 2 = failure | 0 = win  */
        /* Evaluate victory conditions  */
        if (happyness < 0)
        {
            endCondition = 2;
        }
        if (population < 1)
        {
            endCondition = 2;
        }
        if (year == 2250)
        {
            endCondition = 1;
        }
  
        if (endCondition == 2)
        {
            system("clear");
            printf("Years of starvation and mismagement have finally\n");
            printf("worn down the resolve of the colonists. As resentment\n");
            printf("for %s grew more and more people called for a\n", playerName);
            printf("new mayor of %s\n", colonyName);
            printf("\n");
            printf("Mayor %s was thrown in jail for incompetance\n", playerName);
            printf("and a new chapter of %s has begun.\n", colonyName);
            printf("\nYou failed, feel free to try again\n");
            exit(0);
        }
        else if (endCondition == 1)
        {
            system("clear");
            printf("It's been 10 years since the %s colony\n", colonyName);
            printf("was founded. Despite the many challenges %s\n", playerName);
            printf("led the colony to success as its first mayor\n");
            printf("\n");
            printf("%s. Beloved by all a statue was erected to\n", playerName);
            printf("celebrate their part in the colonys founding\n");
            printf("\nCongradulations you won, play again sometime\n");
            exit(0);
        }

        /* End turn calculations */
        food = foodReplant * rando(1, 5);
        year++;
    }


    return 0;

}
