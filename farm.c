#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*****************************************************************
#      Program Name : Luyten Lingering (working title)           # 
#            Author : Brandon M. {BMo}                           #
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
char answer[1024];
char playerName[1024];
char colonyName[1024];

/* Create a pseudo random number  */
int rando(int MIN, int MAX)
{
    srand(time(0));
    return MIN + rand() % (MAX + 1 - MIN);
}

/* This is to take the common prompts for user input and make them re-useable
   meant to be used in conjunction with a loop */
void checkAnswer(int section, int subSection)
{
    /* Section 1 is for distributing the food resource */
    if (section == 1)
    {
        if (subSection == 1)
        {
            printf("How much food do you want to feed your population?: ");
            scanf("%d", &popFoodInput);  
        }
        else if (subSection == 2)
        {
            printf("How much food will you plant?: ");
            scanf("%d", &foodReplant);
        }
        else if (subSection == 3)
        {
            food = food - popFoodInput;
            printf("You now have %d food left\n", food); 
        }
        else if (subSection == 4)
        {
            food = food - foodReplant;
            if (food > 0)
            {
                printf("You still have %d food left, are you sure[y/n]? ", food);
                scanf("%s", answer);
                while (strcmp(answer, "y") != 0)
                {
                    if (strcmp(answer, "y") == 0)
                    {
                        food = food - popFoodInput;
                        printf("You now have %d food left\n", food); 
                    }
                    else if (strcmp(answer, "Y") == 0)
                    {
                        food = food - popFoodInput;
                        printf ("You now have %d food left\n", food); 
                    }
                    else if (strcmp(answer, "n") == 0)
                    {
                        printf("How much food will you plant?: ");
                        scanf("%d", &foodReplant);
                        printf("You said %d food to replant, is that correct[y/n]? ", foodReplant);
                        scanf("%s", answer);
                    }
                    else if (strcmp(answer, "N") == 0)
                    {
                        printf("How much food will you plant?: ");
                        scanf("%d", &foodReplant);
                        printf("You said %d food to replant, is that correct[y/n]? ", foodReplant);
                        scanf("%s", answer);
                    }
                    else
                    {
                        printf("Answer not recognized, please choose 'y' or 'n': ");
                        scanf("%s", answer);
                    }
                }  
            }
        }
        else
        {
            printf("INCORRECT SUBSECTION SELECTION\n");
            exit(1);
        }
    }

    /* Section 2 is for the naming of the player and city  */
    else if (section == 2)
    {
        if (subSection == 1)
        {
            printf("Please enter your name: ");
            scanf("%s", playerName);
        }
        else if (subSection == 2)
        {
            printf("What is the name of this new colony?: ");
            scanf("%s", colonyName);
        }
        else
        {
            printf("INCORRECT SUBSECTION SELECTION\n");
            exit(1);
        }
    }
    else
    {
        printf("INCORRECT SECTION SELECTION\n");
        exit(1);
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

    /* allow the player to enter their name  */
    checkAnswer(2, 1);
    printf("Your name is %s correct[y/n]? ", playerName);
    scanf("%s", answer);
    while (strcmp(answer, "y") != 0)
    {   
        if (strcmp(answer, "y") == 0)
        {
            printf("Welcome mayor %s!\n", playerName);
        }
        else if (strcmp(answer, "Y") == 0)
        {
            printf("Welcome mayor %s!\n", playerName);
        }
        else if (strcmp(answer, "n") == 0)
        {
            checkAnswer(2, 1);
            printf("Your name is %s correct[y/n]? ", playerName);
            scanf("%s", answer);
        }
        else if (strcmp(answer, "N") == 0)
        {
            checkAnswer(2, 1);
            printf("Your name is %s correct[y/n]? ", playerName);
            scanf("%s", answer);
        }
        else
        {
            printf("Incorrect selection, please choose 'y' or 'n': ");
            scanf("%s", answer);
        }
    }   

    /* Get the name of the colony  */
    checkAnswer(2, 2);
    printf("The colony will be named %s correct[y/n]? ", colonyName);
    scanf("%s", answer);
    while (strcmp(answer, "y") != 0)
    {   
        if (strcmp(answer, "y") == 0)
        {
            printf("Welcome to %s colony!\n", colonyName);
        }
        else if (strcmp(answer, "Y") == 0)
        {
            printf("Welcome to %s colony!\n", colonyName);
        }
        else if (strcmp(answer, "n") == 0)
        {
            checkAnswer(2, 2);
            printf("The colony will be named %s correct[y/n]? ", colonyName);
            scanf("%s", answer);
        }
        else if (strcmp(answer, "N") == 0)
        {
            checkAnswer(2, 2);
            printf("The colony will be named %s correct[y/n]? ", colonyName);
            scanf("%s", answer);
        }
        else
        {
            printf("Incorrect selection, please choose 'y' or 'n': ");
            scanf("%s", answer);
        }
    }

    /* Main Game Loop  */
    while (endCondition == 0) 
    {

    /* Clear the Screen for next round  */
    system("clear");
  
    /* Print the status {potentially migrate this to function}  */
    printf("\n");
    printf("CURRENT STATS\n");
    printf("-------------------------\n");
    printf("Year: %d\nMayor: %s\nColony: %s\n", year, playerName, colonyName);
    printf("Food: %d\nPopulation: %d\nHappyness: %d\n", food, population, happyness);
    printf("\n");

        checkAnswer(1, 1);
        while (popFoodInput > food )
        {
            printf("ERROR, you cant use more food than you have\n");
            checkAnswer(1, 1);
        }
        printf("You said %d to feed the population is that correct[y/n]? ", popFoodInput);
        scanf("%s", answer);
        while (strcmp(answer, "y") != 0)
        {   
            if (strcmp(answer, "y") == 0)
            {
                checkAnswer(1, 3);
            }
            else if (strcmp(answer, "Y") == 0)
            {
                checkAnswer(1, 3);
            }
            else if (strcmp(answer, "n") == 0)
            {
                checkAnswer(1, 1);
                printf("You said %d to feed the population is that correct[y/n]? ", popFoodInput);
                scanf("%s", answer);
            }
            else if (strcmp(answer, "N") == 0)
            {
                checkAnswer(1, 1);
            }
            else
            {
                printf("Incorrect selection, please choose 'y' or 'n': ");
                scanf("%s", answer);
            }
        }   

        checkAnswer(1, 2);
        while (foodReplant > food)
        {
            printf("ERROR, you cant plant more food than you have\n");
            printf("Your currently have %d food\n", food);
            checkAnswer(1, 2);
        }
        printf("You said %d food to replant, is that correct[y/n]? ", foodReplant);
        scanf("%s", answer);
        while (strcmp(answer, "y") != 0)
        {
            if (strcmp(answer, "y") == 0)
            {
                checkAnswer(1, 4);
            }
            else if (strcmp(answer, "Y") == 0)
            {
                checkAnswer(1, 4);
            }
            else if (strcmp(answer, "n") == 0)
            {
                checkAnswer(1, 2);
                printf("You said %d food to replant, is that correct[y/n]? ", foodReplant);
                scanf("%s", answer);
            }
            else if (strcmp(answer, "N") == 0)
            {
                checkAnswer(1, 2);
            }
            else
            {
                printf("Incorrect selection, please choose 'y' or 'n': ");
                scanf("%s", answer);
            }
        }

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
