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
