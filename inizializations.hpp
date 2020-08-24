#ifndef SIR_INIZIALIZATIONS_HPP
#define SIR_INIZIALIZATIONS_HPP

#include <iomanip>
#include <iostream>
#include <random>

#include "structures.cpp"


////////////////////////////////////////////////////////////////////////////////////////////////
//Board emptier 
////////////////////////////////////////////////////////////////////////////////////////////////

auto emptyBoard(Population& pop) { //
    for (int i = 0; i < pop.getSize(); i++) {
        for (int j = 0; j < pop.getSize(); j++) {
            pop(i, j) = (Condition::S);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
//infects initializations
////////////////////////////////////////////////////////////////////////////////////////////////

auto initializeCornerInfect(Population& pop) { //inizializzo un malato in 1,1 (2,2)
    pop(1, 1) = (Condition::I);
}

auto initializeInfect(Population& pop) {
    char option_;
    std::cout << "\nChoose how many infects you want in the population (type the number of the option): \n1) 1 Random infect on the board\n" <<
        "2) 10 random infects in a smaller portion of the grid \n3) manual number of random infects\nAny other key for 1 infect in a corner\n";
    std::cin >> option_;
    int i, j;
    switch (option_) {
    case '1':
        {
        pop(i = (rand() + time(nullptr)) % (pop.getSize()),
            j = (rand() + time(nullptr)) % (pop.getSize())) = (Condition::I);
        }
        break;
    case '2':
        {
        for (int x = 0; x < 10; x++) {
            int oddSize;
            if (pop.getSize() % 2 == 0) { oddSize = pop.getSize(); }
            else { oddSize = pop.getSize() - 1; }
            int i = (rand() + time(nullptr)) % (oddSize / 2);
            int j = (rand() + time(nullptr)) % (oddSize / 2);
            pop(i, j) = (Condition::I);
            // print in a smaller grid 10 infects
        }
        }
        break;
    case '3':
        {
        int numOfInfects;
        std::cout << "Instert number of infects\n";
        std::cin >> numOfInfects;
        for (int x = 0; x <= numOfInfects; x++) {
            int i = (rand() + time(nullptr)) % (pop.getSize());
            int j = (rand() + time(nullptr)) % (pop.getSize());
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
//initialization of user data
////////////////////////////////////////////////////////////////////////////////////////////////

int initSize() {
    int sizeval;
    std::cout << "\nPlease enter a valid number as \033[31mboard size\033[0m. (5<x<40), otherwise it will be set as default\n";
    std::cin >> sizeval;
    if (sizeval > 5 && sizeval < 40) {
        return sizeval;
    }
    else {
        return 20;
    }
}

int initSizeNoGraph() {
    int sizeval;
    std::cout << "\nPlease enter a valid number as \033[31mboard size\033[0m (x>5, 100 is the suggested size, an higher value will result in a longer epidemics)\n";
    std::cin >> sizeval;
    if (sizeval > 5) {
        return sizeval;
    }
    else {
        return 100;
    }
    return sizeval;
}

double initBeta() {
    double betaval;
    std::cout << "\nEnter value for \033[31mbeta\033[0m (0 < x < 1), otherwise it will be set as default\n";
    std::cout << "Suggested values are between 0.1 and 0.2, higher values will result in faster spreading\n";
    std::cin >> betaval;
    if (betaval > 0 && betaval < 1) {
        beta = betaval;
    }
    else {
        beta = 0.2;
        betaval = beta;
    }
    return betaval;
}

double initgamma_() {
    double gamma_val;
    std::cout << "\nEnter value for \033[31mgamma\033[0m (0 < x < 1), otherwise it will be set as default\n";
    std::cout << "Suggested values are between 0.05 and 0.2, higher values will result in faster recovering\n";
    std::cin >> gamma_val;
    if (gamma_val > 0 && gamma_val < 1) {
        gamma_ = gamma_val;
    }
    else {
        gamma_ = 0.1;
        gamma_val = gamma_;
    }
    return gamma_val;
}

bool cellMove() {
    char cellMove_;
    std::cout << "\nDo you want to enable the \033[31mmovement\033[0m of cells? (y/n)\n";
    std::cin >> cellMove_;
    if (cellMove_ == 'n') { return 0; }
    else { return 1; }
}


/*auto initializeParametersNoGraph() { //in case we add more parameters in the future
    double betaMirror = initBeta();
    double gammaMirror = initgamma_();

    ParametersCheck checker = ParametersCheck(betaMirror, gammaMirror);
    return checker;
}*/

////////////////////////////////////////////////////////////////////////////////////////////////
//types of initialization
////////////////////////////////////////////////////////////////////////////////////////////////

auto initializeParameters(char optionPar) {
	
	switch(optionPar) {
		case 'a': //automatic initialization
		{
    double autobeta = 0.15;
    double autogamma_ = 0.2;

    beta = autobeta;
    gamma_ = autogamma_;
    bool cellMove = 1;

    ParametersCheck check = ParametersCheck(autobeta, autogamma_, cellMove);
    return check;
		}
	break;
		case 'b':
		{
    double betaMirror = initBeta();
    double gammaMirror = initgamma_();
    bool cellMove_ = cellMove();
    ParametersCheck checker = ParametersCheck(betaMirror, gammaMirror, cellMove);
    return checker;
		}
	break;
		default:
		{}
	break;
}
}



#endif
