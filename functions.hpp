#ifndef SIR_FUNCTIONS_HPP
#define SIR_FUNCTIONS_HPP

#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "structures.hpp"
#include "initializations.hpp"
//#include "functions.cpp"

////////////////////////////////////////////////////////////////////////////////////////////////
//Data collecting functions
////////////////////////////////////////////////////////////////////////////////////////////////

void dataPrint(Population &pop);

void dataCollecting(Population &pop, std::vector<dailyReport> &finalReport);

void printDataToFile(std::vector<dailyReport> &finalReport);

////////////////////////////////////////////////////////////////////////////////////////////////
//Printing on terminal function
////////////////////////////////////////////////////////////////////////////////////////////////

void gridPrint(Population &pop);

////////////////////////////////////////////////////////////////////////////////////////////////
//Adjacent infects
////////////////////////////////////////////////////////////////////////////////////////////////

inline int adjacentInfects(Population &pop, int row, int column);

////////////////////////////////////////////////////////////////////////////////////////////////
//Spreading functions
////////////////////////////////////////////////////////////////////////////////////////////////

Population linearSpread(Population &previous);

Population nonLinearSpread(Population &previous, int daysPassed);

inline void cellMover(Population &pop);

inline int booleanMarker(int x);

////////////////////////////////////////////////////////////////////////////////////////////////
//Check function
////////////////////////////////////////////////////////////////////////////////////////////////

inline void checkParameters(ParametersCheck const &check);

////////////////////////////////////////////////////////////////////////////////////////////////
//execution functions
////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<dailyReport> execute(ParametersCheck const &check, int const size);

std::vector<dailyReport> noGraphicsExecute(ParametersCheck const &check, int const size);

std::vector<dailyReport> bigSimulationExecute(ParametersCheck const &check, int const size);

std::vector<dailyReport> bigSimulationExecuteNL(ParametersCheck const &check, int const size);


#endif
