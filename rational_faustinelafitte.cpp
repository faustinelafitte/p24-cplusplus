#include <iostream>

// vr: 1) il faut indenter automatiquement ton code sous vscode

class Rational
{
private: // vr: 2) ne pas les mettre en public
         // les mettre en private et mettre friend les operator qui en ont besoin
    int numerator;
    int denominator;
    friend bool operator==(const Rational &r1, const Rational &r2);
    friend Rational operator+(const Rational &r1, const Rational &r2);
    friend std::ostream &operator<<(std::ostream &os, const Rational &r);

public:
    // Constructeur par défaut qui initialise à 0
    Rational() : numerator(0), denominator(1)
    {
    }
    // Constructeur avec un seul argument :
    Rational(int num) : numerator(num), denominator(1)
    {
    }
    // Constructeur avec deux arguments
    Rational(int num, int denom) : numerator(num), denominator(denom)
    {
        if (denom == 0)
        {
            throw std ::invalid_argument("Denominator cannot be 0");
        }
    }

    void print() const
    {
        std ::cout << numerator << "/" << denominator;
    }

    double to_float() const
    {
        return static_cast<double>(numerator) / static_cast<double>(denominator);
    }

    
};
// vr: 3) il faut passer les deux arguments de type Rational par référence pour ne pas le recopier
// vr: 4) il faut passer les deux arguments de type Rational const parce qu'on ne les modifie pas
// vr: 5) il faut déclarer ces fonctions friend dans la classe pout accéder aux attributs private
//        et ne pas les mettre public !!!
bool operator==(const Rational &r1, const Rational &r2)
{
    return (r1.numerator * r2.denominator == r2.numerator * r1.denominator);
}

// vr: idem
Rational operator+(const Rational &r1, const Rational &r2)
{
    int num = r1.numerator * r2.denominator + r1.denominator * r2.numerator;
    int denom = r1.denominator * r2.denominator;
    return Rational(num, denom);
}
// vr: 6) déclarer cette fonction comme une méthode de la classe Rational
//        là tu déclares une fonction globale donc c++ ne comprends pas ce que tu veux faire...
// double to_float() const {
//       return static_cast<double>(numerator) / static_cast<double>(denominator);

// vr: 7) définir la fonction globale
// std::ostream &operator<<(std::ostream &os, const Rational &r) {
// ton code ici (cette fonction appelle print)
// }

std::ostream &operator<<(std::ostream &os, const Rational &r)
{
    r.print();
    return os;
}

int main()
{
    Rational r1;
    Rational r2(1);    // num=denom=1
    Rational r3(1, 2); // num=1 denom=2
    r1.print();
    r2.print();
    r3.print();
}