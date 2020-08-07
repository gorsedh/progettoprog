#include<iostream>
#include<random>



inline Board evolve(Board const& current, int count_day)

  int const N = current.size();

  Board next(N);

  for (int i = 0; i != N; ++i) {
    for (int j = 0; j != N; ++j) {
      int const c = neighbours_infected(current, i, j);
    //  int r = neighbours_recovered(current, i, j); da implementare la possibilità che un recovered si possa reinfettare, p < 0.5%
      if( c >= 4) {
     if ((rand() + time(nullptr))%1000 > 300) {
        next(i, j) = State::I;
      } else {
        next(i, j); = current(i, j);
      }
    } else {
        if ((rand() + time(nullptr))%1000 > 700) {
        next(i, j) = State::I;
      } else {
        next(i, j); = current(i, j);
      }

    }
    ++count_day;
  }
  std::cout << count_day << std::endl;
  return next;
}
