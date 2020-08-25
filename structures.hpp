#ifndef SIR_STRUCTURES_HPP
#define SIR_STRUCTURES_HPP

#include <cassert>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////
//global variables
///////////////////////////////////////////////////////////////////////////////////////////

double beta = 0;
double gamma_ = 0; //gamma_ scelto perchè c'era conflittualità in compilazione da linea di comando

///////////////////////////////////////////////////////////////////////////////////////////
//structures
///////////////////////////////////////////////////////////////////////////////////////////

enum class Condition : char { //possible states
    S, I, R, D, E
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
        }
        return inf;
    }

    int susceptiblesCounter() const {
        int sus = 0;
        for (int i = 0; i < n_ * n_; i++) {
            if (board_[i] == Condition::S) {
                sus++;
            }
        }
        return (sus - (4 * n_ - 4)); //ignora i suscettibili sul bordo
    }

    int recoveredCounter() const {
        int rec = 0;
        for (int i = 0; i < n_ * n_; i++) {
            if (board_[i] == Condition::R) {
                rec++;
            }
        }
        return rec;
    }

    int deadCounter() {
        int dead = 0;
        for (int i = 0; i < n_ * n_; i++) {
            if (board_[i] == Condition::D) {
                dead++;
            }
        }
        return dead;
    }

    /*int emptyCounter() { //utile? per me si può eliminare
        int empty = 0;
        for (int i = 0; i < n_ * n_; i++) {
            if (board_[i] == Condition::E) {
                empty++;
            }
        }
        return empty;
    }*/

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
    bool cellMove_;
    double emptyCells_;

    ParametersCheck(double betaCheck, double gammaCheck, bool cellMove, double emptyCells) :
     betaCheck_(betaCheck), gammaCheck_(gammaCheck), cellMove_(cellMove), emptyCells_(emptyCells) {}
};

#endif