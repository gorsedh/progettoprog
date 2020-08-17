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
         State s0;
         int n;
     public:
        std::vector<State> report;
         int const& pop = n;
         Epidemic(State const& s0, int s) : report{s0}, n{s} {};
         void evolve(double b, double g, double n) {  // ic means initial Conditions
            
            State next;
            auto iC = s0;
			 
             for(int i = 0; i < 100; ++i) {

             next.s = iC.s - b * iC.s * iC.i;
			 if (next.s < 0) {
				 next.s == 0; }
			next.i = iC.i + b * iC.i * iC.s - g * iC.i;
			if (next.i < 0) {
				 next.i == 0; }
             next.r = iC.r + g * iC.i;
			 if (next.r < 0) {
				 next.r == 0; }
             report.push_back(next);
             iC = next;
             }
         }
    };     
    
void printData(std::vector<State> report) {
         for(auto it = report.begin(), end = report.end(); it != end; ++it) {
             std::cout << "Susceptibles: " << (*it).s << "\n Infectious: " << (*it).i << "\n Recovered: " << (*it).r <<'\n';
         }
         }
 
int main() {
   double beta_;
   double gamma_;
   double population_;
   std::cout << "Welcome to... \n, Please enter a value for beta (0 < x < 1, suggested values are between 0.3 and 0.6) the mean contagion rate: " << '\n';
   std::cin >> beta_;
   std::cout << "Enter a value for gamma (0 < x < 1, suggested values are between 0.03 and 0.2) the mean recovery rate: " << '\n';
   std::cin >> gamma_;
   std::cout << "Enter a value for the population ( x >0, suggested values are between 50 and 200): " << '\n';
   std::cin >> population_;
   
   State s0{};
   Epidemic covid(s0, population_);
   covid.evolve(beta_, gamma_, population_ );
   printData(covid.report);
 
 
 
}
