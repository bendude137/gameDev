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
int food, tempFood, UsedFood, foodReplant, population, happyness, popFoodInput, popFoodRatio; 
int year, endCondition;
int confirmYear;
char answer[1024], badInput[1];
char playerName[1024];
char colonyName[1024];

/* Create a pseudo random number  */
int rando(int MIN, int MAX)
{
    srand(time(0));
    return MIN + rand() % (MAX + 1 - MIN);
}

int checkAnswer(int section, int subSection)
{
	if (section == 1)
	{
		if (subSection == 1)
		{
			printf("How much food do you want to feed your population?: ");
			if (scanf("%d", &popFoodInput) != 1)
			{
				scanf("%s", badInput);
				return 0;
			}
			if (food - popFoodInput >= 0) 
			{
				printf("Feed population %i bushels of food? Result: %i Bushels left. [Y/N(Any Key)]\n", popFoodInput, food - popFoodInput);
				scanf("%s", answer);
				if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0)
				{
					tempFood = food - popFoodInput;
					return 1;
				}
			}
			else
			{
				printf("Can not feed population %i bushels of food! Result: %i Bushels left. Try Again.", popFoodInput, food - popFoodInput);
				scanf("%s", answer);
			}
		}
		else if (subSection == 2)
		{
			printf("How much food will you plant?: ");
			if (scanf("%d", &foodReplant) != 1)
			{
				scanf("%s", badInput);
				return 0;
			}
			if (tempFood - foodReplant >=0)
			{
				printf("Replant %i bushels of food? Result: %i Bushels left. [Y/N(Any Key)]\n", foodReplant, tempFood - foodReplant);
				scanf("%s", answer);
				if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0)
				{
					return 1;
				}
			}
			else
			{
				printf("Can not Replant  %i bushels of food! Result: %i Bushels left. Try Again.\n", foodReplant, tempFood - foodReplant);
				scanf("%s", answer);
			}
		}
	}
	else if (section == 2)
	{

		printf("%s", "Please enter your name:");
		scanf("%s", playerName);
			
		printf("%s", "What would you like to name your new colony?:");
		scanf("%s", colonyName);
		system("clear");
			
		/* Error check for name and town name preformed by user */
		printf("Welcome mayor %s! You will be the mayor of %s, a budding colony with many challenges to face.\nAre you happy with your choices so far? [Y/N(Any Key)]:", playerName, colonyName);
		scanf("%s", answer);
		if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0)
		{	
			return 1;
		}
		else
		{
		system("clear");
		}
	}
	return 0;
}

void dispTownInfo()
{
	printf("\nCURRENT STATS\n");
	printf("-------------------------\n");
	printf("Year: %d\nMayor: %s\nColony: %s\n", year, playerName, colonyName);
	printf("Food: %d", food);
	if (popFoodInput != 0)
	{
		printf("-%d :%d(Unused)", UsedFood, food-(UsedFood));

	}
	printf("\nPopulation: %d\nHappyness: %d\n\n", population, happyness);
}

void doMath()
{
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
	while (checkAnswer(2,1) != 1)
	{
		system("clear");
	}
	
	/* Main Game Loop  */
    while (endCondition == 0) 
    {
		confirmYear = 0;
		while (confirmYear == 0)
		{
			system("clear");
			dispTownInfo();
			while (checkAnswer(1,1) != 1)   /*get popFoodInput*/ 
			{
				system("clear");
				dispTownInfo();
			}
			UsedFood = popFoodInput;
			
			system("clear");
			dispTownInfo();
			while (checkAnswer(1,2) != 1)  /*get foodReplant*/
			{
				system("clear");
				dispTownInfo();
			}
			UsedFood += foodReplant;
			                              /*After all user input is gathered, confirm total rescource usage for year*/
			system("clear");
			dispTownInfo();
			printf("Are you ready to see how your choises effect %s for the coming year? [Y/N(Any Key)]:", colonyName);
			scanf("%s", answer);
			if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0)
			{	
				confirmYear = 1;
			}
			else 
			{
				popFoodInput = 0;
				foodReplant = 0;
			}
		}
			
		
		/* end of round math */
		doMath();

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

        /* Set up next year */
        food = foodReplant * rando(1, 5);
        year++;
        popFoodInput = 0;
        foodReplant = 0;
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
        }

    return 0;

}
