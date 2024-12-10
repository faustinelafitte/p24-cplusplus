#include <iostream>

class Rational{
public: 
    int numerator;
    int denominator;
public:
    // Constructeur par défaut qui initialise à 0
    Rational() : numerator(0), denominator(1) {
        }
    // Constructeur avec un seul argument : 
    Rational(int num) : numerator(num), denominator(1){
    }
    // Constructeur avec deux arguments
    Rational (int num, int denom) : numerator (num), denominator (denom){
        if (denom==0){
            throw std :: invalid_argument("Denominator cannot be 0");
        }
    }
 
    void print (){
        std :: cout <<numerator<<"/"<<denominator<< std :: endl;
    }

    
};

bool operator==(Rational r1, Rational r2){
        return (r1.numerator*r2.denominator == r2.numerator*r1.denominator);
    }

Rational operator+ (Rational r1, Rational r2){
    int num = r1.numerator*r2.denominator + r1.denominator*r2.numerator;
    int denom = r1.denominator*r2.denominator;
    return Rational (num,denom);
}

//double to_float() const {
  //      return static_cast<double>(numerator) / static_cast<double>(denominator);

int main() {
    Rational r1;
    Rational r2 (1); //num=denom=1
    Rational r3 (1,2); //num=1 denom=2
    r1.print();
    r2.print();
    r3.print();

}