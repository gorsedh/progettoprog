#ifndef SIR_INITIALIZATIONS_HPP
#define SIR_INITIALIZATIONS_HPP

#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

#include "structures.hpp"
//#include "initializations.cpp"

////////////////////////////////////////////////////////////////////////////////////////////////
//Board emptier
////////////////////////////////////////////////////////////////////////////////////////////////

void emptyBoard(Population &pop);

////////////////////////////////////////////////////////////////////////////////////////////////
//infects initializations
////////////////////////////////////////////////////////////////////////////////////////////////

void initializeCornerInfect(Population &pop);

void initializeInfect(Population &pop);

////////////////////////////////////////////////////////////////////////////////////////////////
// Cell emptier
////////////////////////////////////////////////////////////////////////////////////////////////

void cellEmptier(Population &pop, ParametersCheck check, int size);

////////////////////////////////////////////////////////////////////////////////////////////////
//initialization of user data
////////////////////////////////////////////////////////////////////////////////////////////////

int initSize(char graphOrNot);

double initBeta();

double initGamma_();

bool cellMove();

double emptyCell_();

////////////////////////////////////////////////////////////////////////////////////////////////
//types of initialization
////////////////////////////////////////////////////////////////////////////////////////////////

ParametersCheck initializeParameters(char optionPar);

#endif