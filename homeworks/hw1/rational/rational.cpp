#include <stdexcept>
#include "rational.h"
#include <cmath>
#include <iostream>

Rational::Rational()
{
    n = 0;
    d = 1;
}
Rational::Rational(int num, int denom)
{
    if (denom == 0) throw std::invalid_argument("Can't have denom = 0");
    // Continue your implementation below.
    // You should likely call this->reduce() and this->normalize0()
    n = num;
    d = denom;

    this->normalize0();
    this->reduce();
}

std::ostream& operator<<(std::ostream& ostr, const Rational& r){
    //outputs the numerator and the denom with a / in the middle
    ostr << r.n << "/" << r.d;
    return ostr;
}

std::istream& operator>>(std::istream& istr, Rational& r){
    //creates a temp variable
    char temp;
    //inputs into the variables of object
    if(istr >> r.n >> temp){
        if(temp == '/'){
            if(istr >> r.d){
                r.reduce();
                r.normalize0();
                return istr;
            }
        }
    }
    r.n = 0; r.d = 1;
    return istr;
}
        

//adds rational to rational
Rational Rational::operator+(const Rational& rhs) const{
    // using fraction addition, creates new variable
    Rational temp(n*rhs.d + rhs.n*d, d*rhs.d);
    return temp;
}

//adds rational to int
Rational Rational::operator+(const double& rhs) const{
    // using fraction addition, creates new variable
    Rational temp(n+ rhs*d, d);
    return temp;
}

// adds int to rational
Rational operator+(double lhs, const Rational& rhs){
    // using fraction addition, creates new variable
    Rational temp(lhs*rhs.d + rhs.n, rhs.d);
    return temp;
}

//multiplies rational with rational
Rational Rational::operator*(const Rational& rhs) const{
    Rational temp(n*rhs.n, d*rhs.d);
    return temp;
}

//multiplies rational with int
Rational Rational::operator*(const double& rhs) const{
    Rational temp(n*rhs, d);
    return temp;
}

//multiplies int with rational
Rational operator*(double lhs, const Rational& rhs){
    Rational temp(lhs*rhs.n, rhs.d);
    return temp;
}

//rational^int
Rational Rational::operator^(const double& rhs) const{
    //edge case power is 0;
    if(rhs == 0){
        Rational temp(1, 1);
        return temp;
    }
    //if power is negative
    else if (rhs < 0){
        Rational temp(pow(d, rhs*-1),pow(n, rhs*-1));
        return temp;
    }
    //normal case
    else{
        Rational temp(pow(n, rhs), pow(d,rhs));
        return temp;
    }
}
//equality of rational to rational
bool Rational::operator==(const Rational& rhs) const{
    //comapres demon and numer
    return (n == rhs.n && d == rhs.d);
}

//opposite of quality (rational to rational)
bool Rational::operator!=(const Rational& rhs) const{
    return (n != rhs.n || d != rhs.d);
}

//Rational < Rational
bool Rational::operator<(const Rational& rhs) const{
    //equates the difference
    double calc = (rhs.n*d - n*rhs.d)/(rhs.d*d);
    
    if(calc > 0){
        return true;
    }
    else {
        return false;
    }
}

//Rational += Rational
Rational Rational::operator+=(const Rational& rhs){
    //changes the value of the Rational itself
    n = n*rhs.d + rhs.n*d;
    d = d*rhs.d;
    this->reduce();
    this->normalize0();
    return *this;
}

//Rational += int
Rational Rational::operator+=(const double rhs){
    //changes the value of rational
    n += rhs*d;
    this->reduce();
    this->normalize0();
    return *this;
}

//Rational *= Rational
Rational Rational::operator*=(const Rational& rhs){
    //changes the value of the rational
    n = n * rhs.n;
    d = d * rhs.d;
    this->reduce();
    return *this;
}

//Rational *= int
Rational Rational::operator*=(const double rhs){
    //alters the value of rational
    n = n * rhs;
    this->reduce();
    return *this;
}


//PRIVATE
void Rational::reduce(){
    int divisor = gcd(n, d);
    n = n/divisor;
    d = d/divisor;
    
    // deals with negative signs
    //2 cases
    //case 1: both are negative, cancels both
    //case 2: denom is neg, brings neg to num
    if (d < 0){
        n = -n;
        d = -d;
    }
}

int Rational::gcd(int a, int b){
    //https://www.geeksforgeeks.org/
    // recersive implimentation
    if(a == 0){
        return b;
    }
    return gcd(b%a, a);
}

int Rational::lcm(int a, int b){
    //https://www.geeksforgeeks.org/
    //Based off principle: a x b = lcm(a,b) x gcd(a,b)
    return (a*b)/gcd(a, b);
}

void Rational::normalize0()
{
    if (n == 0 && d != 1) d = 1;
}

