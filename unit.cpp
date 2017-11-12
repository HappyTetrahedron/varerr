#include <iostream>
#include <cmath>
#include <string>

#include "unit.h"
#include "varerr.h"

#define IN(n) [n] = (n == i)
#define IN2(n) IN(n), IN(n+1), IN(n+2) 
#define IN3(n) IN2(n), IN2(n+3)

Unit::Unit (): 
    fac(1), 
    exp{0, 0, 0, 0, 0, 0} {} 

Unit::Unit (int i): 
    fac(1), 
    exp{IN3(0)} {}

Unit::Unit (double fac, const double *exp): 
    fac(fac), 
    exp{exp[0], exp[1], exp[2], exp[3], exp[4], exp[5]} {}

Unit::Unit (const Unit& u):
    Unit(u.getValue(), u.getUnit()) {}

// util

const char *LOOKUP [] = {"kg", "m", "s", "K", "A", "mol"};

// -

const Unit Unit::operator-(void) const {
    return (*this) * (-1);
}

// +

const Unit Unit::operator+(const Unit& u) const {
    if (!this->hasSameUnitAs(u))
        throw 1;
    return Unit(this->fac + u.getValue(), exp);
}
const Unit Unit::operator+(double d) const {
    if (this->hasUnit())
        throw 1;
    return Unit(this->fac + d, exp);
}
const Unit operator+(double d, const Unit& u) {
    return u + d;
}

// -

const Unit Unit::operator-(const Unit& u) const {
    return (*this) + (-u);
}
const Unit Unit::operator-(double d) const {
    return (*this) + (-d);
}
const Unit operator-(double d, const Unit& u) {
    return u - d;
}

// *

const Unit Unit::operator*(const Unit& u) const{
    double exp[6];
    int j;
    for (j = 0; j < 6; j++)
        exp[j] = this->exp[j] + u.getUnit()[j];
    return Unit(this->fac * u.getValue(), exp);
}
const Unit Unit::operator*(double d) const{
    return Unit(this->fac * d, this->exp);
}
const Unit operator*(double d, const Unit& u) {
    return u * d;
}

// /
const Unit Unit::operator/(const Unit& u) const{
    double exp[6];
    int j;
    for (j = 0; j < 6; j++)
        exp[j] = this->exp[j] - u.getUnit()[j];
    return Unit(this->fac / u.getValue(), exp);
}
const Unit Unit::operator/(double d) const{
    return Unit(this->fac / d, this->exp);
}
const Unit operator/(double d, const Unit& u) {
    return u / (d * bu::NU);
}

// ^

const Unit Unit::operator^(double d) const{
    double exp[6];
    int j;
    for (j = 0; j < 6; j++)
        exp[j] = this->exp[j] * d;
    return Unit(std::pow(this->fac, d), exp);
}
const Unit Unit::operator^(const Unit& u) const{
    double exp[6];
    int j;
    if (u.hasUnit())
        throw 1;
    for (j = 0; j < 6; j++)
        exp[j] = this->exp[j] * u.getValue();
    return Unit(std::pow(this->fac, u.getValue()), exp);
}
const Unit operator^(double d, const Unit& u) {
    if (u.hasUnit()) 
        throw 1;
    return std::pow(d, u.getValue()) * bu::NU;
}

// misc

double Unit::getValue(void) const{
    return this->fac;
}

double Unit::getValueInUnit(const Unit& u) const{
    return this->fac/u.getValue();
}

const Varerr Unit::operator<<(const Unit& u) const {
    if (!this->hasSameUnitAs(u))
        throw 1;
    return Varerr(*this, u.getValue()/this->fac);
}

const Varerr Unit::operator<<(double e) const {
    return Varerr(*this, e);
}


bool Unit::operator==(const Unit& u) const{
    return (this->fac == u.getValue()) && this->hasSameUnitAs(u);
}


const double *Unit::getUnit(void) const {
    return this->exp;
}

double Unit::getUnit(int i) const {
    return this->exp[i];
}

bool Unit::hasSameUnitAs(const Unit& u) const {
    bool res = true;
    int j;
    for (j=0; j < 6; j++)
        res &= (this->exp[j] == u.getUnit()[j]);
    return res;
}


bool Unit::hasUnit(void) const {
    return !Unit::hasSameUnitAs(bu::NU);
} 

std::string Unit::toString(void) const {
    int j;
    double d = this->getValue();
    std::string s("");
    if (d == (int) d) 
        s = std::to_string((int) d);
    else
        s = std::to_string(d);
    for (j = 0; j < 6; j++) {
        if (!this->getUnit(j) == 0) {
            s = s + LOOKUP[j] ;
            s = s + "^" ;
            d = this->getUnit(j);
            if (d == (int) d) 
                s = s + std::to_string((int) d);
            else
                s = s + std::to_string(d);
        }
    }
    return s;
}
