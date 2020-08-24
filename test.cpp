#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include <iostream>
#include <typeinfo>

////////////////////// FREE FUNCTIONS TEST //////////////////////////
int booleanMarker(int x) {
    if (x == 0) { return 0; }
    else { return 1; }
} 
int initSize() {
    int sizeval;
    if (sizeval > 5 && sizeval < 40) {
        return sizeval;
    }
    else {
        return 20;
    }
}

bool cellMove() {
    char cellMove_;
    if (cellMove_ == 'n') { return 0; }
    else { return 1; }
}


TEST_CASE("functionsTest"){
	
	CHECK(booleanMarker(10) == 1);
	CHECK(typeid(booleanMarker(0.5)) == typeid(int(1))); // check that booleanMarker reads every number as integer
	CHECK(initSize() == 20); // check the default set of initSize
        CHECK(cellMove() == 1); // check that the cells move themselves for the default option
}

/*
////////////////////// GRID TEST //////////////////////////

enum class Condition : char { 
    S, I, R, D
};

class Population { //create the board of states
private:
    int n_;
    std::vector<Condition> board_;

public:
    Population(int n) : n_(n), board_(n* n) {    } 
    Condition& operator() (int row, int column) {
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

TEST_CASE("operator") {
    int n;
	Population s(n);
	std::vector<Condition> board_;
    CHECK(s(0, 0) == board_[0]);
	CHECK(s(1, 0) == board_[n]);
	CHECK(s(0, 1) == board_[1]);
	CHECK(s(1, 1) == board_[n*1 + 1]);
	
    
} */
