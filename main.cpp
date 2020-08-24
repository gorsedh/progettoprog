#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

//#include <algorithm>
//#include <ostream>

#include "structures.cpp"
#include "inizializations.cpp"
#include "functions.cpp"

int main()
{
    std::cout << "Which optionwould you like to use?\n(\033[31ma\033[0m for auto settings, \033[31md\033[0m for disabled graphics, \033[31mb\033[0m for disabled graphics and output,\n\033[31mn\033[0m for a non linear spread and no graphic output, \033[31mm\033[0m for manual settings)\n";
    std::cout << "a and manual are suggested for small populations to get a graphical output of the epidemic (size<30)\n";
    std::cout << "d is suggested for big populations (size>30)\n";
    std::cout << "b is suggested for very big populations just to have the report to analyze (size>100)\n";
    std::cout << "n is suggested for a non linear spread of a disease over a big population, just for the report to analyze (size>100)\n";

   char askparameters;
    std::vector<dailyReport> finalReport;
    std::cin >> askparameters;
    switch (askparameters) {
    case 'a':
    {
        int const boardSize = initSize();
        ParametersCheck const checkParAuto = initializeParameters('a');
        finalReport = execute(checkParAuto, boardSize);
    }
    break;
    case 'd':
    {
        int const boardSize = initSizeNoGraph();
		ParametersCheck const checkParNoGraph = initializeParameters('b');
        finalReport = noGraphicsExecute(checkParNoGraph, boardSize);
    }
    break;
    case 'b':
    {
        int const boardSize = initSizeNoGraph();
		ParametersCheck const checkParNoOutput = initializeParameters('b');
        finalReport = bigSimulationExecute(checkParNoOutput, boardSize);
    }
    break;
    case 'n':
    {
        int const boardSize = initSizeNoGraph();
		ParametersCheck const checkParNoOutput = initializeParameters('b');
        finalReport = bigSimulationExecuteNL(checkParNoOutput, boardSize);
    }
    break;
    case 'm':
    {
        int const boardSize = initSize();
		ParametersCheck const checkDefault = initializeParameters('b');
        finalReport = execute(checkDefault, boardSize);
    }
    break;
    default:
    {
        int const boardSize = initSize();
		ParametersCheck const checkDefault = initializeParameters('b');
        finalReport = execute(checkDefault, boardSize);
    }
    }
    std::cout << "Would you like to get the report for the epidemic?(y/n),\nNon valid input will be considered as an affirmative answer\n";
    char printReport;
    std::cin >> printReport;
    if (printReport == 'n') {
        std::cout << "See you in the next simulation!\n\n";
    }
    else {
        printDataToFile(finalReport);
        std::cout << "You will find the report in the directory of this file, remember to cancel it before running the program again!\n";
    }

}