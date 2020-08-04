#include<iostream>
#include<numeric>
#include<algorithm>

auto calculator(double a, double b, char i) {
    
 if(i == '+') {
     std::cout << "The result is " << a + b << ".";

 } else if ( i == '-' ) {
     std::cout << "The result is " << a - b << ".";

 } else if ( i == '*') 
{
    std::cout << "The result is " << a * b << ".";
} else if ( i == '/' && b != 0) {
    std::cout << "The result is " << a / b << ".";
} else {
    std::cout << "The character is not valid";
}
return 0;
}


int main() {

    char op;
    double num1;
    double num2;

std::cout << "Enter a number: " << std::endl;
std::cin >> num1;
std::cout << "Enter another numer: " << std::endl;
std::cin >> num2;
std::cout << "Enter an operator" << std::endl;
std::cin >> op;

return calculator(num1, num2, op);

}
