#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cassert>
#include <iomanip>
#include <thread>
#include <ostream>
#include <fstream>
#include <cmath>
#include <algorithm>
//#include <functional>

//global variables
double beta = 0;
double gamma_ = 0; //gamma_ scelto perchè c'era conflittualità in compilazione da linea di comando


//strutture
enum class Condition : char { //possible states
    S, I, R, D
};

struct dailyReport {

    int daily_S_;
    int daily_I_;
    int daily_R_;
    int daily_D_;

    dailyReport(int iS, int iI, int iR, int iD) : daily_S_(iS), daily_I_(iI), daily_R_(iR), daily_D_(iD) {}
};

class Population { //create the board of states
private:
    int n_;
    std::vector<Condition> board_;

public:
    Population(int n) : n_(n), board_(n* n) {    } //

    Condition& operator() (int row, int column) {
        assert(column >= 0 && column < n_&& row >= 0 && row < n_);
        return board_[row * n_ + column];
    }

    //member functions to access data in private

    int getSize() const { return n_; }

    auto getBoard() const { return board_; }

    int infectsCounter() const {
        int inf = 0;
        for (int i = 0; i < n_ * n_; i++) {
            if (board_[i] == Condition::I) {
                inf++;
            }
            else {}
        }
        return inf;
    }

    int susceptiblesCounter() const {
        int sus = 0;
        for (int i = 0; i < n_ * n_; i++) {
            if (board_[i] == Condition::S) {
                sus++;
            }
            else {}
        }
        return (sus - (4 * n_ - 4)); //ignora i suscettibili sul bordo
    }

    int recoveredCounter() const {
        int rec = 0;
        for (int i = 0; i < n_ * n_; i++) {
            if (board_[i] == Condition::R) {
                rec++;
            }
            else {}
        }
        return rec;
    }

    int deadCounter() {
        int dead = 0;
        for (int i = 0; i < n_ * n_; i++) {
            if (board_[i] == Condition::D) {
                dead++;
            }
            else {}
        }
        return dead;
    }

    void swapTwoCells(int iX, int jX, int iY, int jY) {
        Condition temp;
        temp = board_[iX * n_ + jX];
        board_[iX * n_ + jX] = board_[iY * n_ + jY];
        board_[iY * n_ + jY] = temp;
    }
};

struct ParametersCheck {

    double betaCheck_;
    double gammaCheck_;



    ParametersCheck(double betaCheck, double gammaCheck) : betaCheck_(betaCheck), gammaCheck_(gammaCheck) {}

};

//Definition of the free functions

//get the number of infects nearby
int adjacentInfects(Population& pop, int row, int column) {
    auto cell = pop(row, column);
    int infect = static_cast<int>(Condition::I);
    int result = static_cast<int>(pop(row, column));
    if (result == 1) {
        result--;
    }
    // taking the neighbourhood-central cell back to zero (not a neighbour!)
    for (int i = row - 1; i != row + 2; ++i) {
        for (int j = column - 1; j != column + 2; ++j) {
            int adjacent = static_cast<int>(pop(i, j));
            if (adjacent == infect) {
                // only neighbours (not central cell) make the count increase
                result++;

            }
            else {
            }
        }
    }
    switch (cell) {
    case Condition::I:
        return (result - 1);
        break;
    default:
        return result;
        break;
    }
}

int booleanMarker(int x) {
    if (x == 0) { return 0; }
    else { return 1; }
}

//print the grid
void gridPrint(Population& pop) { //sistemare gli output
    std::cout << "   ";
    for (int edge = 0; edge < pop.getSize(); ++edge) {
        // labels on vertical edge
        std::cout << std::right << std::setw(2) << edge << " ";
    }
    std::cout << '\n';

    for (int row = 0; row < pop.getSize(); ++row) {
        // labels on horizontal edge
        std::cout << std::right << std::setw(2) << row << "  ";

        for (int column = 0; column < pop.getSize(); ++column) {
            auto cell = pop.getBoard()[row * pop.getSize() + column];

            // cells on the edge o the board are counted as "susceptible".
            switch (cell) {
            case (Condition::S):
                std::cout << std::setw(1) << "O"
                    << "  ";
                break;

            case (Condition::I):
                std::cout << std::setw(1) << "\033[31mI\033[0m"
                    << "  ";
                break;

            case (Condition::R):
                std::cout << std::setw(1) << "\033[36mX\033[0m"
                    << "  ";
                break;
            case (Condition::D):
                std::cout << std::setw(1) << "\033[34mD\033[0m"
                    << "  ";
                break;

            default:
                std::cout << "no cell selected" << '\n';
            }
        }

        std::cout << '\n';
    }
    std::cout << '\n';
}

void dataPrint(Population& pop) {
    std::cout << "S = " << pop.susceptiblesCounter() << ", I = " << pop.infectsCounter() << ", R = " << pop.recoveredCounter() << ", D = " << pop.deadCounter() << "\n";
}

auto dataCollecting(Population& pop, std::vector<dailyReport>& finalReport) {
    dailyReport day = dailyReport(pop.susceptiblesCounter(), pop.infectsCounter(), pop.recoveredCounter(), pop.deadCounter());
    finalReport.push_back(day);

}

//Type of spreadings

auto linearSpread(Population& previous) { //includere uno spread in cui i valori di gamma_ e beta variano a seconda del numero di malati?
    int size = previous.getSize();
    Population evolved(size);
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_real_distribution<> dis(0, 1);

    for (int row_loop = 1; row_loop < size - 1; ++row_loop) {
        for (int column_loop = 1; column_loop < size - 1; ++column_loop) {

            assert(row_loop != 0 && row_loop != size && column_loop != 0 && column_loop != size);

            auto cell = previous(row_loop, column_loop);
            switch (cell) {
            case Condition::S: {
                int i = 0;

                while (i != adjacentInfects(previous, row_loop, column_loop)) {
                    ++i;

                }
                if (i == adjacentInfects(previous, row_loop, column_loop) &&
                    dis(gen) <= i * beta) { //modello di spread lineare fra (0,0) e (1,beta) 

                   // dis(gen) <= booleanMarker(i) * ( (i-1)*(1-beta)/7 + beta) ) { //linear spread fra (1,beta) e (8,1) con annullamento sullo zero

                    evolved(row_loop, column_loop) = (Condition::I);
                }
                else {
                }
                break;
            }
            case Condition::I: {
                if (dis(gen) <= gamma_) {
                    if (dis(gen) <= std::pow(gamma_, 2)) {
                        evolved(row_loop, column_loop) = (Condition::D);
                    }
                    else {
                        evolved(row_loop, column_loop) = (Condition::R);
                    }
                }
                else {
                    evolved(row_loop, column_loop) = previous(row_loop, column_loop);
                }
                break;
            }
            case Condition::R: {
                evolved(row_loop, column_loop) = previous(row_loop, column_loop);
                break;
            }
            case Condition::D: {
                evolved(row_loop, column_loop) = previous(row_loop, column_loop);
                break;
            }

            default:
                break;
            }
        }
    }
    return evolved;
}

//spread non lineare, maggiore il numero di malati più lenta la guarigione e più lento il contagio
//i suscettibili si ammalano più lentamente, i malati guariscono più lentamente
auto nonLinearSpread(Population& previous, int daysPassed) {
    int size = previous.getSize();
    Population evolved(size);
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_real_distribution<> dis(0, 1);
    int previousDayInfects = previous.infectsCounter();

    if (daysPassed % 7 == 0) { beta = beta * 1.5; } //questa riga simula la movida del sabato
    if (daysPassed > 60 && daysPassed <= 100) { gamma_ = gamma_ * 1.5; } //dopo 60 giorni dallo scoppio dell'epidemia le tecniche di cura diventano più efficaci
    if (daysPassed > 101) { gamma_ = gamma_ * 2; } //dopo 100 giorni dallo scoppio dell'epidemia le tecniche di cura diventano ancora più efficaci

    for (int row_loop = 1; row_loop < size - 1; ++row_loop) {
        for (int column_loop = 1; column_loop < size - 1; ++column_loop) {

            assert(row_loop != 0 && row_loop != size && column_loop != 0 && column_loop != size);

            auto cell = previous(row_loop, column_loop);
            switch (cell) {
            case Condition::S: {
                int i = 0;
                while (i != adjacentInfects(previous, row_loop, column_loop)) {
                    ++i;
                }
                if (i == adjacentInfects(previous, row_loop, column_loop) &&
                    dis(gen) <= ((beta * i) / (((size * size + previousDayInfects) / (size * size))))) { //riduce infettività all'aumentare degli infetti
                    evolved(row_loop, column_loop) = (Condition::I);
                }
                else {
                }
                break;
            }
            case Condition::I: {
                if (dis(gen) <= gamma_) {
                    if (dis(gen) <= std::pow(gamma_, 2)) {
                        evolved(row_loop, column_loop) = (Condition::D);
                    }
                    else {
                        evolved(row_loop, column_loop) = (Condition::R);
                    }
                }
                else {
                    evolved(row_loop, column_loop) = previous(row_loop, column_loop);
                }
                break;
            }
            case Condition::R: {
                evolved(row_loop, column_loop) = previous(row_loop, column_loop);
                break;
            }
            case Condition::D: {
                evolved(row_loop, column_loop) = previous(row_loop, column_loop);
                break;
            }

            default:
                break;
            }
        }
    }
    return evolved;
}

auto cellMover(Population& pop) {

    int iX, jX, iY, jY;
    int redSize = static_cast<int> (pop.getSize()) - 2;
    int numOfSwaps = pop.getSize(); 
    for (int i = 0; i < numOfSwaps; i++) {

        iX = (rand() + time(nullptr)) % (redSize) + 1;
        jX = (rand() + time(nullptr)) % (redSize) + 1;
        iY = (rand() + time(nullptr)) % (redSize) + 1;
        jY = (rand() + time(nullptr)) % (redSize) + 1;

        if (pop(iX, jX) != Condition::D && pop(iY, jY) != Condition::D) {
            pop.swapTwoCells(iX, jX, iY, jY);
        }
    }
    return pop;
}

//initializations
auto emptyBoard(Population& pop) {
    for (int i = 0; i < pop.getSize(); i++) {
        for (int j = 0; j < pop.getSize(); j++) {
            pop(i, j) = (Condition::S);
        }
    }

}

//types of epidemics
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

        pop(i = (rand() + time(nullptr)) % (pop.getSize()),
            j = (rand() + time(nullptr)) % (pop.getSize())) = (Condition::I);
        break;
    case '2':

        for (int x = 0; x < 10; x++) {

            int oddSize;
            if (pop.getSize() % 2 == 0) { oddSize = pop.getSize(); }
            else { oddSize = pop.getSize() - 1; }
            int i = (rand() + time(nullptr)) % (oddSize / 2);
            int j = (rand() + time(nullptr)) % (oddSize / 2);
            pop(i, j) = (Condition::I);
            // print in a smaller grid 10 infects
        }
        break;
    case '3':
        int numOfInfects;
        std::cout << "Instert number of infects\n";
        std::cin >> numOfInfects;
        for (int x = 0; x <= numOfInfects; x++) {
            int i = (rand() + time(nullptr)) % (pop.getSize());
            int j = (rand() + time(nullptr)) % (pop.getSize());
            pop(i, j) = (Condition::I);
        }
        break;
    default:
        pop(1, 1) = (Condition::I);
        break;
    }
}

//initialize data

int initSize() {
    int sizeval;
    std::cout << "\nPlease enter a valid number as \033[31mboard size\033[0m. (3<x<40), otherwise it will be set as default\n";
    std::cin >> sizeval;
    if (sizeval > 3 && sizeval < 40) {
        return sizeval;
    }
    else {
        return 15;
    }

}

int initSizeNoGraph() {
    int sizeval;
    std::cout << "\nPlease enter a valid number as \033[31mboard size\033[0m (x>3, 100 is the suggested size, an higher value will result in a longer epidemics)\n";
    std::cin >> sizeval;
    if (sizeval > 3) {
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
        beta = 0.3;
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

auto initializeparameters() { //in case we add more parameters in the future
    double betaMirror = initBeta();
    double gammaMirror = initgamma_();

    ParametersCheck checker = ParametersCheck(betaMirror, gammaMirror);
    return checker;
}

auto initializeParametersNoGraph() { //in case we add more parameters in the future

    double betaMirror = initBeta();
    double gammaMirror = initgamma_();

    ParametersCheck checker = ParametersCheck(betaMirror, gammaMirror);
    return checker;

}

auto autoinitialize() {

    double autobeta = 0.15;
    double autogamma_ = 0.2;


    beta = autobeta;
    gamma_ = autogamma_;


    ParametersCheck check = ParametersCheck(autobeta, autogamma_);
    return check;
}

auto checkParameters(ParametersCheck check) {
    if (beta != check.betaCheck_) { beta = check.betaCheck_; }
    if (gamma_ != check.gammaCheck_) { gamma_ = check.gammaCheck_; }

}

//executions
auto execute(ParametersCheck check, int size) {
    Population pop(size);
    std::vector<dailyReport> finalReport;
    emptyBoard(pop);
    initializeCornerInfect(pop); //add initialization settings
    int dayspassed = 1;
    //far andare la funzione autonomamente
    while (pop.infectsCounter() != 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
        pop = cellMover(pop);
        pop = linearSpread(pop);
        std::cout << "Day: " << dayspassed << "\n";
        gridPrint(pop);
        dataPrint(pop);
        dataCollecting(pop, finalReport);
        std::cout << "\n";
        dayspassed++;
        checkParameters(check);
        if (pop.infectsCounter() == 0) {
            return finalReport;
            break;
        }
        else {}

    }


}

auto noGraphicsExecute(ParametersCheck check, int size) {
    Population pop(size);
    std::vector<dailyReport> finalReport;
    emptyBoard(pop);
    initializeInfect(pop); //add initialization settings
    int dayspassed = 1;
    //far andare la funzione autonomamente
    while (pop.infectsCounter() != 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        //pop = linearSpread(pop);
        std::cout << "Day: " << dayspassed << "\n";

        dataPrint(pop);
        dataCollecting(pop, finalReport);
        std::cout << "\n";
        dayspassed++;
        checkParameters(check);
        if (pop.infectsCounter() == 0) {
            return finalReport;
            break;
        }
        else {}

    }


}

auto bigSimulationExecute(ParametersCheck check, int size) {
    Population pop(size);
    std::vector<dailyReport> finalReport;
    emptyBoard(pop);
    initializeInfect(pop);
    while (pop.infectsCounter() != 0) {
        pop = cellMover(pop);
        pop = linearSpread(pop);
        std::cout << "\n";
        dataCollecting(pop, finalReport);
        checkParameters(check);
        if (pop.infectsCounter() == 0) {
            return finalReport;
            break;
        }
        else {}

    }

}

auto bigSimulationExecuteNL(ParametersCheck check, int size) {
    Population pop(size);
    std::vector<dailyReport> finalReport;
    emptyBoard(pop);
    initializeInfect(pop);
    int daysPassed = 1;
    while (pop.infectsCounter() != 0) {
        //pop = cellMover(pop);
        pop = nonLinearSpread(pop, daysPassed);
        std::cout << "\n";
        dataCollecting(pop, finalReport);
        daysPassed++;
        checkParameters(check);
        if (pop.infectsCounter() == 0) {
            return finalReport;
            break;
        }
        else {}

    }

}

//
void printDataToFile(std::vector<dailyReport>& finalReport) {
    int const calculated_size = (sqrt(finalReport[0].daily_S_ + finalReport[0].daily_I_ + finalReport[0].daily_R_ + finalReport[0].daily_D_) + 2);
    std::ofstream report;
    report.open("report.txt");
    report <<
        "//Size is " << calculated_size << ", beta is " << beta << ", Gamma is " << gamma_ << "\n";
    for (size_t i = 0; i < finalReport.size(); i++) {
        report << i + 1 << std::setw(10) << finalReport[i].daily_S_ << std::setw(10) << finalReport[i].daily_I_ << std::setw(10) << finalReport[i].daily_R_ << std::setw(10) << finalReport[i].daily_D_ << "\n";
    }
    report.close();
}

//main

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
        ParametersCheck const checkParAuto = autoinitialize();
        finalReport = execute(checkParAuto, boardSize);
    }
    break;
    case 'd':
    {
        int const boardSize = initSizeNoGraph();
        ParametersCheck const checkParNoGraph = initializeParametersNoGraph();
        finalReport = noGraphicsExecute(checkParNoGraph, boardSize);
    }
    break;
    case 'b':
    {
        int const boardSize = initSizeNoGraph();
        ParametersCheck const checkParNoOutput = initializeParametersNoGraph();
        finalReport = bigSimulationExecute(checkParNoOutput, boardSize);
    }
    break;
    case 'n':
    {
        int const boardSize = initSizeNoGraph();
        ParametersCheck const checkParNoOutput = initializeParametersNoGraph();
        finalReport = bigSimulationExecuteNL(checkParNoOutput, boardSize);
    }
    break;
    case 'm':
    {
        int const boardSize = initSize();
        ParametersCheck const checkDefault = initializeparameters();
        finalReport = execute(checkDefault, boardSize);
    }
    break;
    default:
    {
        int const boardSize = initSize();
        ParametersCheck const checkDefault = initializeparameters();
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
