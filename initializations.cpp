/*This file performs all the initializations for the execution of main.cpp*/

#include "initializations.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

////////////////////////////////////////////////////////////////////////////////////////////////
//Board emptier
////////////////////////////////////////////////////////////////////////////////////////////////

//virtually useless, was helpful during debug and provides an extra layer of safety
void emptyBoard(Population &pop)
{ //
    for (int i = 0; i < pop.getSize(); i++)
    {
        for (int j = 0; j < pop.getSize(); j++)
        {
            pop(i, j) = (Condition::S);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
//infects initializations
////////////////////////////////////////////////////////////////////////////////////////////////

void initializeCornerInfect(Population &pop)
{ //initialize an infect in 1,1 (2,2)
    pop(1, 1) = (Condition::I);
}

//user input infect initializations
void initializeInfect(Population &pop)
{
    char option_;
    std::cout << "\nChoose how many infects you want in the population (type the number of the option): \n1) 1 Random infect on the board\n"
              << "2) 10 random infects in a smaller portion of the grid \n3) manual number of random infects\nAny other key for 1 infect in a corner\n";
    std::cin >> option_;
    int i, j;
    switch (option_)
    {
    case '1':
    {
        pop(i = ((rand() + time(nullptr)) % (pop.getSize() - 2)) + 1,
            j = ((rand() + time(nullptr)) % (pop.getSize() - 2)) + 1) = (Condition::I);
    }
    break;
    case '2':
    {
        for (int x = 0; x < 10; x++)
        {
            int oddSize;
            if (pop.getSize() % 2 == 0)
            {
                oddSize = pop.getSize();
            }
            else
            {
                oddSize = pop.getSize() - 1;
            }
            int i = ((rand() + time(nullptr)) % (oddSize / 2)) + 1;
            int j = ((rand() + time(nullptr)) % (oddSize / 2)) + 1;
            pop(i, j) = (Condition::I);
            // print in a smaller grid 10 infects
        }
    }
    break;
    case '3':
    {
        int numOfInfects;
        std::cout << "Insert number of infects\n";
        std::cin >> numOfInfects;
        for (int x = 0; x <= numOfInfects; x++)
        {
            int i = (rand() + time(nullptr)) % (pop.getSize() - 2) + 1;
            int j = (rand() + time(nullptr)) % (pop.getSize() - 2) + 1;
            pop(i, j) = (Condition::I);
        }
    }
    break;
    default:
    {
        pop(1, 1) = (Condition::I);
    }
    break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Cell emptier
////////////////////////////////////////////////////////////////////////////////////////////////

//this function eliminates cells randomly to allow movement
void cellEmptier(Population &pop, ParametersCheck check, int size)
{
    double cellsToRemove;
    cellsToRemove = (size * size * check.emptyCells_);
    int removedCounter = 0;
    int removeTries = 0;
    while (removedCounter < cellsToRemove)
    {
        int iC = ((rand() + time(nullptr)) % (size - 2)) + 1;
        int jC = ((rand() + time(nullptr)) % (size - 2)) + 1;

        if (pop(iC, jC) == (Condition::S))
        {
            pop(iC, jC) = (Condition::E);
            removedCounter++;
        }
        else
        {
            removeTries++;
        }

        if (removeTries > 100 * cellsToRemove)
        {
            removedCounter = size * size;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
//initialization of user data
////////////////////////////////////////////////////////////////////////////////////////////////

//size
int initSize(char graphOrNot) //gRAPH vs nOGRAPH
{
    int sizeval;
    switch (graphOrNot)
    {
    case 'g':
    {
        std::cout << "\nPlease enter a valid number as \033[31mboard size\033[0m. (5<x<40), otherwise it will be set as default\n";
        std::cin >> sizeval;
        return (sizeval > 5 && sizeval < 40) ? sizeval + 2 : 20;
	}
    case 'n': //noGraphic case
    {
        std::cout << "\nPlease enter a valid number as \033[31mboard size\033[0m (x>5, 100 is the suggested size, an higher value will result in a longer epidemics)\n";
        std::cin >> sizeval;
        return (sizeval > 5) ? sizeval + 2 : 100;
    }
    default:
    {
         std::cout << "\nPlease enter a valid number as \033[31mboard size\033[0m (x>5, 100 is the suggested size, an higher value will result in a longer epidemics)\n";
        std::cin >> sizeval;
        return (sizeval > 5) ? sizeval + 2 : 100;
    }
  }
}

//beta
double initBeta()
{
    double betaval;
    std::cout << "\nEnter value for \033[31mbeta\033[0m (0 < x < 1), otherwise it will be set as default\n";
    std::cout << "Suggested values are between 0.1 and 0.2, higher values will result in faster spreading\n";
    std::cin >> betaval;
    if (betaval > 0 && betaval < 1)
    {
        beta = betaval;
    }
    else
    {
        beta = 0.2;
        betaval = beta;
    }
    return betaval;
}

//gamma
double initGamma_()
{
    double gamma_val;
    std::cout << "\nEnter value for \033[31mgamma\033[0m (0 < x < 1), otherwise it will be set as default\n";
    std::cout << "Suggested values are between 0.1 and 0.2, higher values will result in faster recovering\n";
    std::cin >> gamma_val;
    if (gamma_val > 0 && gamma_val < 1)
    {
        gamma_ = gamma_val;
    }
    else
    {
        gamma_ = 0.1;
        gamma_val = gamma_;
    }
    return gamma_val;
}

//if cells are allowed to move
bool cellMove()
{
    char cellMove_;
    std::cout << "\nDo you want to enable the \033[31mmovement\033[0m of cells? (y/n)\n";
    std::cin >> cellMove_;
    return (cellMove_ == 'n') ? 0 : 1;
}

//what percentage of cells should be emptied
double emptyCell_()
{
    double emptyCellVal;
    std::cout << "\nWhat percentage of the population do you want to \033[31mremove\033[0m? (0 < x < 0.8)\n";
    std::cout << "Don't remove more than 80% of the population\n";
    std::cin >> emptyCellVal;
    if (emptyCellVal >= 0 && emptyCellVal < 0.8)
    {
        return emptyCellVal;
    }
    else
    {
        emptyCellVal = 0.3;
        return emptyCellVal;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
//types of initialization
////////////////////////////////////////////////////////////////////////////////////////////////

ParametersCheck initializeParameters(char optionPar)
{

    switch (optionPar)
    {
    case 'a': //automatic initialization, user only has to decide the size of the board
    {
        double autobeta = 0.15;
        double autogamma_ = 0.2;

        beta = autobeta;
        gamma_ = autogamma_;
        bool cellMove_ = 1;
        double emptyCell = 0;

        ParametersCheck checker = ParametersCheck(autobeta, autogamma_, cellMove_, emptyCell);
        return checker;
    }
    break;
    case 'b': //manual input of parameters
    {
        double betaMirror = initBeta();
        double gammaMirror = initGamma_();
        bool cellMove_ = cellMove();
        double emptyCell = emptyCell_();

        ParametersCheck checker = ParametersCheck(betaMirror, gammaMirror, cellMove_, emptyCell);
        return checker;
    }
    break;
    default:
    {
        {
        double betaMirror = initBeta();
        double gammaMirror = initGamma_();
        bool cellMove_ = cellMove();
        double emptyCell = emptyCell_();

        ParametersCheck checker = ParametersCheck(betaMirror, gammaMirror, cellMove_, emptyCell);
        return checker;
    }
    break;
    }
    break;
    }
}
