#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include<vector>
 
 
 
struct State{
    double s;
    double i; 
    double r; 
    //int d;
    
    State() {
        s = 0;
        i = 0;
        r = 0;
        //d = 0;
    }
    
};
 
bool operator==(State const& lhs, State const& rhs) {
    if((lhs.s == rhs.s) && (lhs.i == rhs.i) && (lhs.r == rhs.r)) { return true;}
    else { return false;}
}
 
class Epidemic{
     
     private:
         State s0();
         int n;
     public:
        std::vector<State> report;
         int const& pop = n;
         Epidemic(State const& s0, int s) : report{s0}, n{s} {};
         void evolve(double b, double g, double n_) {  // ic means initial Conditions
            
			 
			State next;
			 
             for(int i = 0; i < 10; ++i) {
				// assert( next.s >= 0 && next.r >= 0 && next.i >= 0);

             
			 if (next.s < 0) {
				 next.s == 0; } else {
					 next.s = report[i].s - b * report[i].s * report[i].i; }
			
			if (next.i < 0) {
				 next.i == 0; } else {
				 next.i = report[i].i + b * report[i].i * report[i].s - g * report[i].i; }
             
			 if (next.r < 0) {
				 next.r == 0; } else {
					 next.r = report[i].r + g * report[i].i; }
             report.push_back(next);
             //iC = next;
             }
         }
    };     
    
void printData(std::vector<State> report) {
         int daysPassed = 0;
         for(auto it = report.begin(), end = report.end(); it != end; ++it) {
             std::cout << "Giorno "<< daysPassed <<"\n Susceptibles: " << (*it).s << "\n Infectious: " << (*it).i << "\n Recovered: " << (*it).r <<'\n';
		 ++daysPassed;
         }
         }
 
int main() {
   double beta_;
   double gamma_;
   double population_;
   std::cout << "Welcome to the "Option 1 epidemic simulation", \n Please enter a value for beta (0 < x < 1, suggested values are between 0.001 and 0.01) the mean contagion rate: " << '\n';
   std::cin >> beta_;
   std::cout << "Enter a value for gamma (0 < x < 1, suggested values are between 0.001 and 0.005) the mean recovery rate: " << '\n';
   std::cin >> gamma_;
   std::cout << "Enter a value for the population ( x > 0, suggested value is 100): " << '\n';
   std::cin >> population_;
   
   double sus =  population_ - 1;
   State s0{};
   s0.s = sus;
   s0.i = 1;
   Epidemic covid(s0, population_);
   covid.evolve(beta_, gamma_, population_ );
   printData(covid.report);
 
 
 
}
