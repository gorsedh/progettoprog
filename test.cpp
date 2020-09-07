#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "structures.hpp"

#include <iostream>
#include <vector>
#include <typeinfo>
#include <random>
//#include <cmath>
#include <cassert>

////////////////////// GRID TEST //////////////////////////

TEST_CASE("operator()")
{
	int n = 10;
	Population s(n);
	std::vector<Condition> board_(n * n);
	CHECK(s(0, 0) == board_[0]);
	CHECK(s(1, 0) == board_[n]);
	CHECK(s(0, 1) == board_[1]);
	CHECK(s(1, 1) == board_[n * 1 + 1]);
}

TEST_CASE("check board")
{
	int n;
	Population s(n);
	CHECK(s(0, 0) == Condition::S);
	CHECK(s(1, 1) == Condition::S);

	for (int it = 0; it < 5; ++it)
	{
		////check that a casual person on the board is not infect/recovered/died or the cell is  empty
		int iTry = (rand() + time(nullptr)) % (s.getSize());
		int jTry = (rand() + time(nullptr)) % (s.getSize());
		if (it == 0)
		{
			CHECK(s(iTry, jTry) != Condition::I);
		}
		else if (it == 1)
		{
			CHECK(s(iTry, jTry) != Condition::E);
		}
		else if (it == 2)
		{
			CHECK(s(iTry, jTry) != Condition::R);
		}
		else
		{
			CHECK(s(iTry, jTry) != Condition::D);
		}
	}
}

TEST_CASE("another check board")
{
	int n;
	Population s(n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			s(i, j) = Condition::I;
		}
	}
	for (int it = 0; it < 5; ++it)
	{
		////check that a casual person on the board is not susceptible/recovered/died or the cell is  empty if we initialize all cells as infects
		int iTry = (rand() + time(nullptr)) % (s.getSize() - 2) + 1;
		int jTry = (rand() + time(nullptr)) % (s.getSize() - 2) + 1;
		if (it == 0)
		{
			CHECK(s(iTry, jTry) != Condition::S);
		}
		if (it == 1)
		{
			CHECK(s(iTry, jTry) != Condition::E);
		}
		else if (it == 2)
		{
			CHECK(s(iTry, jTry) != Condition::R);
		}
		else
		{
			CHECK(s(iTry, jTry) != Condition::D);
		}
	}
}

TEST_CASE("check susceptibleCounter")
{
	int n;
	Population t(n);
	CHECK(t.susceptiblesCounter() == std::pow(n, 2) - (4 * n - 4));
	if (n == 1)
	{
		CHECK(t.susceptiblesCounter() == 1);
	}
}

TEST_CASE("general check of Counters")
{
	int n = 10;
	Population p(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int c = 0; c < 8; c++)
			{
				if (c > 1 && c <= 5)
				{
					p(1, c) = Condition::I;
					p(2, c) = Condition::I;
					p(5, c) = Condition::R;
					p(4, c) = Condition::D;
				}
				else
				{
					p(i, j) = Condition::S;
				}
			}
		}
	}

	int sus = 0;
	int inf = 0;
	int rec = 0;
	int dead = 0;
	for (int i = 0; i < n - 2; i++)
	{ //si esclude il bordo
		for (int j = 0; j < n - 2; j++)
		{
			switch (p(i, j))
			{
			case Condition::S:
				sus++;
				break;
			case Condition::I:
				inf++;
				break;
			case Condition::R:
				rec++;
				break;
			case Condition::D:
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

TEST_CASE("struct parametersCheck  constructor")
{
	auto a = ParametersCheck(0., 0., true, 0.);
	CHECK(a.betaCheck_ == 0);
	CHECK(a.gammaCheck_ == 0);
	CHECK(a.cellMove_ == true);
	CHECK(a.emptyCells_ == 0.);

	auto b = ParametersCheck(0.3, 0.4, false, 0.9);
	CHECK(b.betaCheck_ == 0.3);
	CHECK(b.gammaCheck_ == 0.4);
	CHECK(b.cellMove_ == false);
	CHECK(b.emptyCells_ == 0.9);
}

////////////////////// FUNCTIONS TEST //////////////////////////
int booleanMarker(int x)
{
	if (x == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int initSize()
{
	int sizeval;
	if (sizeval > 5 && sizeval < 40)
	{
		return sizeval;
	}
	else
	{
		return 20;
	}
}

bool cellMove()
{
	char cellMove_;
	if (cellMove_ == 'n')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

auto emptyBoard(Population &pop)
{
	for (int i = 0; i < pop.getSize(); i++)
	{
		for (int j = 0; j < pop.getSize(); j++)
		{
			pop(i, j) = (Condition::S);
		}
	}
}

int adjacentInfects(Population &pop, int row, int column)
{
    //assert(row != 0 && column != 0);
    auto cell = pop(row, column);
    int result = 0;
    //count only adjacents, not the central one
    for (int i = row - 1; i != row + 2; ++i)
    {
        for (int j = column - 1; j != column + 2; ++j)
        {
            if (pop(i,j) == Condition::I)
            {
                result++;
            }
        }
    }
    switch (cell)
    {
    case Condition::I:
        return (result - 1);
        break;
    default:
        return result;
        break;
    }
}

auto cellMover(Population &pop)
{

	int iX, jX, iY, jY;
	int redSize = static_cast<int>(pop.getSize()) - 2; //avoid swapping cells on border
	int numOfSwaps = floor((redSize * redSize) / 10);
	for (int i = 0; i < numOfSwaps; i++)
	{

		iX = (rand() + time(nullptr)) % (redSize) + 1;
		jX = (rand() + time(nullptr)) % (redSize) + 1;
		iY = (rand() + time(nullptr)) % (redSize) + 1;
		jY = (rand() + time(nullptr)) % (redSize) + 1;

		if (pop(iX, jX) != Condition::D && pop(iY, jY) != Condition::D)
		{
			pop.swapTwoCells(iX, jX, iY, jY);
		}
	}
}

TEST_CASE("functionsTest, first heat")
{

	CHECK(booleanMarker(10) == 1);
	CHECK(typeid(booleanMarker(0.5)) == typeid(int(1))); // check that booleanMarker reads every number as integer, of course it did, otherwise this test wouldn't be here
	CHECK(initSize() == 20);							 // check the default set of initSize
	CHECK(cellMove() == 1);								 // check that the cells move themselves for the default option
	
	Population pop = 10;
	emptyBoard(pop);
	int iTry = (rand() + time(nullptr)) % (pop.getSize());
	int jTry = (rand() + time(nullptr)) % (pop.getSize());
	CHECK(pop(iTry, jTry) != Condition::I); // it seems I've already seen this test
	CHECK(pop(iTry, jTry) != Condition::E);
	CHECK(pop(iTry, jTry) != Condition::R);
	CHECK(pop(iTry, jTry) != Condition::D);

	CHECK(adjacentInfects(pop, 1, 1) == 0);
	CHECK(adjacentInfects(pop, 1, 3) == 0);
	CHECK(adjacentInfects(pop, 4, 4) == 0);

	Population popz = 10; // using implicit conversion in order to avoid declaring too many int variables to construct new Population
	popz(2, 2) = Condition::I;
	popz(2, 3) = Condition::I;
	popz(4, 4) = Condition::I;
	popz(3, 5) = Condition::I;
	popz(4, 6) = Condition::I;
	CHECK(adjacentInfects(popz, 2, 2) == 1); //the function doesn't consider the central cell
	CHECK(adjacentInfects(popz, 3, 3) == 3);
	CHECK(adjacentInfects(popz, 4, 1) == 0);
	CHECK(adjacentInfects(popz, 4, 5) == 3);
	CHECK(adjacentInfects(popz, 4, 6) == 1);
	CHECK(adjacentInfects(popz, 3, 6) == 2);

	popz(3, 3) = Condition::D;
	popz(7, 7) = Condition::D;
	cellMover(popz);
	CHECK(popz(3, 3) == Condition::D); // the function doesn't swap dead
	CHECK(popz(7, 7) == Condition::D);
	CHECK(popz(1, 1) == Condition::S); // the function doesn't swap a cell on the edge

	int smallerSize;
	Population r(smallerSize);
	if (smallerSize == 3)
	{
		r(2, 2) = Condition::I;
		cellMover(r);
		CHECK(r(2, 2) == Condition::I);
		CHECK(r(1, 1) != Condition::I);
	}
	else if (smallerSize == 4)
	{
		r(2, 2) = Condition::R;
		r(2, 3) = Condition::D;
		r(3, 2) = Condition::I;
		r(3, 3) = Condition::E;
		cellMover(r);
		CHECK(r(2, 2) != Condition::S); // no cell from the edges swapped
		CHECK(r(2, 3) != Condition::S);
		CHECK(r(3, 2) != Condition::S);
		CHECK(r(3, 3) != Condition::S);
		CHECK(r(2, 3) == Condition::D);
		CHECK(r(3, 3) != Condition::E);
	}
}
