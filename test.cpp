#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "structures.hpp"
 // al compilatore non piacciono nè functions.hpp nè initializations.hpp

#include <iostream>
#include <vector>
#include <typeinfo>
#include <random>
#include <cmath>

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
	CHECK(typeid(booleanMarker(0.5)) == typeid(int(1))); // check that booleanMarker reads every number as integer, of course it did, otherwise this test wouldn't be here
	CHECK(initSize() == 20); // check the default set of initSize
    CHECK(cellMove() == 1); // check that the cells move themselves for the default option
} 
	
////////////////////// GRID TEST //////////////////////////


TEST_CASE("operator()") {
    int n = 10;
	Population s(n);
	std::vector<Condition> board_(n*n);
    CHECK(s(0, 0) == board_[0]);
	CHECK(s(1, 0) == board_[n]);
	CHECK(s(0, 1) == board_[1]);
	CHECK(s(1, 1) == board_[n*1 + 1]);
	
	
    
} 

TEST_CASE("check board") {
	int n;
	Population s(n);
	CHECK(s(0,0) == Condition::S);
	CHECK(s(1,1) == Condition::S);
	
	
	for(int it = 0; it < 5; ++it){ 
		////check that a casual person on the board is not infect/recovered/died or the cell is  empty
	int iTry = (rand() + time(nullptr)) % (s.getSize());
	int jTry = (rand() + time(nullptr)) % (s.getSize());
	if(it == 0) {
	    CHECK(s(iTry, jTry) != Condition::I); 
	} else if(it == 1) {
	    CHECK(s(iTry, jTry) != Condition::E);
	} else if(it == 2) {
		CHECK(s(iTry, jTry) != Condition::R);
	} else {
	    CHECK(s(iTry, jTry) != Condition::D);
		}
   }
}

 TEST_CASE("another check board") {
	int n;
	Population s(n); 
	
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        s(i, j) = Condition::I;
	  }
    }
	      for(int it = 0; it < 5; ++it){ 
		   ////check that a casual person on the board is not susceptible/recovered/died or the cell is  empty if we initialize all cells as infects
		  int iTry = (rand() + time(nullptr)) % (s.getSize()-2) +1;
		  int jTry = (rand() + time(nullptr)) % (s.getSize()-2) +1;
	         if(it == 0) {
	          CHECK(s(iTry, jTry) != Condition::S); 
	       } if(it == 1) {
	          CHECK(s(iTry, jTry) != Condition::E);
	       } else if(it == 2) {
		      CHECK(s(iTry, jTry) != Condition::R);
	       } else {
	          CHECK(s(iTry, jTry) != Condition::D);
		   }
		}
}

TEST_CASE("check susceptibleCounter") {
	int n;
	Population t(n);
	CHECK(t.susceptiblesCounter() == std::pow(n, 2) - (4 * n - 4));
	if(n == 1) {
		CHECK(t.susceptiblesCounter() == 1);
	}
}	

TEST_CASE("general check of Counters") {
    int n = 10;
    Population p(n);
    for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for(int c = 0; c < 8; c++) {
				if( c > 1 && c <= 5) {
					p(1, c) = Condition::I;
					p(2, c) = Condition::I;
					p(5, c) = Condition::R;
                    p(4, c) = Condition::D;
				} else {
					 p(i, j) = Condition::S;
				}
			}
		}
	}
	
  int sus = 0;
  int inf = 0;
  int rec = 0;
  int dead = 0;
  for (int i = 0; i < n - 2; i++) { //si esclude il bordo
    for (int j = 0; j < n - 2; j++) {
		switch (p(i, j)) {
      case Condition::S :
        sus++;
        break;
      case Condition::I :
        inf++;
        break;
      case Condition::R :
        rec++;
        break;
	  case Condition::D :
	    dead++;
		break;
      default:
        break;
      }
    }
  }
  
  CHECK(sus == p.susceptiblesCounter());
  CHECK(inf == p.infectsCounter());
  CHECK(rec == p.recoveredCounter());
  CHECK(dead == p.deadCounter());
  CHECK(sus == 48); // n*n - (4*n - 4) - inf - rec - dead, n = 100
  CHECK(inf == 8);
  CHECK(rec == 4);
  CHECK(dead == 4);
}
				
	
